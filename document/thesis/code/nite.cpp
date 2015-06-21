#include <iostream>
#include "NiTE.h"

int main(){
    nite::HandTracker handTracker;
    nite::NiTE::initialize();
    handTracker.create();    
    handTracker.startGestureDetection(nite::GESTURE_WAVE);
    handTracker.startGestureDetection(nite::GESTURE_CLICK);
    nite::HandTrackerFrameRef handTrackerFrame;
    
    while (true)
    {
        handTracker.readFrame(&handTrackerFrame);
        const nite::Array<nite::GestureData>& gestures = handTrackerFrame.getGestures();
        
        for (int i = 0; i < gestures.getSize(); ++i)
        {
            if (gestures[i].isComplete())
            {
                printf ("Gesture Type %d \n", gestures[i].getType());

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
                printf ("Hand at x : %f, y : %f, z : %f \n", hand.getPosition().x, hand.getPosition().y, hand.getPosition().z);
            }
        }        
    }
    
    nite::NiTE::shutdown();

    return 0;
}






