#include <stdio.h>
#include <iostream>
#include <fstream>

#include "GRT.h"
using namespace GRT;

bool AreDoubleSame(double dFirstVal, double dSecondVal)
{
    return std::fabs(dFirstVal - dSecondVal) < 1E-3;
}



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

void metrics_separate_data(){
    
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
    minDist.setNumClusters(4);
    minDist.enableScaling(true);
    minDist.enableNullRejection(true);
    
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


void metrics_subset_data(){
    
    
    ANBC anbc;
    anbc.enableScaling(true);
    anbc.enableNullRejection(true);
    
    MinDist minDist;
    minDist.setNumClusters(4);
    minDist.enableScaling(true);
    minDist.enableNullRejection(true);
    
    //    ofstream opRecall("anbc-recall-nr-0-10.csv");
    //    opRecall <<"nrCoeff,class0,class1,class2,class3,class4,class5\n";
    //
    //    ofstream opInstanceRes("anbc-prediction-nr-2.csv");
    //    opInstanceRes <<"actualClass,predictedClass,maximumLikelihood,lZ,lY,lZ,rZ,rY,rZ\n";
    //
    //    ofstream opMetrics("anbc-precision-recall-fmeasure-nr-2.csv");
    //    opMetrics <<"class1,class2,class3,class4,class5\n";
    //
    //    ofstream opConfusion("anbc-confusion-nr-2.csv");
    //    opConfusion <<"class0,class1,class2,class3,class4,class5\n";
    
    
    ofstream opRecall("mindist-recall-nr-0-10.csv");
    opRecall <<"nrCoeff,class0,class1,class2,class3,class4,class5\n";
    
    ofstream opInstanceRes("mindist-prediction-nr-2.csv");
    opInstanceRes <<"actualClass,predictedClass,maximumLikelihood,lZ,lY,lZ,rZ,rY,rZ\n";
    
    ofstream opMetrics("mindist-precision-recall-fmeasure-nr-2.csv");
    opMetrics <<"class1,class2,class3,class4,class5\n";
    
    ofstream opConfusion("mindist-confusion-nr-2.csv");
    opConfusion <<"class0,class1,class2,class3,class4,class5\n";
    
    // Training and test data
    ClassificationData trainingData;
    ClassificationData testData;
    ClassificationData nullGestureData;
    
    string file_path = "../../../data/";
    
    if( !trainingData.loadDatasetFromFile(file_path +  "train/grt/hri-training-dataset.txt") ){
        std::cout <<"Failed to load training data!\n";
    }
    
    if( !nullGestureData.loadDatasetFromFile(file_path +  "test/grt/0.txt") ){
        std::cout <<"Failed to load null gesture data!\n";
    }
    
    
    testData = trainingData.partition(90);
    testData.sortClassLabels();
//    testData.saveDatasetToFile("anbc-validation-subset.txt");
    testData.saveDatasetToFile("mindist-validation-subset.txt");
    
    
    for(double nullRejectionCoeff = 0; nullRejectionCoeff <= 10; nullRejectionCoeff=nullRejectionCoeff+0.2){
        
        //        anbc.setNullRejectionCoeff(nullRejectionCoeff);
        //        GestureRecognitionPipeline pipeline;
        //        pipeline.setClassifier(anbc);
        
        minDist.setNullRejectionCoeff(nullRejectionCoeff);
        GestureRecognitionPipeline pipeline;
        pipeline.setClassifier(minDist);
        
        pipeline.train(trainingData);
        
        pipeline.test(testData);
        TestResult testRes = pipeline.getTestResults();
        
        opRecall << nullRejectionCoeff << ",";
        
        
        //null rejection prediction
        double accuracy = 0;
        for(UINT i=0; i<nullGestureData.getNumSamples(); i++){
            
            vector< double > inputVector = nullGestureData[i].getSample();
            
            if( !pipeline.predict( inputVector )){
                std::cout << "Failed to perform prediction for test sampel: " << i <<"\n";
            }
            
            UINT predictedClassLabel = pipeline.getPredictedClassLabel();
            if(predictedClassLabel == 0 ) accuracy++;
        }
        
        opRecall << accuracy/double(nullGestureData.getNumSamples()) << ",";
        
        
        // other classes prediction
        for(int cl = 0; cl < testRes.recall.size(); cl++ ){
            opRecall << testRes.recall[cl];
            if(cl < testRes.recall.size() - 1){
                opRecall << ",";
            }
        }
        
        opRecall<< endl;
        
        
        // Calculate instance prediction, precision, recall, fmeasure and confusion matrix for nullRejection 2.0
        if(AreDoubleSame(nullRejectionCoeff, 2.0))
        {
            //instance prediction
            for(UINT i=0; i<testData.getNumSamples(); i++){
                
                UINT actualClassLabel = testData[i].getClassLabel();
                vector< double > inputVector = testData[i].getSample();
                
                if( !pipeline.predict( inputVector )){
                    std::cout << "Failed to perform prediction for test sampel: " << i <<"\n";
                }
                
                UINT predictedClassLabel = pipeline.getPredictedClassLabel();
                double maximumLikelihood = pipeline.getMaximumLikelihood();
                
                opInstanceRes << actualClassLabel << "," << predictedClassLabel << "," << maximumLikelihood << ","
                << inputVector[0] << "," << inputVector[1] << ","  << inputVector[2] << ","  << inputVector[3] << ","  << inputVector[4] << ","  << inputVector[5] << "\n";
                
            }
            
            //precision, recall, fmeasure
            for(int cl = 0; cl < testRes.precision.size(); cl++ ){
                opMetrics << testRes.precision[cl];
                if(cl < testRes.precision.size() - 1){
                    opMetrics << ",";
                }
            }
            opMetrics<< endl;
            
            for(int cl = 0; cl < testRes.recall.size(); cl++ ){
                opMetrics << testRes.recall[cl];
                
                if(cl < testRes.recall.size() - 1){
                    opMetrics << ",";
                }
            }
            opMetrics<< endl;
            
            for(int cl = 0; cl < testRes.fMeasure.size(); cl++ ){
                opMetrics << testRes.fMeasure[cl];
                
                if(cl < testRes.fMeasure.size() - 1){
                    opMetrics << ",";
                }
            }
            opMetrics<< endl;
            
            //confusion matrix
            MatrixDouble matrix = testRes.confusionMatrix;
            for(UINT i=0; i<matrix.getNumRows(); i++){
                for(UINT j=0; j<matrix.getNumCols(); j++){
                    opConfusion << matrix[i][j];
                    
                    if(j < matrix.getNumCols() - 1){
                        opConfusion << ",";
                    }
                    
                }
                opConfusion << endl;
            }
            opConfusion << endl;
            
        }
        
        
        
    }
    
    cout << "Done\n";
}





int main()
{
    metrics_subset_data();
    //    metrics_separate_data();
    //    prediction_axis_data();
    
    //    double tes = 2.1;
    //    cout << AreDoubleSame(tes, 2.0);
}


