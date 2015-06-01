/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 22/12/14.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#ifndef __human_robot_interaction__udp_server__
#define __human_robot_interaction__udp_server__

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include "setup.h"

using boost::asio::ip::udp;

class udp_server
{
    
private:
    const int server_port;
    const int client_port;
    bool clientConnected;
    boost::array<char, 2> receive_buffer;
    boost::array<char, 8> send_buffer;
    udp::endpoint client_endpoint;
    udp::socket socket_server;
    
    void receive();
    void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);
    void handle_send(boost::shared_ptr<std::string> message, const boost::system::error_code& error, std::size_t bytes_transferred);
    
public:
    udp_server(boost::asio::io_service& io_service);
    void send(boost::shared_ptr<std::string> message);
    std::string connectedClient;
    bool isClientConnected();
    
};

#endif
