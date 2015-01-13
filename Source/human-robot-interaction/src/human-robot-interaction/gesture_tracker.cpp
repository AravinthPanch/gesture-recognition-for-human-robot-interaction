/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 28/12/14.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include <iostream>
#include <sstream>
#include <boost/log/trivial.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "NiTE.h"
#include "gesture_tracker.h"


gesture_tracker::gesture_tracker(udp_server *server){
    server_ = server;
}

void gesture_tracker::init_nite(){
    niteRc = nite::NiTE::initialize();
    if (niteRc != nite::STATUS_OK)
    {
        BOOST_LOG_TRIVIAL(error) << "NiTE initialization failed" ;
    }
    else
    {
        BOOST_LOG_TRIVIAL(info) << "NiTE initialized" ;
    }
    
    niteRc = handTracker.create();
    if (niteRc != nite::STATUS_OK)
    {
        BOOST_LOG_TRIVIAL(error) << "Couldn't create hand tracker" ;
    }
    else
    {
        BOOST_LOG_TRIVIAL(info) << "Hand tracker created" ;
    }
    
    handTracker.startGestureDetection(nite::GESTURE_WAVE);
    handTracker.startGestureDetection(nite::GESTURE_CLICK);
    BOOST_LOG_TRIVIAL(info) << "Gesture detection started" ;
}

using boost::property_tree::ptree;
using boost::property_tree::write_json;
void gesture_tracker::send_gesture(const nite::GestureData& gesture){
    ptree gestureJson;
    gestureJson.put("type", gesture.getType());
    
    std::ostringstream gesture_buffer;
    write_json (gesture_buffer, gestureJson, false);
    boost::shared_ptr<std::string> message(new std::string( gesture_buffer.str()));
    
    if(server_->isClientConnected())
    {
        server_->send(message);
    }
    else
    {
        BOOST_LOG_TRIVIAL(debug) << *message;
    }
    
}

void gesture_tracker::track_gestures(){
    
    nite::HandTrackerFrameRef handTrackerFrame;
    
    for(;;)
    {
        niteRc = handTracker.readFrame(&handTrackerFrame);
        if (niteRc != nite::STATUS_OK)
        {
            BOOST_LOG_TRIVIAL(error) << "Get next frame failed";
            continue;
        }
        
        const nite::Array<nite::GestureData>& gestures = handTrackerFrame.getGestures();
        for (int i = 0; i < gestures.getSize(); ++i)
        {
            if (gestures[i].isComplete())
            {
                nite::HandId newId;
                BOOST_LOG_TRIVIAL(info) << "Gesture type " << gestures[i].getType();
                send_gesture(gestures[i]);
            }
        }
    }
}

void gesture_tracker::run(){
    init_nite();
    track_gestures();
}
