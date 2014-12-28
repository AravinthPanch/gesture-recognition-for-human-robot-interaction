/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 22/12/14.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#ifndef __human_robot_interaction__udp_server__
#define __human_robot_interaction__udp_server__

#include <stdio.h>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

using boost::asio::ip::udp;
class udp_server
{
    
private:
    const int SERVER_PORT = 50005;
    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 4> recv_buffer_;
    bool connected = false;
    
    void start_receive();
    void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);
    void handle_send(boost::shared_ptr<std::string> message, const boost::system::error_code& error, std::size_t bytes_transferred);
    
public:
    udp_server(boost::asio::io_service& io_service);
    void send(boost::shared_ptr<std::string> message);
    bool isConnected();
};



#endif