/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 04/03/15.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/log/trivial.hpp>
#include "udp_client.h"


void helper(){
}

int main(int argc, char* argv[])
{
    try
    {
        
        boost::asio::io_service io_service;
        
        BOOST_LOG_TRIVIAL(info) << "Starting Brain Module";
        udp_client client(io_service);
        boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service));
        
        std::string argument;
        std::getline(std::cin, argument);
        
        
        //        helper();
        
    }
    
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}

