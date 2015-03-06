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

#define DEFAULT_PREP_TIME 5000
#define DEFAULT_RECORD_TIME 5000
#define SAMPLE_DIMENSION 3
#define HRI_PIPELINE "hri_pipeline"

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
    bool startTraining();
    bool stopTraining();
    int train(vector< double > leftHand, vector< double > rightHand);
    UINT trainNext();
    bool trainPipeline();
    string predict(vector< double > leftHand, vector< double > rightHand);
    
    string incomingData(vector< double > leftHand, vector< double > rightHand);
    
    bool setPredictionModeActive();
    bool setTrainingModeActive();
    bool isPredictionModeActive();
    bool isTrainingModeActive();
    
};


#endif
