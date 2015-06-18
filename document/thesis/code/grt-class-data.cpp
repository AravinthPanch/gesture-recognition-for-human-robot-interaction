#include "GRT.h"
using namespace GRT;

int main (int argc, const char * argv[])
{
    ClassificationData trainingData;

    trainingData.setNumDimensions( 3 );    
    trainingData.setDatasetName("static-hand-gesture");    
    trainingData.setInfoText("Gesture Recognition For Human-Robot Interaction");

    UINT gestureLabel = 1;
    VectorDouble sample(3) = getDataFromSensor();
    trainingData.addSample( gestureLabel, sample );

    trainingData.saveDatasetToFile( "hri-training-dataset.txt" );
    trainingData.loadDatasetFromFile( "hri-training-dataset.txt" );
    
    ClassificationData testData = trainingData.partition( 80 );

    for(UINT i=0; i<trainingData.getNumSamples(); i++)
    {    
        VectorDouble sampleVector = trainingData[i].getSample(); 
       printf("%f, %f, %f \n", sampleVector[0], sampleVector[1], sampleVector[2]);
    }

    trainingData.clear();

    return EXIT_SUCCESS;
}