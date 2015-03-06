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
    //Reference Brain Module
    brain_ = brain;
    
    // Resolve hostname and attach io service from main threas
    server_endpoint = endpoint_resolver(io_service, server_host_name,  server_port);
    
    // Send message to the server. Message is a string that is 01 to initate Hand Tracker
    boost::shared_ptr<std::string> message(new std::string("01"));
    send(message);
    BOOST_LOG_TRIVIAL(info) << "UDP Client started at port : " << client_port;
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
    
    
    // NiTE gesture must be taken care as welll
    rapidjson::Value& handData = document["HAND"];
    
    vector<double> leftHand;
    vector<double> rightHand;
    
    
    // Hand tracker may send hand id greater than 2. Hand tracker must reset the ids if both the hands are lost from the scene
    if(strcmp(handData[0u].GetString(), "1") == 0){
        leftHand.push_back(std::atof(handData[1u].GetString()));
        leftHand.push_back(std::atof(handData[2u].GetString()));
        leftHand.push_back(std::atof(handData[3u].GetString()));
        
    }
    else if(strcmp(handData[0].GetString(), "2") == 0){
        rightHand.push_back(std::atof(handData[1u].GetString()));
        rightHand.push_back(std::atof(handData[2u].GetString()));
        rightHand.push_back(std::atof(handData[3u].GetString()));
    }
    
    vector<vector<double>> handVector;
    handVector.push_back(leftHand);
    handVector.push_back(rightHand);
    
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
        BOOST_LOG_TRIVIAL(info) << "Received : " << trimmedData << " : " << bytes_transferred << " bytes : " << server_endpoint;
        
        
        // Parse the received json string to get data
        const char * jsonString = trimmedData.c_str();
        vector<vector<double>> handVector = getHandData(jsonString);
        
        
        // Predict or train
        if(brain_->isPredictionModeActive()){
            string classLabel = brain_->predict(handVector[0], handVector[1]);
            boost::shared_ptr<std::string> message(new string(classLabel));
            send(message);
        }
        else if(brain_->isTrainingModeActive()){
            brain_->train(handVector[0], handVector[1]);
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
 * Resolve hostname
 *
 */

udp::endpoint udp_client::endpoint_resolver(boost::asio::io_service& io_service, const char* host_name, int port){
    udp::resolver resolver(io_service);
    udp::resolver::query query(udp::v4(), host_name, std::to_string(port));
    udp::resolver::iterator iterator = resolver.resolve(query);
    return *iterator;
}



