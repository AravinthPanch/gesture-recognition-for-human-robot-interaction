/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 22/12/14.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/log/trivial.hpp>
#include "udp_server.h"
#include "skeleton_tracker.h"
#include "gesture_tracker.h"
#include "utils.h"


/**
 * Constructor
 *
 */

udp_server::udp_server(boost::asio::io_service& io_service):
client_port(getConfigValue<int>("clientPort")),
server_port(getConfigValue<int>("serverPort")),
socket_server(io_service, udp::endpoint(udp::v4(), server_port))
{
    clientConnected = false;
    receive();
    BOOST_LOG_TRIVIAL(info) << "UDP Server started at port : " << server_port;
}


/**
 * Create UDP connection and start receive
 *
 */

void udp_server::receive()
{
    socket_server.async_receive_from(
                                     boost::asio::buffer(receive_buffer),
                                     client_endpoint,
                                     boost::bind(
                                                 &udp_server::handle_receive,
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

void udp_server::send(boost::shared_ptr<std::string> message){
    if(isClientConnected()){
        socket_server.async_send_to(boost::asio::buffer(*message),
                                    client_endpoint,
                                    boost::bind(
                                                &udp_server::handle_send,
                                                this,
                                                message,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred
                                                )
                                    );
    }
    else
    {
        BOOST_LOG_TRIVIAL(debug) << *message;
    }
    
}


/**
 * Create UDP connection handler for receiving data
 *
 */

void udp_server::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size)
    {        
        std::string data_received(receive_buffer.begin(), receive_buffer.end());
        BOOST_LOG_TRIVIAL(debug) << "Received : " << data_received << " : " << bytes_transferred << " bytes : " << client_endpoint;
        
        BOOST_LOG_TRIVIAL(info) << "UDP Client connected" ;
        clientConnected = true;
        
        receive();
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

void udp_server::handle_send(boost::shared_ptr<std::string> message, const boost::system::error_code& error, std::size_t bytes_transferred)
{
    BOOST_LOG_TRIVIAL(info) << "Sent : " << *message;
}


/**
 * Check whether client is connected
 *
 */

bool udp_server::isClientConnected(){
    return clientConnected;
}


