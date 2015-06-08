#include <websocketpp/config/asio_no_tls_client.hpp>

#include <websocketpp/client.hpp>

#include <iostream>
#include <boost/log/trivial.hpp>

typedef websocketpp::client<websocketpp::config::asio_client> client;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

void on_message(client* c, websocketpp::connection_hdl hdl, message_ptr msg) {
    BOOST_LOG_TRIVIAL(info) << "Message" << msg->get_payload();
}

void on_open(client* c, websocketpp::connection_hdl hdl) {
    BOOST_LOG_TRIVIAL(info) << "open";
    c->send(hdl, "Hoola", websocketpp::frame::opcode::text);
}


int main(int argc, char* argv[]) {
    
    BOOST_LOG_TRIVIAL(info) << "started";
    
    client c;
    std::string uri = "ws://localhost:9002";
    
    try {
        c.set_access_channels(websocketpp::log::alevel::none);
        //        c.set_access_channels(websocketpp::log::alevel::message_payload);
        
        // Initialize ASIO
        c.init_asio();
        
        c.set_open_handler(bind(&on_open,&c,::_1));
        c.set_message_handler(bind(&on_message,&c,::_1,::_2));
        
        websocketpp::lib::error_code ec;
        client::connection_ptr con = c.get_connection(uri, ec);
        
        c.connect(con);
        
        c.run();
        
        std::cout << "done" << std::endl;
        
    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    }
}