/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 28/12/14.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include "skeleton_tracker.h"
#include "NiTE.h"
#include <iostream>
#include <boost/log/trivial.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>



skeleton_tracker::skeleton_tracker(udp_server *server){
    server_ = server;
    init_nite();
    start_gesture_detection();
    track_gestures();
}

void skeleton_tracker::init_nite(){
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
}

void skeleton_tracker::start_gesture_detection(){
    handTracker.startGestureDetection(nite::GESTURE_WAVE);
    handTracker.startGestureDetection(nite::GESTURE_CLICK);
    BOOST_LOG_TRIVIAL(info) << "Gesture detection started" ;
}


void skeleton_tracker::track_gestures(){
    
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
            }
        }
    }
    
}

void skeleton_tracker::test(){
    server_->testSend(5555);
}
