/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 22/12/14.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include <iostream>
#include <boost/asio.hpp>
#include "udp_server.h"

int main(){
    
    try
    {
        
        boost::asio::io_service io_service;
        udp_server server(io_service);
        io_service.run();
        
    }
    
    catch (std::exception& e)
    {
        
        std::cerr << e.what() << std::endl;
        
    }
    
    return 0;
}

