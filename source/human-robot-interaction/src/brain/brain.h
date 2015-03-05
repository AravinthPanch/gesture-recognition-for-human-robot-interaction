/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 04/03/15.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#ifndef __human_robot_interaction__brain__
#define __human_robot_interaction__brain__

#include <stdio.h>
#include "GRT.h"

using namespace GRT;

class brain
{
    
private:
    vector< double > leftHand;
    vector< double > rightHand;
    
    GestureRecognitionPipeline pipeline;
    ANBC anbc;
    vector< UINT > classLabels;
    
    
    ClassificationData testData;
    
    
    ClassificationData trainingData;
    TrainingDataRecordingTimer trainingTimer;
    bool trainingModeActive;
    bool predictionModeActive;
    UINT trainingClassLabel;
    
public:
    brain();
    void train();
    UINT predict(vector< double > leftHand, vector< double > rightHand);
    
};


#endif
