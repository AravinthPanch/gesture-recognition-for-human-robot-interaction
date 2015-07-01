#include <stdio.h>
#include <iostream>
#include <fstream>

#include "GRT.h"
using namespace GRT;


int main()
{
    
    // Training and test data
    ClassificationData trainingData;
    ClassificationData testData;
    
    string file_path = "../../../data/";
    string class_name = "2";
    
    if( !trainingData.loadDatasetFromFile(file_path +  "train/grt/" + class_name + ".txt") ){
        std::cout <<"Failed to load training data!\n";
    }
    
    if( !testData.loadDatasetFromFile(file_path +  "test/grt/" + class_name + ".txt") ){
        std::cout <<"Failed to load training data!\n";
    }
    
    
    // Pipeline setup
    ANBC anbc;
    anbc.setNullRejectionCoeff(1);
    anbc.enableScaling(true);
    anbc.enableNullRejection(true);
    
    GestureRecognitionPipeline pipeline;
    pipeline.setClassifier(anbc);
    
    
    // Train the pipeline
    if( !pipeline.train( trainingData ) ){
        std::cout << "Failed to train classifier!\n";
    }
    
    
    // File stream
    ofstream outputFileStream(class_name + ".csv");
    
    
    // Evaluation
    double accuracy = 0;
    
    outputFileStream << "actualClass,predictedClass,maximumLikelihood \n";
    
    for(UINT i=0; i<testData.getNumSamples(); i++){
        
        UINT actualClassLabel = testData[i].getClassLabel();
        vector< double > inputVector = testData[i].getSample();
        
        if( !pipeline.predict( inputVector )){
            std::cout << "Failed to perform prediction for test sampel: " << i <<"\n";
        }
        
        UINT predictedClassLabel = pipeline.getPredictedClassLabel();
        double maximumLikelihood = pipeline.getMaximumLikelihood();
        
        outputFileStream << actualClassLabel << "," << predictedClassLabel << "," << maximumLikelihood << "\n";
        
        if( actualClassLabel == predictedClassLabel) accuracy++;
        
    }
    
    std::cout << "Test Accuracy testHandsUp : " << accuracy/double(testData.getNumSamples())*100.0 << " %\n";
}


