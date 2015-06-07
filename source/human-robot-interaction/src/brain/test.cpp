/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 07/06/15.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include <boost/log/trivial.hpp>
#include "test.h"

test::test()
{
    BOOST_LOG_TRIVIAL(info) << "Test Runner Initiated";
    
    run();
}

void test::run(){
    
    //--------------------- Load Datasets --------------------------//
    
    ClassificationData trainingData;
    ClassificationData testData;
    
    
    if( !trainingData.loadDatasetFromFile(TRAINING_DATASET) ){
        BOOST_LOG_TRIVIAL(error) <<"Failed to load training data!\n";
    }
    
    if( !testData.loadDatasetFromFile(TEST_DATASET) ){
        BOOST_LOG_TRIVIAL(error) <<"Failed to load training data!\n";
    }
    
    //        testData = trainingData.partition(80);
    
    //--------------------- Init Classifiers ------------------------//
    
    ANBC anbc;
    anbc.setNullRejectionCoeff(10);
    anbc.enableScaling(true);
    anbc.enableNullRejection(true);
    
    //--------------------- Init and Train Pipeline -----------------------//
    
    GestureRecognitionPipeline pipeline;
    pipeline.setClassifier(anbc);
    pipeline.addPostProcessingModule(ClassLabelFilter(5,10));
    pipeline.addPostProcessingModule(ClassLabelChangeFilter());
    
    if( !pipeline.train( trainingData ) ){
        BOOST_LOG_TRIVIAL(error) << "Failed to train classifier!\n";
    }
    
    
    //--------------------- Test Accuracy ---------------------------//
    
    double accuracy = 0;
    
    for(UINT i=0; i<testData.getNumSamples(); i++){
        
        UINT classLabel = testData[i].getClassLabel();
        vector< double > inputVector = testData[i].getSample();
        
        
        if( !pipeline.predict( inputVector )){
            BOOST_LOG_TRIVIAL(error) << "Failed to perform prediction for test sampel: " << i <<"\n";
        }
        
        
        UINT predictedClassLabel = pipeline.getPredictedClassLabel();
        UINT unprocessedClassLabel = pipeline.getUnProcessedPredictedClassLabel();
        vector< double > classLikelihoods = pipeline.getClassLikelihoods();
        vector< double > classDistances = pipeline.getClassDistances();
        
        
        if( classLabel == predictedClassLabel ) accuracy++;
        
        
        BOOST_LOG_TRIVIAL(debug) << "TestSample: " << i <<  " ClassLabel: " << classLabel
        << " PredictedClassLabel: " << predictedClassLabel << " unprocessedClassLabel: " << unprocessedClassLabel;
        
    }
    
    
    BOOST_LOG_TRIVIAL(info) << "Test Accuracy: " << accuracy/double(testData.getNumSamples())*100.0 << "%";
}