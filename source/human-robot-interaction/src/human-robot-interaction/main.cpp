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
}

int main(int argc, char* argv[])
{
    try
    {
        std::cout << "================ Gesture Recognition For Human-Robot Interaction ================ \n";
        std::cout << "================ Author: Aravinth Panchadcharam <me@aravinth.info> ============== \n" <<std::endl;
        
        boost::asio::io_service io_service;
        std::string argument;
        bool optionSelected = false;
        
        std::cout << "Press \n 1 -> Gesture Tracker \n 2 -> Skeleton Tracker \n 3 -> Client \n 4 -> Exit \n: ";
        std::getline(std::cin, argument);
        
        while (!optionSelected) {
            if(argument == "1")
            {
                optionSelected = true;
                BOOST_LOG_TRIVIAL(info) << "Starting Hand Gesture Tracking";
                udp_server server(io_service);
                boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service));
                gesture_tracker gestureTracker(&server);
                gestureTracker.run();
            }
            else if(argument == "2")
            {
                optionSelected = true;
                BOOST_LOG_TRIVIAL(info) << "Starting Skeleton Tracking";
                udp_server server(io_service);
                boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service));
                skeleton_tracker skeletonTracker(&server);
                skeletonTracker.run();
            }
            else if(argument == "3")
            {
                optionSelected = true;
                BOOST_LOG_TRIVIAL(info) << "Starting UDP Client";
                udp_client client(io_service);
                io_service.run();
            }
            else if(argument == "4")
            {
                optionSelected = true;
                BOOST_LOG_TRIVIAL(info) << "Exiting Gesture Recognition For Human-Robot Interaction";
                return 0;
            }
            else{
                optionSelected = false;
                BOOST_LOG_TRIVIAL(info) << "Invalid selection." ;
                std::cout << "Press \n 1 -> Gesture Tracker \n 2 -> Skeleton Tracker \n 3 -> Client \n 4 -> Exit \n: ";
                std::getline(std::cin, argument);
            }
        }
        
    }
    
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}

