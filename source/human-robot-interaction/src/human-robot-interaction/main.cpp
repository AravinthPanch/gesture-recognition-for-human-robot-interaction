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
#include <boost/log/trivial.hpp>
#include "udp_server.h"
#include "udp_client.h"
#include "gesture_tracker.h"
#include "skeleton_tracker.h"
#include "setup.h"


void helper(){
    int serverPort = 0;
    serverPort= getConfigValue<int>("serverPort");
    std::cout<<" serverPort:"<<serverPort;
}

int main(int argc, char* argv[])
{
    try
    {
        std::cout << "================ Gesture Recognition For Human-Robot Interaction ================ \n";
        std::cout << "================ Author: Aravinth Panchadcharam <me@aravinth.info> ============== \n" <<std::endl;
        
        boost::asio::io_service io_service;
        std::string argument;
        
        std::cout << "Press \n 1 -> Gesture Tracker \n 2 -> Skeleton Tracker \n 3 -> Client \n: ";
        std::getline(std::cin, argument);
        
        if(argument == "1")
        {
            BOOST_LOG_TRIVIAL(info) << "Starting UDP Server with Hand Gesture Tracking";
            udp_server server(io_service);
            boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service));
            gesture_tracker gestureTracker(&server);
            gestureTracker.run();
        }
        else if(argument == "2")
        {
            BOOST_LOG_TRIVIAL(info) << "Starting UDP Server with Skeleton Tracking";
            udp_server server(io_service);
            boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service));
            skeleton_tracker skeletonTracker(&server);
            skeletonTracker.run();
        }
        else if(argument == "3")
        {
            BOOST_LOG_TRIVIAL(info) << "Starting UDP Client";
            udp_client client(io_service);
            boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service));
            std::getline(std::cin, argument);
        }
        else{
            BOOST_LOG_TRIVIAL(info) << "Invalid selection. Enter server or client" ;
            std::cout << "Enter server or server sekel or client " << std::endl ;
            helper();
        }
    }
    
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}

