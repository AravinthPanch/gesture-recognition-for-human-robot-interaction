/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 22/12/14.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include "udp_server.h"
#include "skeleton_tracker.h"


int main(){
    
    try
    {
        boost::asio::io_service io_service;
        udp_server server(io_service);
        boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service));

        skeleton_tracker tracker(&server);
    }
    
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}

