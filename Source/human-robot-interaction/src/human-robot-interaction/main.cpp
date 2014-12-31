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

#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


using boost::property_tree::ptree;
using boost::property_tree::write_json;
void helper(){
    ptree pt;
    pt.put ("foo", 12.5f);
    std::ostringstream buf;
    write_json (buf, pt, false);
    std::string json = buf.str();
    std::cout << json;
}


int main(int argc, char* argv[])
{
    try
    {
        boost::asio::io_service io_service;
        
        std::cout << "Do you want to start server or client? " << std::endl ;
        std::string argument;
        std::getline(std::cin, argument);
        
        if(argument == "server hand")
        {
            BOOST_LOG_TRIVIAL(info) << "Starting UDP Server with Gesture Tracking";
            udp_server server(io_service);
            boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service));
            gesture_tracker gestureTracker(&server);
            gestureTracker.run();
        }
        else if(argument == "server user")
        {
            BOOST_LOG_TRIVIAL(info) << "Starting UDP Server with Skeleton Tracking";
            udp_server server(io_service);
            boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service));
            skeleton_tracker skeletonTracker(&server);
            skeletonTracker.run();
        }
        else if(argument == "client")
        {
            BOOST_LOG_TRIVIAL(info) << "Starting UDP Client";
            udp_client client(io_service);
            boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service));
            std::getline(std::cin, argument);
        }
        else{
            BOOST_LOG_TRIVIAL(info) << "Invalid selection. Enter server or client" ;
            helper();
        }
    }
    
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}

