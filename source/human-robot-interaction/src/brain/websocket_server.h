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
#include <set>

typedef websocketpp::server<websocketpp::config::asio> ws_socket;
typedef ws_socket::message_ptr message_ptr;
typedef std::set<websocketpp::connection_hdl,std::owner_less<websocketpp::connection_hdl>> con_list;

class websocket_server
{
private:
    ws_socket ws_socket_;
    websocketpp::connection_hdl cc_hdl_;
    websocketpp::connection_hdl al_hdl_;
    bool clientConnected = false;
    void on_open(websocketpp::connection_hdl hdl);
    void on_close(websocketpp::connection_hdl hdl);
    void on_message(ws_socket* server_, websocketpp::connection_hdl hdl, message_ptr msg);
    
public:
    void init();
    void send(const char* parsedData, bool isLogged, int client);
    bool isClientConnected();
    con_list connections_hdl;
};


#endif