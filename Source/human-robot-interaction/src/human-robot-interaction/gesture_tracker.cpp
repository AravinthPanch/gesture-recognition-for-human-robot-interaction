/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 28/12/14.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include <iostream>
#include <boost/log/trivial.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
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
            if (gestures[i].isComplete() && server_->isConnected())
            {
                nite::HandId newId;
                BOOST_LOG_TRIVIAL(info) << "Gesture type " << gestures[i].getType();
                boost::shared_ptr<std::string> message(new std::string ("{ type : " + boost::lexical_cast<std::string>(gestures[i].getType()) + " }" ));
                server_->send(message);
            }
        }
    }
}

void gesture_tracker::run(){
    init_nite();
    track_gestures();
}
