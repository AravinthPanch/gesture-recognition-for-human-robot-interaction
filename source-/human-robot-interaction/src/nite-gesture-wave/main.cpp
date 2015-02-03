/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 11/12/14.
 * Contributors:
 */

#include "NiTE.h"
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

enum { max_length = 1024 };
const char* SERVER_PORT = "50005";

using boost::asio::ip::udp;

int main(int argc, char** argv)
{
    try
    {
        
        // Init UDP Server
        boost::asio::io_service io_service;
        short port = std::atoi(SERVER_PORT);
        udp::socket socket(io_service, udp::endpoint(udp::v4(), port));
        std::cout << "NiTE Gesture UDP Server is started at port " << SERVER_PORT << std::endl;
        
        char data[max_length];
        udp::endpoint sender_endpoint;
        socket.receive_from(boost::asio::buffer(data, max_length), sender_endpoint);
        std::cout << "UDP Client is connected from the address " << sender_endpoint <<std::endl;
        
        
        // Init NiTE
        nite::HandTracker handTracker;
        nite::Status niteRc;
        niteRc = nite::NiTE::initialize();
        if (niteRc != nite::STATUS_OK)
        {
            printf("NiTE initialization failed\n");
            return 1;
        }
        
        niteRc = handTracker.create();
        if (niteRc != nite::STATUS_OK)
        {
            printf("Couldn't create user tracker\n");
            return 3;
        }
        
        
        // Init Gesture Detection
        handTracker.startGestureDetection(nite::GESTURE_WAVE);
        handTracker.startGestureDetection(nite::GESTURE_CLICK);
        printf("\nWave or click to start tracking your hand...\n");
        
        
        // Get gesture
        nite::HandTrackerFrameRef handTrackerFrame;
        for(;;)
        {
            niteRc = handTracker.readFrame(&handTrackerFrame);
            if (niteRc != nite::STATUS_OK)
            {
                printf("Get next frame failed\n");
                continue;
            }
            
            const nite::Array<nite::GestureData>& gestures = handTrackerFrame.getGestures();
            for (int i = 0; i < gestures.getSize(); ++i)
            {
                if (gestures[i].isComplete())
                {
                    nite::HandId newId;
                    std::cout << "Gesture type " << gestures[i].getType() <<std::endl;
                    
                    // Stream gesture via UDP
                    std::string gestureType =  "{ type : " + boost::lexical_cast<std::string>(gestures[i].getType()) + " }";
                    strcpy(data, gestureType.c_str());
                    socket.send_to(boost::asio::buffer(data, sizeof(data)), sender_endpoint);
                }
            }
            
        }
        
        
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    
    return 0;
    
}







