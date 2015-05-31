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
multicast_port(getConfigValue<int>("multicastPort")),
multicast_address(getConfigValue<std::string>("multicastAddress")),
multicast_endpoint(boost::asio::ip::address::from_string(multicast_address),multicast_port),
socket_server(io_service, multicast_endpoint.protocol())
{
    BOOST_LOG_TRIVIAL(info) << "UDP Multicast Server added membership to IP : " << multicast_address << " at Port : " << multicast_port;
}




/**
 * Send data to the conneted end point
 *
 */

void udp_server::send(boost::shared_ptr<std::string> message){
    
    socket_server.async_send_to(boost::asio::buffer(*message),
                                multicast_endpoint,
                                boost::bind(
                                            &udp_server::handle_send,
                                            this,
                                            message,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred
                                            )
                                );
}



/**
 * Create UDP connection handler for sending data
 *
 */

void udp_server::handle_send(boost::shared_ptr<std::string> message, const boost::system::error_code& error, std::size_t bytes_transferred)
{
    std::cout << "done";
    //    BOOST_LOG_TRIVIAL(info) << "Sent : " << *message;
}











/**
 * Create UDP connection and start receive
 *
 */

//void udp_server::receive()
//{
//    socket_server.async_receive_from(
//                                     boost::asio::buffer(receive_buffer),
//                                     client_endpoint,
//                                     boost::bind(
//                                                 &udp_server::handle_receive,
//                                                 this,
//                                                 boost::asio::placeholders::error,
//                                                 boost::asio::placeholders::bytes_transferred
//                                                 )
//                                     );
//}












/**
 * Create UDP connection handler for receiving data
 *
 */

//void udp_server::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
//{
//    if (!error || error == boost::asio::error::message_size)
//    {
//
//        std::string data_received(receive_buffer.begin(), receive_buffer.end());
//        BOOST_LOG_TRIVIAL(info) << "Received : " << data_received << " : " << bytes_transferred << " bytes : " << client_endpoint;
//
//        if(data_received=="01")
//        {
//            BOOST_LOG_TRIVIAL(info) << "Gesture Tracker activated" ;
//            connectedClient="gesture";
//            clientConnected = true;
//        }
//        else if(data_received=="02")
//        {
//            BOOST_LOG_TRIVIAL(info) << "Skeleton Tracker activated" ;
//            connectedClient = "skeleton";
//            clientConnected = true;
//        }else
//        {
//            clientConnected = false;
//        }
//
//        receive();
//    }
//    else
//    {
//        BOOST_LOG_TRIVIAL(error) << error;
//    }
//}





/**
 * Check whether client is connected
 *
 */

bool udp_server::isClientConnected(){
    return clientConnected;
}


