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
#define HRI_TRAINING_DATASET "hri-training-dataset.txt"

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
    
    
    void saveTrainingDataSetToFile();
    void trainPipelineFromTrainingData();
    void startTraining();
    void stopTraining();
    
    
public:
    brain();
    
    void setPredictionModeActive();
    void setTrainingModeActive();
    bool isPredictionModeActive();
    bool isTrainingModeActive();
    
    void train(vector< double > leftHand, vector< double > rightHand);
    void trainNext();
    
    string predict(vector< double > leftHand, vector< double > rightHand);
    
};


#endif
