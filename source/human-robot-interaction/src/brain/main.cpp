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


#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

void helper(){
    
    // 1. Parse a JSON string into DOM.
    const char* json = "{\"HAND\": [\"1\", \"-79.65819\", \"47.94268\", \"935.5719\"]}";
    Document d;
    d.Parse(json);
    
    // 2. Modify it by DOM.
    Value& b = d["HAND"];
    
    
    for (SizeType i = 0; i < b.Size(); i++)
    {
        const Value& c = b[i];
        printf("%s \n",c.GetString());
    }
    
}

int main(int argc, char* argv[])
{
    try
    {
        //                std::string argument;
        //        boost::asio::io_service io_service;
        //
        //        BOOST_LOG_TRIVIAL(info) << "Starting Brain Module";
        //        udp_client client(io_service);
        //        boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service));
        //
        //        std::getline(std::cin, argument);
        
        
        helper();
        
    }
    
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}

