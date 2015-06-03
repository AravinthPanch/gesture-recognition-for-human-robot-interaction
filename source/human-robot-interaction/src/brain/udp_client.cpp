/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 28/12/14.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include "udp_client.h"
#include <iostream>
#include <string>
#include <boost/log/trivial.hpp>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <boost/thread.hpp>


/**
 * Constructor
 *
 */

udp_client::udp_client(boost::asio::io_service& io_service, brain *brain) :
client_port(getConfigValue<int>("clientPort")),
server_port(getConfigValue<int>("serverPort")),
server_host_name(getConfigValue<char*>("serverHostName")),
socket_client(io_service, udp::endpoint(udp::v4(), client_port))
{
    BOOST_LOG_TRIVIAL(info) << "UDP Client started at port : " << client_port;
    
    // Resolve hostname to IP (Eg: nao5.local to 10.0.7.5) and attach io service from main thread
    server_endpoint = endpoint_resolver(io_service, server_host_name,  server_port);
    
    // Send message to the server. Message is a string that is 01 to initate Hand Tracker
    boost::shared_ptr<std::string> message(new std::string("01"));
    send(message);
    
    //Reference Brain Module
    brain_ = brain;
    
    // Start a thread for Websocket
    boost::thread socket_thread(boost::bind(&websocket_server::init, &ws_socket));
}



/**
 * Create UDP connection and start receive
 *
 */

void udp_client::receive()
{
    socket_client.async_receive_from(
                                     boost::asio::buffer(receive_buffer),
                                     server_endpoint,
                                     boost::bind(
                                                 &udp_client::handle_receive,
                                                 this,
                                                 boost::asio::placeholders::error,
                                                 boost::asio::placeholders::bytes_transferred
                                                 )
                                     );
}


/**
 * Send data to the conneted end point
 *
 */

void udp_client::send(boost::shared_ptr<std::string> message){
    socket_client.async_send_to(boost::asio::buffer(*message),
                                server_endpoint,
                                boost::bind(
                                            &udp_client::handle_send,
                                            this,
                                            message,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred
                                            )
                                );
}



/**
 * Parse the received string and extract the data
 *
 */

vector<vector<double>> getHandData(const char* json){
    
    rapidjson::Document document;
    document.Parse(json);
    
    vector<vector<double>> handVector;
    vector<double> leftHand;
    vector<double> rightHand;
    
    // NiTE gesture must be taken care as welll
    if(document.HasMember("RIGHT") && document.HasMember("LEFT")){
        rapidjson::Value& handData1 = document["RIGHT"];
        rightHand.push_back(std::atof(handData1[0u].GetString()));
        rightHand.push_back(std::atof(handData1[1u].GetString()));
        rightHand.push_back(std::atof(handData1[2u].GetString()));
        
        rapidjson::Value& handData2 = document["LEFT"];
        leftHand.push_back(std::atof(handData2[0u].GetString()));
        leftHand.push_back(std::atof(handData2[1u].GetString()));
        leftHand.push_back(std::atof(handData2[2u].GetString()));
        
        handVector.push_back(rightHand);
        handVector.push_back(leftHand);
    }
    else if(document.HasMember("RIGHT")){
        rapidjson::Value& handData1 = document["RIGHT"];
        rightHand.push_back(std::atof(handData1[0u].GetString()));
        rightHand.push_back(std::atof(handData1[1u].GetString()));
        rightHand.push_back(std::atof(handData1[2u].GetString()));
        
        handVector.push_back(rightHand);
        handVector.push_back(leftHand);
    }
    else if(document.HasMember("LEFT")){
        rapidjson::Value& handData2 = document["LEFT"];
        leftHand.push_back(std::atof(handData2[0u].GetString()));
        leftHand.push_back(std::atof(handData2[1u].GetString()));
        leftHand.push_back(std::atof(handData2[2u].GetString()));
        
        handVector.push_back(rightHand);
        handVector.push_back(leftHand);
    }
    
    return handVector;
}



/**
 * receive_buffer has also old data. New data must be trimmed by checking the data between { and } brackets
 *
 */

string trim_data(string receivedBufferData){
    std::size_t first = receivedBufferData.find_first_of("{");
    std::size_t last = receivedBufferData.find_first_of("}");
    std::string trimmedData = receivedBufferData.substr(first,last+1);
    return trimmedData;
}

/**
 * Create UDP connection handler for receiving data
 *
 */

void udp_client::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size)
    {
        // Receive next data
        receive();
        
        // receive_buffer has also old data. New data must be trimmed by checking the data between { and } brackets
        std::string trimmedData = trim_data(receive_buffer.data());
        BOOST_LOG_TRIVIAL(debug) << "Received : " << trimmedData;
        
        // Parse the received json string to get data
        const char * jsonString = trimmedData.c_str();
        vector<vector<double>> handVector = getHandData(jsonString);
        
        // Predict or train
        if(brain_->isPredictionModeActive() && !handVector.empty()){
            
            // Predict and get classLabel and maximum likelihood
            vector<double> predictionResults = brain_->predict(handVector[0], handVector[1]);
            
            // Parse the same received json
            rapidjson::Document document;
            document.Parse(jsonString);
            
            // Add an array OUTPUT with prediction results
            rapidjson::Value predictionArray(rapidjson::kArrayType);
            predictionArray.PushBack(predictionResults[0], document.GetAllocator()).PushBack(predictionResults[1], document.GetAllocator());
            document.AddMember("OUTPUT", predictionArray, document.GetAllocator());
            
            // Write the document to the buffer
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            document.Accept(writer);
            
            // BOOST_LOG_TRIVIAL(debug) << buffer.GetString();
            
            //Send it via websocket with prediction results
            if(ws_socket.isClientConnected())
            {
                ws_socket.send(buffer.GetString());
            }
        }
        else if(brain_->isTrainingModeActive()){
            brain_->train(handVector[0], handVector[1]);
            
            //Send it via websocket without prediction results
            if(ws_socket.isClientConnected())
            {
                ws_socket.send(jsonString);
            }
        }
        else {
            //Forward it via websocket
            if(ws_socket.isClientConnected())
            {
                ws_socket.send(jsonString);
            }
        }
    }
    else
    {
        BOOST_LOG_TRIVIAL(error) << error;
    }
}


/**
 * Create UDP connection handler for sending data
 *
 */

void udp_client::handle_send(boost::shared_ptr<std::string> message, const boost::system::error_code& error, std::size_t bytes_transferred)
{
    BOOST_LOG_TRIVIAL(info) << "Sent : " << *message << " : " << server_endpoint;
    receive();
}



/**
 * Resolve hostname to IP
 *
 */

udp::endpoint udp_client::endpoint_resolver(boost::asio::io_service& io_service, const char* host_name, int port){
    udp::resolver resolver(io_service);
    udp::resolver::query query(udp::v4(), host_name, std::to_string(port));
    udp::resolver::iterator iterator = resolver.resolve(query);
    return *iterator;
}



