/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 01/06/15.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#ifndef __human_robot_interaction__websocket_server__
#define __human_robot_interaction__websocket_server__

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <iostream>

typedef websocketpp::server<websocketpp::config::asio> ws_socket;
typedef ws_socket::message_ptr message_ptr;

class websocket_server
{
    
private:
    ws_socket ws_socket_;
    websocketpp::connection_hdl hdl_;
    bool clientConnected = false;
    void on_message(ws_socket* server_, websocketpp::connection_hdl hdl, message_ptr msg);
    
public:
    void init();
    void send(const char* parsedData, bool isLogged);
    bool isClientConnected();
};


#endif