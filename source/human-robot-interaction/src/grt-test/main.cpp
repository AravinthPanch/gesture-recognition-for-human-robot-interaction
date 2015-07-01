#include <stdio.h>
#include <iostream>
#include <fstream>

#include "GRT.h"
using namespace GRT;


void prediction_axis_data(){
    
    // Training and test data
    ClassificationData trainingData;
    ClassificationData testData;
    
    string file_path = "../../../data/";
    string class_name = "5";
    
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
    
    outputFileStream << "actualClass,predictedClass,maximumLikelihood,lZ,lY,lZ,rZ,rY,rZ \n";
    
    for(UINT i=0; i<testData.getNumSamples(); i++){
        
        UINT actualClassLabel = testData[i].getClassLabel();
        vector< double > inputVector = testData[i].getSample();
        
        if( !pipeline.predict( inputVector )){
            std::cout << "Failed to perform prediction for test sampel: " << i <<"\n";
        }
        
        UINT predictedClassLabel = pipeline.getPredictedClassLabel();
        double maximumLikelihood = pipeline.getMaximumLikelihood();
        
        outputFileStream << actualClassLabel << "," << predictedClassLabel << "," << maximumLikelihood << ","
        << inputVector[0] << "," << inputVector[1] << ","  << inputVector[2] << ","  << inputVector[3] << ","  << inputVector[4] << ","  << inputVector[5] << "\n";
        
        if( actualClassLabel == predictedClassLabel) accuracy++;
        
    }
    
    std::cout << "Test Accuracy testHandsUp : " << accuracy/double(testData.getNumSamples())*100.0 << " %\n";
    
}

void accuracy_rejection_data(){
    
    // Training and test data
    ClassificationData trainingData;
    ClassificationData testData;
    
    string file_path = "../../../data/";
    
    if( !trainingData.loadDatasetFromFile(file_path +  "train/grt/12345.txt") ){
        std::cout <<"Failed to load training data!\n";
    }
    
    ANBC anbc;
    anbc.enableScaling(true);
    anbc.enableNullRejection(true);
    
    SVM svm(SVM::RBF_KERNEL);
    svm.enableScaling(true);
    svm.enableNullRejection(true);
    
    MinDist minDist;
    minDist.setNumClusters(1);
    svm.enableScaling(true);
    svm.enableNullRejection(true);
    
    ofstream outputFileStream("accuracy-mindist.csv");
    outputFileStream << "classLabel,nullRejectionCoeff,accuracy, \n";
    
    
    for(int class_name = 1; class_name<=5; class_name++){
        
        if( !testData.loadDatasetFromFile(file_path +  "test/grt/" + to_string(class_name)  + ".txt") ){
            std::cout <<"Failed to load training data!\n";
        }
        
        
        
        for(double nullRejectionCoeff = 0; nullRejectionCoeff <= 10; nullRejectionCoeff=nullRejectionCoeff+0.2){
            //            anbc.setNullRejectionCoeff(nullRejectionCoeff);
            //            svm.setNullRejectionCoeff(nullRejectionCoeff);
            minDist.setNullRejectionCoeff(nullRejectionCoeff);
            
            GestureRecognitionPipeline pipeline;
            //            pipeline.setClassifier(anbc);
            //            pipeline.setClassifier(svm);
            pipeline.setClassifier(minDist);
            
            
            // Train the pipeline
            if( !pipeline.train( trainingData ) ){
                std::cout << "Failed to train classifier!\n";
            }
            
            
            // Evaluation
            double accuracy = 0;
            for(UINT i=0; i<testData.getNumSamples(); i++){
                
                UINT actualClassLabel = testData[i].getClassLabel();
                vector< double > inputVector = testData[i].getSample();
                
                if( !pipeline.predict( inputVector )){
                    std::cout << "Failed to perform prediction for test sampel: " << i <<"\n";
                }
                
                UINT predictedClassLabel = pipeline.getPredictedClassLabel();
                if( actualClassLabel == predictedClassLabel) accuracy++;
            }
            
            outputFileStream << class_name << ',' << nullRejectionCoeff << ',' << accuracy/double(testData.getNumSamples())*100.0 << '\n';
            
            cout<< "Done" << endl;
        }
        
        
    }
    
    
    //---------------------- Null Gesture Test -----------------//
    int class_name = 0;
    
    if( !testData.loadDatasetFromFile(file_path +  "test/grt/" + to_string(class_name)  + ".txt") ){
        std::cout <<"Failed to load training data!\n";
    }
    
    
    for(double nullRejectionCoeff = 0; nullRejectionCoeff <= 10; nullRejectionCoeff=nullRejectionCoeff+0.2){
        //            anbc.setNullRejectionCoeff(nullRejectionCoeff);
        //            svm.setNullRejectionCoeff(nullRejectionCoeff);
        minDist.setNullRejectionCoeff(nullRejectionCoeff);
        
        GestureRecognitionPipeline pipeline;
        //            pipeline.setClassifier(anbc);
        //            pipeline.setClassifier(svm);
        pipeline.setClassifier(minDist);
        
        
        // Train the pipeline
        if( !pipeline.train( trainingData ) ){
            std::cout << "Failed to train classifier!\n";
        }
        
        
        // Evaluation
        double accuracy = 0;
        for(UINT i=0; i<testData.getNumSamples(); i++){
            
            vector< double > inputVector = testData[i].getSample();
            
            if( !pipeline.predict( inputVector )){
                std::cout << "Failed to perform prediction for test sampel: " << i <<"\n";
            }
            
            UINT predictedClassLabel = pipeline.getPredictedClassLabel();
            if(predictedClassLabel == 0 ) accuracy++;
        }
        
        outputFileStream << class_name << ',' << nullRejectionCoeff << ',' << accuracy/double(testData.getNumSamples())*100.0 << '\n';
        
        cout<< "Done" << endl;
        
        
    }
    
}




int main()
{
    accuracy_rejection_data();
    //    prediction_axis_data();
}


