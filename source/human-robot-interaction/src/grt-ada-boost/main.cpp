/*
 GRT AdaBoost Example
 This examples demonstrates how to initialize, train, and use the AdaBoost algorithm for classification.
 
 AdaBoost (Adaptive Boosting) is a powerful classifier that works well on both basic and more complex recognition problems.
 AdaBoost works by combining several relatively weak classifiers together to form a highly accurate strong classifier.  AdaBoost
 therefore acts as a meta algorithm, which allows you to use it as a wrapper for other classifiers.  In the GRT, these classifiers
 are called WeakClassifiers such as a DecisionStump (which is just one node of a DecisionTree).
 
 In this example we create an instance of an AdaBoost algorithm and then train the algorithm using some pre-recorded training data.
 The trained AdaBoost algorithm is then used to predict the class label of some test data.
 This example uses the DecisionStump as the WeakClassifer, although AdaBoost works with any GRT WeakClassifier (including any you write yourself).
 
 This example shows you how to:
 - Create an initialize the AdaBoost algorithm
 - Set a DecisionStump as the WeakClassifer
 - Load some LabelledClassificationData from a file and partition the training data into a training dataset and a test dataset
 - Train the AdaBoost algorithm using the training dataset
 - Test the AdaBoost algorithm using the test dataset
 - Manually compute the accuracy of the classifier
 */

//You might need to set the specific path of the GRT header relative to your project
#include "GRT.h"
using namespace GRT;

int main (int argc, const char * argv[])
{
    //Create a new AdaBoost instance
    AdaBoost adaBoost;
    
    //Set the weak classifier you want to use
    adaBoost.setWeakClassifier( DecisionStump() );
    
    //Load some training data to train the classifier
    ClassificationData trainingData;
    
    if( !trainingData.loadDatasetFromFile("ada-boost-training-data.txt") ){
        cout << "Failed to load training data!\n";
        return EXIT_FAILURE;
    }
    
    //Use 20% of the training dataset to create a test dataset
    ClassificationData testData = trainingData.partition( 80 );
    
    //Train the classifier
    if( !adaBoost.train( trainingData ) ){
        cout << "Failed to train classifier!\n";
        return EXIT_FAILURE;
    }
    
    //Save the model to a file
    if( !adaBoost.saveModelToFile("AdaBoostModel.txt") ){
        cout << "Failed to save the classifier model!\n";
        return EXIT_FAILURE;
    }
    
    //    //Load the model from a file
    if( !adaBoost.loadModelFromFile("AdaBoostModel.txt") ){
        cout << "Failed to load the classifier model!\n";
        return EXIT_FAILURE;
    }
    
    
    
    //Use the test dataset to test the AdaBoost model
    //    double accuracy = 0;
    //    for(UINT i=0; i<testData.getNumSamples(); i++){
    //        //Get the i'th test sample
    //        UINT classLabel = testData[i].getClassLabel();
    //        vector< double > inputVector = testData[i].getSample();
    //
    //        //Perform a prediction using the classifier
    //        if( !adaBoost.predict( inputVector ) ){
    //            cout << "Failed to perform prediction for test sampel: " << i <<"\n";
    //            return EXIT_FAILURE;
    //        }
    //
    //        //Get the predicted class label
    //        UINT predictedClassLabel = adaBoost.getPredictedClassLabel();
    //        double maximumLikelhood = adaBoost.getMaximumLikelihood();
    //        vector< double > classLikelihoods = adaBoost.getClassLikelihoods();
    //        vector< double > classDistances = adaBoost.getClassDistances();
    //
    //        //Update the accuracy
    //        if( classLabel == predictedClassLabel ) accuracy++;
    //
    //        cout << "TestSample: " << i <<  " ClassLabel: " << classLabel;
    //        cout << " PredictedClassLabel: " << predictedClassLabel << " Likelihood: " << maximumLikelhood;
    //        cout << endl;
    //    }
    //
    //    cout << "Test Accuracy: " << accuracy/double(testData.getNumSamples())*100.0 << "%" << endl;
    
    return EXIT_SUCCESS;
}