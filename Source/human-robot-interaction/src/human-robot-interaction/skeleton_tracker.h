/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 28/12/14.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#ifndef __human_robot_interaction__skeleton_tracker__
#define __human_robot_interaction__skeleton_tracker__

#include <stdio.h>
#include "NiTE.h"
#include "udp_server.h"

class skeleton_tracker{
    
private:
    nite::HandTracker handTracker;
    nite::Status niteRc;
    udp_server *server_;
    
    void init_nite();
    void start_gesture_detection();
    
public:
    skeleton_tracker(udp_server *server);
    void track_gestures();
    void test();
};

#endif
