/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 28/12/14.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#ifndef __human_robot_interaction__udp_client__
#define __human_robot_interaction__udp_client__

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include "setup.h"
#include "brain.h"
#include "websocket_server.h"


using boost::asio::ip::udp;

class udp_client
{
    
private:
    const int server_port;
    const int client_port;
    const char* server_host_name;
    
    boost::array<char, 1024> receive_buffer;
    boost::array<char, 8> send_buffer;
    
    udp::endpoint server_endpoint;
    udp::socket socket_client;
    websocket_server ws_socket;
    
    brain* brain_;
    
    void receive();
    void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);
    void handle_send(boost::shared_ptr<std::string> message, const boost::system::error_code& error, std::size_t bytes_transferred);

    udp::endpoint endpoint_resolver(boost::asio::io_service& io_service, const char* host_name, int port);
    
    
public:
    udp_client(boost::asio::io_service& io_service, brain *brain);
    void send(boost::shared_ptr<std::string> message);
};

#endif