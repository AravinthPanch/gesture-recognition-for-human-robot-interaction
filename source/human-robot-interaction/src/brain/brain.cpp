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
    anbc.enableNullRejection(true);
    anbc.setNullRejectionCoeff(5);
    pipeline.setClassifier( anbc );
}

void brain::train(){
    trainingData.setNumDimensions( 6 );
    trainingModeActive = false;
    predictionModeActive = false;
    trainingClassLabel = 1;
}

UINT brain::predict(vector< double > leftHand, vector< double > rightHand){
    BOOST_LOG_TRIVIAL(info) << "Left Hand " << leftHand[0] << leftHand[1] << leftHand[2] ;
    BOOST_LOG_TRIVIAL(info) << "Right Hand " << rightHand[0] << rightHand[1] << rightHand[2];
    UINT classLabel = 1;
    return classLabel;
}