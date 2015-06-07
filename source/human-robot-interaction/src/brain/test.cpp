/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 07/06/15.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include "test.h"
#include "GRT.h"

using namespace GRT;

int main (int argc, const char * argv[])
{
    
    //Create a new ANBC instance
    ANBC anbc;
    anbc.setNullRejectionCoeff( 10 );
    anbc.enableScaling( true );
    anbc.enableNullRejection( true );
    
    //Load some training data to train the classifier
    ClassificationData trainingData;
    
    if( !trainingData.loadDatasetFromFile("ANBCTrainingData.txt") ){
        cout << "Failed to load training data!\n";
        return EXIT_FAILURE;
    }
    
    //Use 20% of the training dataset to create a test dataset
    ClassificationData testData = trainingData.partition( 80 );
    
    //Train the classifier
    if( !anbc.train( trainingData ) ){
        cout << "Failed to train classifier!\n";
        return EXIT_FAILURE;
    }
    
    //Save the ANBC model to a file
    if( !anbc.saveModelToFile("ANBCModel.txt") ){
        cout << "Failed to save the classifier model!\n";
        return EXIT_FAILURE;
    }
    
    //Load the ANBC model from a file
    if( !anbc.loadModelFromFile("ANBCModel.txt") ){
        cout << "Failed to load the classifier model!\n";
        return EXIT_FAILURE;
    }
    
    //Use the test dataset to test the ANBC model
    double accuracy = 0;
    for(UINT i=0; i<testData.getNumSamples(); i++){
        //Get the i'th test sample
        UINT classLabel = testData[i].getClassLabel();
        vector< double > inputVector = testData[i].getSample();
        
        //Perform a prediction using the classifier
        bool predictSuccess = anbc.predict( inputVector );
        
        if( !predictSuccess ){
            cout << "Failed to perform prediction for test sampel: " << i <<"\n";
            return EXIT_FAILURE;
        }
        
        //Get the predicted class label
        UINT predictedClassLabel = anbc.getPredictedClassLabel();
        vector< double > classLikelihoods = anbc.getClassLikelihoods();
        vector< double > classDistances = anbc.getClassDistances();
        
        //Update the accuracy
        if( classLabel == predictedClassLabel ) accuracy++;
        
        cout << "TestSample: " << i <<  " ClassLabel: " << classLabel << " PredictedClassLabel: " << predictedClassLabel << endl;
    }
    
    cout << "Test Accuracy: " << accuracy/double(testData.getNumSamples())*100.0 << "%" << endl;
    
    return EXIT_SUCCESS;
}