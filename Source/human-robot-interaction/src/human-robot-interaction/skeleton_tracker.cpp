/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 29/12/14.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include <iostream>
#include <boost/log/trivial.hpp>
#include "NiTE.h"
#include "skeleton_tracker.h"

skeleton_tracker::skeleton_tracker(udp_server *server){
    server_ = server;
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
    
    niteRc = userTracker.create();
    if (niteRc != nite::STATUS_OK)
    {
        BOOST_LOG_TRIVIAL(error) << "Couldn't create user tracker" ;
    }
    else
    {
        BOOST_LOG_TRIVIAL(info) << "User tracker created" ;
    }
}



void print_status(std::string message, int userId){
    BOOST_LOG_TRIVIAL(info) << "User " << userId << " : " << message ;
}

#define MAX_USERS 10
void skeleton_tracker::update_user_state(const nite::UserData& user)
{
    bool g_visibleUsers[MAX_USERS] = {false};
    nite::SkeletonState g_skeletonStates[MAX_USERS] = {nite::SKELETON_NONE};
    
    if (user.isNew()){
        print_status("New", user.getId());
    }else if (user.isVisible() && !g_visibleUsers[user.getId()]){
        print_status("Visible", user.getId());
    }else if (!user.isVisible() && g_visibleUsers[user.getId()]){
        print_status("Out of Scene", user.getId());
    }else if (user.isLost()){
        print_status("Lost", user.getId());
        g_visibleUsers[user.getId()] = user.isVisible();
    }
    
    
    //    if(g_skeletonStates[user.getId()] != user.getSkeleton().getState())
    //    {
    //        switch(g_skeletonStates[user.getId()] = user.getSkeleton().getState())
    //        {
    //            case nite::SKELETON_NONE:
    //                print_status("Stopped tracking.", user.getId());
    //                break;
    //            case nite::SKELETON_CALIBRATING:
    //                print_status("Calibrating", user.getId());
    //                break;
    //            case nite::SKELETON_TRACKED:
    //                print_status("Tracking", user.getId());
    //                break;
    //            case nite::SKELETON_CALIBRATION_ERROR_TORSO:
    //                print_status("Calibration Failed", user.getId());
    //                break;
    //        }
    //    }
}

void skeleton_tracker::track_skeleton(){
    nite::UserTrackerFrameRef userTrackerFrame;
    for(;;)
    {
        niteRc = userTracker.readFrame(&userTrackerFrame);
        if (niteRc != nite::STATUS_OK)
        {
            printf("Get next frame failed\n");
            continue;
        }
        
        const nite::Array<nite::UserData>& users = userTrackerFrame.getUsers();
        for (int i = 0; i < users.getSize(); ++i)
        {
            const nite::UserData& user = users[i];
            
            if (user.isNew())
            {
                userTracker.startSkeletonTracking(user.getId());
                print_status("New User", user.getId());
            }
            else if (user.getSkeleton().getState() == nite::SKELETON_TRACKED)
            {
                const nite::SkeletonJoint& head = user.getSkeleton().getJoint(nite::JOINT_HEAD);
                if (head.getPositionConfidence() > .5){
                    printf("%d. (%5.2f, %5.2f, %5.2f)\n", user.getId(), head.getPosition().x, head.getPosition().y, head.getPosition().z);
                }
            }
        }
    }
}

void skeleton_tracker::run(){
    init_nite();
    track_skeleton();
}

