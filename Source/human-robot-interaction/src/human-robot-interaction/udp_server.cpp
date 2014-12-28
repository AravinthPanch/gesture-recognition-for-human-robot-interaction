/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 22/12/14.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include <iostream>
#include <string>
#include <boost/log/trivial.hpp>
#include "udp_server.h"

/**
 * Constructor
 *
 */

udp_server::udp_server(boost::asio::io_service& io_service) : socket_(io_service, udp::endpoint(udp::v4(), SERVER_PORT))
{
    start_receive();
    BOOST_LOG_TRIVIAL(info) << "UDP Server started at port : " << SERVER_PORT;
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
 * Send data to the conneted end point
 *
 */
void udp_server::send(boost::shared_ptr<std::string> message){
    socket_.async_send_to(boost::asio::buffer(*message),
                          remote_endpoint_,
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
 * Create UDP connection handler for receiving data
 *
 */

void udp_server::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size)
    {
        connected = true;
        std::string data_received(recv_buffer_.begin(), recv_buffer_.end());
        BOOST_LOG_TRIVIAL(info) << "Received : " << data_received << " : " << remote_endpoint_;
        start_receive();
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
    BOOST_LOG_TRIVIAL(info) << "Sent : " << *message << " to : " << remote_endpoint_;
}



/**
 * Check whether client is connected
 *
 */

bool udp_server::isConnected(){
    return connected;
}












