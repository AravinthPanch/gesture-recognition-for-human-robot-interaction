/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 28/12/14.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include <iostream>
#include <sstream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "NiTE.h"
#include "utils.h"


nite::HandTracker handTracker;
nite::Status niteRc;

void init_nite(){
    niteRc = nite::NiTE::initialize();
    if (niteRc != nite::STATUS_OK)
    {
        std::cout << "NiTE initialization failed" << std::endl;
    }
    else
    {
        std::cout << "NiTE initialized" << std::endl;
    }
    
    niteRc = handTracker.create();
    if (niteRc != nite::STATUS_OK)
    {
        std::cout << "Couldn't create hand tracker" << std::endl;
    }
    else
    {
        std::cout << "Hand tracker created" << std::endl;
    }
    
    handTracker.startGestureDetection(nite::GESTURE_WAVE);
    handTracker.startGestureDetection(nite::GESTURE_CLICK);
    std::cout << "Wave your hand to locate it" << std::endl;
}



using boost::property_tree::ptree;
using boost::property_tree::write_json;

void send_gesture(const nite::GestureData& gesture){
    
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
    
    std::cout << gesture_buffer.str() << std::endl;
}



void send_hand(const nite::HandData& hand){
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
    
    std::cout << hand_buffer.str() << std::endl;
}



void track_hand(){
    
    nite::HandTrackerFrameRef handTrackerFrame;
    
    while (!utils::wasKeyboardHit())
    {
        niteRc = handTracker.readFrame(&handTrackerFrame);
        if (niteRc != nite::STATUS_OK)
        {
            std::cout << "Get next frame failed" << std::endl;
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
    
    nite::NiTE::shutdown();
}


int main(int argc, char* argv[])
{
    try
    {
        init_nite();
        track_hand();
    }
    
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}



