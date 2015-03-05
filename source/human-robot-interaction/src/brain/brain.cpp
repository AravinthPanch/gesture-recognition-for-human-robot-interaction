/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 04/03/15.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include "brain.h"

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