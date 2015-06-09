/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 28/12/14.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#ifndef __human_robot_interaction__gesture_tracker__
#define __human_robot_interaction__gesture_tracker__

#include <stdio.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "NiTE.h"
#include "udp_server.h"
#include "utils.h"

class gesture_tracker
{
private:
    nite::HandTracker handTracker;
    nite::Status niteRc;
    udp_server *server_;
    
    int leftHand;
    int rightHand;
    int lastLostHand;
    int handsSize;
    
    void init_nite();
    void track_gestures();
    void send_gesture(const nite::GestureData& gesture);
    void send_hand(const nite::HandData& hand);
    void send_hand(const nite::HandData& hand1, const nite::HandData& hand2);
    std::string getHandName(int handId);
    boost::property_tree::ptree parseToJSON(const nite::HandData& hand);
    void send_info(std::string info);
    
public:
    gesture_tracker(udp_server *server);
    void run();
    
};

#endif
