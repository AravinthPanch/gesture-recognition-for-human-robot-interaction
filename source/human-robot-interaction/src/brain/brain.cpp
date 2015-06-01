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
    
    trainingData.setNumDimensions(SAMPLE_DIMENSION);
}


/**
 *
 * Check whether predictionMode is active
 *
 */
bool brain::isPredictionModeActive(){
    return predictionModeActive;
}


/**
 *
 * Check whether traingMode is Active
 *
 */
bool brain::isTrainingModeActive(){
    return trainingModeActive;
}


/**
 *
 * Set predictionMode active and load the training data from dataset. If training dataset is not found, then throws an error.
 *
 */
void brain::setPredictionModeActive(){
    predictionModeActive = true;
    trainingModeActive = false;
    
    if(trainingData.loadDatasetFromFile(HRI_TRAINING_DATASET) ){
        BOOST_LOG_TRIVIAL(info) << "Training Data Loaded From File";
    }
    else{
        BOOST_LOG_TRIVIAL(error) << "Failed To Load Training Data From File";
    };
    
    trainPipelineFromTrainingData();
}


/**
 *
 * Set trainingMode active and start the training.
 *
 */
void brain::setTrainingModeActive(){
    predictionModeActive = false;
    trainingModeActive = true;
    brain::startTraining();
}


/**
 *
 * Initiates the training data with given dimension and starts the training timer with given prepartion time and recording time.
 * training timer starts immediately with preparation.
 */
void brain::startTraining(){
    if(trainingTimer.startRecording(DEFAULT_PREP_TIME, DEFAULT_RECORD_TIME)){
        BOOST_LOG_TRIVIAL(debug) << "Training Timer Started";
    }
    else{
        BOOST_LOG_TRIVIAL(error) << "Failed To Start Training Timer";
    };
}


/**
 *
 * Stop the recording of training. Recording stops automatically with default record time.
 *
 */
void brain::stopTraining(){
    if(trainingTimer.stopRecording()){
        BOOST_LOG_TRIVIAL(debug) << "Training Timer Stopped";
    }
    else{
        BOOST_LOG_TRIVIAL(error) << "Failed To Stop Training Timer";
    };
}


/**
 *
 * Increase the classlabel
 *
 */
void brain::trainNext(){
    trainingClassLabel++;
    BOOST_LOG_TRIVIAL(debug) << "New Training Class Label Is " << trainingClassLabel;
}


/**
 *
 * Save the training data to a file
 *
 */
void brain::saveTrainingDataSetToFile(){
    if(trainingData.saveDatasetToFile(HRI_TRAINING_DATASET)){
        BOOST_LOG_TRIVIAL(debug) << "Training Data Saved To File";
    }
    else{
        BOOST_LOG_TRIVIAL(error) << "Failed To Save Training Data To File";
    };
}


/**
 *
 * Train the pipeline using training data. Training data must be loaded from file if it is prediction mode.
 *
 */
void brain::trainPipelineFromTrainingData(){
    if( pipeline.train( trainingData ) ){
        BOOST_LOG_TRIVIAL(info) << "Pipeline Trained";
    }
    else {
        BOOST_LOG_TRIVIAL(error) <<  "Failed To Train Pipeline";
    }
}


/**
 *
 * It receives the handVector and adds them to the trainingData with given class label.
 *
 */
void brain::train(vector< double > leftHand, vector< double > rightHand){
    vector< double > inputVector(SAMPLE_DIMENSION);
    inputVector[0] = leftHand[0];
    inputVector[1] = leftHand[1];
    inputVector[2] = leftHand[2];
    
    if(trainingTimer.getInRecordingMode()){
        trainingData.addSample(trainingClassLabel, inputVector);
        BOOST_LOG_TRIVIAL(debug) << "Training Class Label " << trainingClassLabel << " With Sample " << leftHand[0] << " , " << leftHand[1] << " , " << leftHand[2];
        BOOST_LOG_TRIVIAL(debug) << "Timer" << trainingTimer.getSeconds();
    }
    else if(trainingTimer.getRecordingStopped()){
        BOOST_LOG_TRIVIAL(debug) << "Training Timer Stopped";
        saveTrainingDataSetToFile();
        trainPipelineFromTrainingData();
        trainingModeActive = false;
    }
    else if(trainingTimer.getInPrepMode()){
        BOOST_LOG_TRIVIAL(debug) << "Training Timer In Preparation Mode";
    }
    else {
        BOOST_LOG_TRIVIAL(debug) << "Error In Training";
    }
}


/**
 *
 * It predicts the incoming handVector and returns the identified class label and likelyhood.
 *
 */
vector<double> brain::predict(vector< double > leftHand, vector< double > rightHand){
    //    BOOST_LOG_TRIVIAL(info) << "Left Hand " << leftHand[0] <<", " << leftHand[1] <<", " << leftHand[2] <<", " << leftHand.size() ;
    
    vector<double> inputVector(SAMPLE_DIMENSION);
    inputVector[0] = leftHand[0];
    inputVector[1] = leftHand[1];
    inputVector[2] = leftHand[2];
    
    pipeline.predict(inputVector);
    UINT predictedClassLabel = pipeline.getPredictedClassLabel();
    double maxLikelihood =  pipeline.getMaximumLikelihood();
    
    vector<double> result(2);
    result[0] = maxLikelihood;
    result[1] = double(predictedClassLabel);
    
    return result;
}

