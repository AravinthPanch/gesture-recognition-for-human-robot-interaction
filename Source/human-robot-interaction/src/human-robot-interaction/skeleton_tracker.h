/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 29/12/14.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#ifndef __human_robot_interaction__skeleton_tracker__
#define __human_robot_interaction__skeleton_tracker__

#include "NiTE.h"
#include "udp_server.h"
#include "utils.h"

class skeleton_tracker
{
private:
    nite::UserTracker userTracker;
    nite::Status niteRc;
    udp_server *server_;
    
    void init_nite();
    void track_skeleton();
    void display_user_status(const nite::UserData& user);
    
public:
    skeleton_tracker(udp_server *server);
    void run();
    void send_skeleton(const nite::UserData& user, int frameId);
};

#endif
