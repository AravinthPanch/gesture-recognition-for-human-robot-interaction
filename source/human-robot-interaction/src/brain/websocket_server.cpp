/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 01/06/15.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include "websocket_server.h"
#include "setup.h"
#include <boost/log/trivial.hpp>

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;


/**
 * On Message handler
 *
 */


void websocket_server::on_open(websocketpp::connection_hdl hdl) {
    connections_hdl.insert(hdl);
    BOOST_LOG_TRIVIAL(debug) << "Websocket Client connected";
}


void websocket_server::on_close(websocketpp::connection_hdl hdl) {
    connections_hdl.erase(hdl);
    BOOST_LOG_TRIVIAL(debug) << "Websocket Client closed";
}


void websocket_server::on_message(ws_socket* socket_, websocketpp::connection_hdl hdl, message_ptr msg) {
    
    if(msg->get_payload() == "CC"){
        cc_hdl_ = hdl;
        clientConnected = true;
        BOOST_LOG_TRIVIAL(info) << "Control Center connected via websocket";
    }
    else if (msg->get_payload() == "AL"){
        al_hdl_ = hdl;
        clientConnected = true;
        BOOST_LOG_TRIVIAL(info) << "Al-Proxy connected via websocket";
    }
    
}

/**
 * Initiate the websocket server
 *
 */

void websocket_server::init(){
    int websocketPort =getConfigValue<int>("websocketPort");
    BOOST_LOG_TRIVIAL(info) << "Websocket started at Port : " << websocketPort;
    
    try{
        // Set logging settings
        ws_socket_.set_access_channels(websocketpp::log::alevel::none);
        ws_socket_.set_access_channels(websocketpp::log::elevel::none);
        
        
        // Initialize ASIO
        ws_socket_.init_asio();
        
        // Register our message handler
        ws_socket_.set_open_handler(websocketpp::lib::bind(&websocket_server::on_open,this,::_1));
        ws_socket_.set_close_handler(websocketpp::lib::bind(&websocket_server::on_close,this,::_1));
        ws_socket_.set_message_handler(websocketpp::lib::bind(&websocket_server::on_message,this,&ws_socket_,::_1,::_2));
        
        // Listen on websocketPort
        ws_socket_.listen(websocketPort);
        
        // Start the server accept loop
        ws_socket_.start_accept();
        
        // Start the ASIO io_service run loop
        ws_socket_.run();
        
    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    }
}


/**
 * send data to the client
 *
 */

void websocket_server::send(const char* parsedData, bool isLogged, int client){
    
    if(isClientConnected())
    {
        if(client == 1){
            ws_socket_.send(cc_hdl_, parsedData, websocketpp::frame::opcode::text);
        }
        else if(client == 2){
            ws_socket_.send(al_hdl_, parsedData, websocketpp::frame::opcode::text);
        }
        else if(client == 3){
            ws_socket_.send(cc_hdl_, parsedData, websocketpp::frame::opcode::text);
            ws_socket_.send(al_hdl_, parsedData, websocketpp::frame::opcode::text);
        }
        
        if(isLogged){
            BOOST_LOG_TRIVIAL(debug) << "Sent : " << parsedData;
        }
    }
}


/**
 * Check whether client is connected
 *
 */

bool websocket_server::isClientConnected(){
    return clientConnected;
}
