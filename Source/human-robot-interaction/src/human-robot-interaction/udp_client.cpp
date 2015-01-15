/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 28/12/14.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include <iostream>
#include <string>
#include <boost/log/trivial.hpp>
#include "udp_client.h"


#include<sstream>
template <typename T>
std::string to_string(T value)
{
    //create an output string stream
    std::ostringstream os ;
    
    //throw the value into the string stream
    os << value ;
    
    //convert the string stream into a string and return
    return os.str() ;
}


/**
 * Constructor
 *
 */

udp_client::udp_client(boost::asio::io_service& io_service) : socket_client(io_service, udp::endpoint(udp::v4(), client_port)),
server_port(5005),client_port(5006), server_host_name_remote("nao6.local"), server_host_name_local("localhost")
{
    server_endpoint = endpoint_resolver(io_service, server_host_name_remote,  server_port);
    
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
 * Create UDP connection handler for receiving data
 *
 */

void udp_client::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size)
    {
        std::string data_b = receive_buffer.data();
        std::size_t f = data_b.find_first_of("{");
        std::size_t l = data_b.find_first_of("}");
        std::string data_c = data_b.substr(f,l+1);
        
        BOOST_LOG_TRIVIAL(info) << "Received : " << data_c << " : " << bytes_transferred << " bytes : " << server_endpoint;
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



