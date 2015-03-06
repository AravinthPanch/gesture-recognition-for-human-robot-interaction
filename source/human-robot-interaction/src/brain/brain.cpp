/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 04/03/15.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include "brain.h"
#include <boost/log/trivial.hpp>


/**
 *
 * Constructor
 *
 */
brain::brain(){
    trainingModeActive = false;
    predictionModeActive = false;
    trainingClassLabel = 1;
    
    anbc.enableNullRejection(true);
    anbc.setNullRejectionCoeff(5);
    pipeline.setClassifier( anbc );
}


bool brain::isPredictionModeActive(){
    return predictionModeActive;
}


bool brain::isTrainingModeActive(){
    return trainingModeActive;
}

/**
 *
 *
 *
 */
bool brain::setPredictionModeActive(){
    predictionModeActive = true;
    trainingModeActive = false;
    
    return true;
    
    //    if(pipeline.loadPipelineFromFile(HRI_PIPELINE) ){
    //        BOOST_LOG_TRIVIAL(debug) << "Pipeline loaded from file " << HRI_PIPELINE ;
    //    trainPipeline();
    //        return true;
    //    }
    //    else{
    //        BOOST_LOG_TRIVIAL(error) << "Failed to load Pipeline from file " << HRI_PIPELINE ;
    //        return false;
    //    };
    
    
}



/**
 *
 *
 *
 */
bool brain::setTrainingModeActive(){
    predictionModeActive = false;
    trainingModeActive = true;
    brain::startTraining();
    return true;
}



/**
 *
 * Initiates the training data with given dimension and starts the training timer with given prepartion time and recording time.
 * training timer starts immediately with preparation.
 */
bool brain::startTraining(){
    trainingData.setNumDimensions(SAMPLE_DIMENSION);
    trainingTimer.startRecording(DEFAULT_PREP_TIME, DEFAULT_RECORD_TIME);
    return true;
}


/**
 *
 * Initiates the training data with given dimension and starts the training timer with prepartion time and recording time.
 *
 */
bool brain::stopTraining(){
    trainingTimer.stopRecording();
    return true;
}


/**
 *
 * Initiates the training data with given dimension and starts the training timer with prepartion time and recording time.
 *
 */
UINT brain::trainNext(){
    trainingClassLabel++;
    BOOST_LOG_TRIVIAL(debug) << "Traingin Class Label" << trainingClassLabel;
    return trainingClassLabel;
}


/**
 *
 * It receives the handVector and adds them to the trainingData with given class label.
 *
 */
int brain::train(vector< double > leftHand, vector< double > rightHand){
    vector< double > inputVector(SAMPLE_DIMENSION);
    inputVector[0] = leftHand[0];
    inputVector[1] = leftHand[1];
    inputVector[2] = leftHand[2];
    
    if(trainingTimer.getInRecordingMode()){
        trainingData.addSample(trainingClassLabel, inputVector);
        BOOST_LOG_TRIVIAL(debug) << "Training Class Label " << trainingClassLabel << " with Input Vector " << leftHand[0] << " , " << leftHand[1] << " , " << leftHand[2];
        return 0;
    }
    else if(trainingTimer.getRecordingStopped()){
        BOOST_LOG_TRIVIAL(debug) << "Training timer stopped";
        return 1;
    }
    else{
        BOOST_LOG_TRIVIAL(debug) << "Error in training";
        return 2;
    }
}



/**
 *
 * It predicts the incoming handVector and returns the identified class label and likelyhood.
 *
 */
bool brain::trainPipeline(){
    if( pipeline.train( trainingData ) ){
        BOOST_LOG_TRIVIAL(info) << "Pipeline Trained";
        return true;
    }
    else {
        BOOST_LOG_TRIVIAL(error) <<  "Failed to train pipeline";
        return false;
    }
}


/**
 *
 * It predicts the incoming handVector and returns the identified class label and likelyhood.
 *
 */
string brain::predict(vector< double > leftHand, vector< double > rightHand){
    BOOST_LOG_TRIVIAL(info) << "Left Hand " << leftHand[0] << leftHand[1] << leftHand[2] << leftHand.size() ;
    
    vector< double > inputVector(SAMPLE_DIMENSION);
    inputVector[0] = leftHand[0];
    inputVector[1] = leftHand[1];
    inputVector[2] = leftHand[2];
    
    pipeline.predict(inputVector);
    UINT predictedClassLabel = pipeline.getPredictedClassLabel();
    double maxLikelihood =  pipeline.getMaximumLikelihood();
    
    return "hola";
}

