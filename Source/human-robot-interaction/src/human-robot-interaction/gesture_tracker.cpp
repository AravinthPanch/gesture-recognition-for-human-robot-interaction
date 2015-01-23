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
#include "utils.h"

using boost::property_tree::ptree;
using boost::property_tree::write_json;

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
    BOOST_LOG_TRIVIAL(info) << "Gesture detection started: Wave your Hand to start the hand tracking" ;
}



void gesture_tracker::send_gesture(const nite::GestureData& gesture){
    ptree gestureJson, gestureType, joint_array, xAxis, yAxis, zAxis, joint_confidence;
    std::string gesture_type;
    
    if(gesture.getType() == 0){
        gesture_type = "WAVE";
    }else if (gesture.getType() == 1){
        gesture_type = "CLICK";
    }
    
    gestureType.put("", gesture_type);
    xAxis.put("", gesture.getCurrentPosition().x);
    yAxis.put("", gesture.getCurrentPosition().y);
    zAxis.put("", gesture.getCurrentPosition().z);
    
    joint_array.push_back(std::make_pair("", gestureType));
    joint_array.push_back(std::make_pair("", xAxis));
    joint_array.push_back(std::make_pair("", yAxis));
    joint_array.push_back(std::make_pair("", zAxis));
    
    gestureJson.add_child("GESTURE", joint_array);
    
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



void gesture_tracker::send_hand(const nite::HandData& hand){
    ptree handJson, handId, joint_array, xAxis, yAxis, zAxis, joint_confidence;
    
    handId.put("", hand.getId());
    xAxis.put("", hand.getPosition().x);
    yAxis.put("", hand.getPosition().y);
    zAxis.put("", hand.getPosition().z);
    
    joint_array.push_back(std::make_pair("", handId));
    joint_array.push_back(std::make_pair("", xAxis));
    joint_array.push_back(std::make_pair("", yAxis));
    joint_array.push_back(std::make_pair("", zAxis));
    
    handJson.add_child("HAND", joint_array);
    
    std::ostringstream hand_buffer;
    write_json (hand_buffer, handJson, false);
    
    boost::shared_ptr<std::string> message(new std::string( hand_buffer.str()));
    
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
    
    while (!wasKeyboardHit())
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
                send_gesture(gestures[i]);
                nite::HandId newId;
                handTracker.startHandTracking(gestures[i].getCurrentPosition(), &newId);
            }
        }
        
        const nite::Array<nite::HandData>& hands = handTrackerFrame.getHands();
        for (int i = 0; i < hands.getSize(); ++i)
        {
            const nite::HandData& hand = hands[i];
            if (hand.isTracking())
            {
                send_hand(hand);
            }
        }
    }
}



void gesture_tracker::run(){
    init_nite();
    track_gestures();
}
