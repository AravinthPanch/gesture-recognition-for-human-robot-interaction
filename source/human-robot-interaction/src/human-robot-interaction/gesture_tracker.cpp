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
#include "NiTE.h"
#include "gesture_tracker.h"

using boost::property_tree::ptree;
using boost::property_tree::write_json;

/**
 *
 * Constructor
 *
 */
gesture_tracker::gesture_tracker(udp_server *server){
    server_ = server;
}


/**
 *
 * Initializes NiTE and takes available OpenNI device
 * NiTE::initialize() takes OpenNI deviceId as argument, if there ar many
 * Wave and Click Gestures are initiated
 *
 */
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
    
    // Check for OpenNI device and start hand tracker.
    niteRc = handTracker.create();
    if (niteRc != nite::STATUS_OK)
    {
        BOOST_LOG_TRIVIAL(error) << "Couldn't create hand tracker" ;
    }
    else
    {
        BOOST_LOG_TRIVIAL(info) << "Hand tracker created" ;
    }
    
    handTracker.setSmoothingFactor(0.1);
    handTracker.startGestureDetection(nite::GESTURE_WAVE);
    handTracker.startGestureDetection(nite::GESTURE_CLICK);
    BOOST_LOG_TRIVIAL(info) << "Wave your hand to start the hand tracking" ;
}


/**
 *
 * Serializes gesture data with position of hand at which gesture was detected
 * Send it to the connected client
 *
 */
void gesture_tracker::send_gesture(const nite::GestureData& gesture){
    
    std::string gestureJson;
    if(gesture.getType() == 0){
        gestureJson = "{\"GESTURE\":\"WAVE\"}";
    }else if (gesture.getType() == 1){
        gestureJson = "{\"GESTURE\":\"CLICK\"}";
    }
    
    boost::shared_ptr<std::string> message(new std::string(gestureJson));
    server_->send(message);
}


void gesture_tracker::send_info(std::string info){
    
    std::stringstream infoBuffer;
    infoBuffer << "{\"INFO\":\"" << info << "\"}";
    
    boost::shared_ptr<std::string> message(new std::string(infoBuffer.str()));
    server_->send(message);
}



/**
 *
 * Serializes hand data with position and hand id
 * Send it to the connected client
 *
 */
ptree gesture_tracker::parseToJSON(const nite::HandData& hand){
    
    // keys and values for json array
    ptree joint_array, xAxis, yAxis, zAxis;
    
    xAxis.put("", hand.getPosition().x);
    yAxis.put("", hand.getPosition().y);
    zAxis.put("", hand.getPosition().z);
    
    // Make an array of hand joint for x,y,z axes
    joint_array.push_back(std::make_pair("", xAxis));
    joint_array.push_back(std::make_pair("", yAxis));
    joint_array.push_back(std::make_pair("", zAxis));
    
    return joint_array;
}


/**
 *
 * Serializes hand data with position and hand id
 * Send it to the connected client
 *
 */
void gesture_tracker::send_hand(const nite::HandData& hand){
    
    ptree handJson;
    std::string handName = getHandName(hand.getId());
    
    if(!handName.empty())
    {
        // Parse it json array and add to object
        handJson.add_child(handName, parseToJSON(hand));
        
        // Stringify the ptree
        std::ostringstream hand_buffer;
        write_json (hand_buffer, handJson, false);
        boost::shared_ptr<std::string> message(new std::string( hand_buffer.str()));
        
        server_->send(message);
    }
}


/**
 *
 * Serializes hand data with position and hand id
 * Send it to the connected client
 *
 */
void gesture_tracker::send_hand(const nite::HandData& hand1, const nite::HandData& hand2){
    
    ptree handJson;
    std::string handName1 = getHandName(hand1.getId());
    std::string handName2 = getHandName(hand2.getId());
    
    if(!handName1.empty() && !handName2.empty())
    {
        // Parse it json array and add to object
        handJson.add_child(handName1, parseToJSON(hand1));
        handJson.add_child(handName2, parseToJSON(hand2));
        
        // Stringify the ptree
        std::ostringstream hand_buffer;
        write_json (hand_buffer, handJson, false);
        boost::shared_ptr<std::string> message(new std::string( hand_buffer.str()));
        
        server_->send(message);
    }
}


/**
 *
 *
 * Finds the hand name based on given handId
 *
 */

std::string gesture_tracker::getHandName(int handId){
    std::string handName;
    
    if(handId == leftHand){
        handName = "LEFT";
    }
    else if(handId == rightHand){
        handName = "RIGHT";
    }
    
    return handName;
}


/**
 *
 * Starts Gesture recognition and Hand tracking based on the position of Hand found by WAVE gesture
 * It tracks it till there is a keyboard ESC Hit and stops
 *
 */
void gesture_tracker::track_gestures(){
    
    nite::HandTrackerFrameRef handTrackerFrame;
    
    while (!utils::wasKeyboardHit())
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
                
                // Dont track more than 2 hands. handTrackerFrame.getHands().getSize() sometime goes to 3 even though
                // there are 2 active hands
                if(gestures[i].getType() == 0){
                    handTracker.startHandTracking(gestures[i].getCurrentPosition(), &newId);
                }
            }
        }
        
        const nite::Array<nite::HandData>& hands = handTrackerFrame.getHands();
        
        // hands.getSize() gives the number of active hands, but handId increases
        // hands.getSize() = 0 and goes to hands.getSize() = 2, when there is a new hand detected
        // hands.getSize() = 0, this happens for a fraction of second when tacking is troubled
        for (int i = 0; i < hands.getSize(); ++i)
        {
            // Get Hand data
            const nite::HandData& hand = hands[i];
            
            // If hand is lost, update the losthandid
            if(!hand.isTracking())
            {
                lastLostHand = hand.getId();
                BOOST_LOG_TRIVIAL(info) << getHandName(hand.getId()) << " Hand with id " << hand.getId() << " is Lost";
                
                send_info( getHandName(hand.getId()) + " Hand is lost");
                
                // When there is no active hands, reset all the values
                // Last active hand
                if(hands.getSize() == 1){
                    leftHand = 0;
                    rightHand = 0;
                    lastLostHand = 0;
                    handsSize = 0;
                }
            }
            
            // If new hand is found
            if(hand.isNew()){
                BOOST_LOG_TRIVIAL(info) << "Found new hand with id " << hand.getId();
                
                handsSize++;
                
                // Check if it is a hand for the first time or second time
                if(handsSize == 1 && lastLostHand == 0){
                    BOOST_LOG_TRIVIAL(debug) << "First hand is found";
                    rightHand = hand.getId();
                }
                else if (handsSize == 2 && lastLostHand == 0){
                    BOOST_LOG_TRIVIAL(debug) << "Second hand is found";
                    leftHand = hand.getId();
                }
                // If a hand was lost and a hand is active, then update the appropriate id to left or right hand
                else if(handsSize > 2 && lastLostHand > 0){
                    if(lastLostHand == leftHand){
                        leftHand = hand.getId();
                    }else if(lastLostHand == rightHand){
                        rightHand = hand.getId();
                    }
                }
                
                send_info( getHandName(hand.getId()) + " Hand is new");
            }
            
        }
        
        if(hands.getSize() == 2 && hands[0].isTracking() && !hands[0].isNew() && hands[1].isTracking() && !hands[1].isNew()){
            send_hand(hands[0], hands[1]);
        }
        else if(hands.getSize() == 1 && hands[0].isTracking() && !hands[0].isNew()){
            send_hand(hands[0]);
        }
        
    }
    
    nite::NiTE::shutdown();
}


/**
 *
 * Called by the main thread and Boost ioService keeps it in the loop
 *
 */
void gesture_tracker::run(){
    init_nite();
    track_gestures();
}
