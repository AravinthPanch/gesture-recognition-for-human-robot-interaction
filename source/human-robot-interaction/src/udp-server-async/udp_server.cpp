/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 22/12/14.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include <iostream>
#include <string>
#include "udp_server.h"


/**
 * Constructor
 *
 */

udp_server::udp_server(boost::asio::io_service& io_service) : socket_(io_service, udp::endpoint(udp::v4(), SERVER_PORT_))
{
    start_receive();
    std::cout << "UDP Server started at port : " << SERVER_PORT_ << std::endl;
}


/**
 * Create UDP connection and start receive
 *
 */

void udp_server::start_receive()
{
    socket_.async_receive_from(
                               boost::asio::buffer(recv_buffer_),
                               remote_endpoint_,
                               boost::bind(
                                           &udp_server::handle_receive,
                                           this,
                                           boost::asio::placeholders::error,
                                           boost::asio::placeholders::bytes_transferred
                                           )
                               );
}


/**
 * Create UDP connection handler for receiving data
 *
 */

void udp_server::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size)
    {
        std::cout << "Received " << remote_endpoint_ << std::endl;
        start_receive();
    }
    else
    {
        std::cout << "Error " << remote_endpoint_ << std::endl;
    }
}



/**
 * Create UDP connection handler for sending data
 *
 */

void udp_server::handle_send(boost::shared_ptr<std::string> message, const boost::system::error_code& error, std::size_t bytes_transferred)
{
    std::cout << "Sent " << remote_endpoint_ << std::endl;
}

