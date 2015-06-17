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
    
    //    run();
    //    grtDataToJson();
    //    testNullRejection();
    //        testHandsUp();
    externalRangeTest();
}



void test::testHandsUp(){
    //--------------------- Load Datasets --------------------------//
    
    ClassificationData trainingData;
    ClassificationData testData;
    
    
    if( !trainingData.loadDatasetFromFile("../-train/1-1-2-3-4.txt") ){
        BOOST_LOG_TRIVIAL(error) <<"Failed to load training data!\n";
    }
    
    if( !testData.loadDatasetFromFile("../-train/1-5.txt") ){
        BOOST_LOG_TRIVIAL(error) <<"Failed to load training data!\n";
    }
    
    
    //--------------------- Init Classifiers ------------------------//
    
    ANBC anbc;
    anbc.setNullRejectionCoeff(5);
    anbc.enableScaling(true);
    anbc.enableNullRejection(true);
    
    //--------------------- Init and Train Pipeline -----------------------//
    
    GestureRecognitionPipeline pipeline;
    pipeline.setClassifier(anbc);
    
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
        
        if( classLabel == predictedClassLabel) accuracy++;
        
        //        BOOST_LOG_TRIVIAL(debug) << "TestSample: " << i <<  " ClassLabel: " << classLabel << " PredictedClassLabel: " << predictedClassLabel;
    }
    
    BOOST_LOG_TRIVIAL(info) << "Test Accuracy testHandsUp : " << accuracy/double(testData.getNumSamples())*100.0 << "%";
}

void test::testNullRejection(){
    
    //--------------------- Load Datasets --------------------------//
    
    ClassificationData trainingData;
    ClassificationData testData;
    
    
    if( !trainingData.loadDatasetFromFile("../-test/1-1-2-3.txt") ){
        BOOST_LOG_TRIVIAL(error) <<"Failed to load training data!\n";
    }
    
    if( !testData.loadDatasetFromFile("../-train/0.txt") ){
        BOOST_LOG_TRIVIAL(error) <<"Failed to load training data!\n";
    }
    
    
    //--------------------- Init Classifiers ------------------------//
    
    ANBC anbc;
    anbc.setNullRejectionCoeff(3);
    anbc.enableScaling(true);
    anbc.enableNullRejection(true);
    
    //--------------------- Init and Train Pipeline -----------------------//
    
    GestureRecognitionPipeline pipeline;
    pipeline.setClassifier(anbc);
    
    if( !pipeline.train( trainingData ) ){
        BOOST_LOG_TRIVIAL(error) << "Failed to train classifier!\n";
    }
    
    
    vector< MinMax > ranges = trainingData.getRanges();
    
    
    cout << "The ranges of the dataset are: \n";
    for(UINT j=0; j<ranges.size(); j++){
        cout << "Dimension: " << j << " Min: " << ranges[j].minValue << " Max: " << ranges[j].maxValue << endl;
    }
    
    //--------------------- Test Accuracy ---------------------------//
    
    double accuracy = 0;
    
    UINT classLabel = trainingData[0].getClassLabel();
    
    for(UINT i=0; i<testData.getNumSamples(); i++){
        
        
        vector< double > inputVector = testData[i].getSample();
        
        if( !pipeline.predict( inputVector )){
            BOOST_LOG_TRIVIAL(error) << "Failed to perform prediction for test sampel: " << i <<"\n";
        }
        
        UINT predictedClassLabel = pipeline.getPredictedClassLabel();
        
        if( predictedClassLabel == 0 ) accuracy++;
        
        BOOST_LOG_TRIVIAL(debug) << "TestSample: " << i << " PredictedClassLabel: " << predictedClassLabel << " classLabel: " << classLabel;
    }
    
    
    BOOST_LOG_TRIVIAL(info) << "Test Accuracy testNullRejection :" << accuracy/double(testData.getNumSamples())*100.0 << "%";
    
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
        
        
        if( classLabel == unprocessedClassLabel ) accuracy++;
        
        //        BOOST_LOG_TRIVIAL(debug) << i <<  " : " << classLabel << " : "<< unprocessedClassLabel;
        
        
        BOOST_LOG_TRIVIAL(debug) << "TestSample: " << i <<  " ClassLabel: " << classLabel
        << " PredictedClassLabel: " << predictedClassLabel << " unprocessedClassLabel: " << unprocessedClassLabel;
        
    }
    
    
    BOOST_LOG_TRIVIAL(info) << "Test Accuracy: " << accuracy/double(testData.getNumSamples())*100.0 << "%";
}

void test::grtDataToJson(){
    ClassificationData testData;
    if( !testData.loadDatasetFromFile("../-train/2-6.txt") ){
        BOOST_LOG_TRIVIAL(error) <<"Failed to load training data!\n";
    }
    
    for(UINT i=0; i<testData.getNumSamples(); i++){
        
        std::string lx = "\"" + std::to_string(testData[i].getSample()[0]) + "\",";
        std::string ly = "\"" + std::to_string(testData[i].getSample()[1]) + "\",";
        std::string lz = "\"" + std::to_string(testData[i].getSample()[2]) + "\"]";
        
        std::string rx = "\"" + std::to_string(testData[i].getSample()[3]) + "\",";
        std::string ry = "\"" + std::to_string(testData[i].getSample()[4]) + "\",";
        std::string rz = "\"" + std::to_string(testData[i].getSample()[5]) + "\"]";
        
        std::string right = "{\"RIGHT\":[" +  rx + ry + rz ;
        std::string left = ", \"LEFT\":[" +  lx + ly + lz + "},";
        std::cout << right + left + "\n";
    }
    
}

void test::externalRangeTest(){
    //--------------------- Load Datasets --------------------------//
    
    ClassificationData trainingData;
    ClassificationData testData;
    
    
    if( !trainingData.loadDatasetFromFile("../-test/1-1-ext.txt") ){
        BOOST_LOG_TRIVIAL(error) <<"Failed to load training data!\n";
    }
    
    //--------------------- Init Classifiers ------------------------//
    
    ANBC anbc;
    anbc.setNullRejectionCoeff(3);
    anbc.enableScaling(true);
    anbc.enableNullRejection(true);
    
    //--------------------- Init and Train Pipeline -----------------------//
    
    GestureRecognitionPipeline pipeline;
    pipeline.setClassifier(anbc);
    
    if( !pipeline.train( trainingData ) ){
        BOOST_LOG_TRIVIAL(error) << "Failed to train classifier!\n";
    }
    

    trainingData.enableExternalRangeScaling(true);
    
    //--------------------- Test -----------------------//
    vector< MinMax > ranges = trainingData.getClassData(1).getRanges();
    
    cout << "The ranges of the dataset are: \n";
    for(UINT j=0; j<ranges.size(); j++){
        cout << "Dimension: " << j << " Min: " << ranges[j].minValue << " Max: " << ranges[j].maxValue << endl;
    }
    

    
    
//    vector< MinMax > externalRange;
//    MinMax d1(-1000,1000);
//    MinMax d2(-1000,1000);
//    MinMax d3(-1000,1000);
//    MinMax d4(-1000,1000);
//    MinMax d5(-1000,1000);
//    MinMax d6(-1000,1000);
//    
//    externalRange.push_back(d1);
//    externalRange.push_back(d2);
//    externalRange.push_back(d3);
//    externalRange.push_back(d4);
//    externalRange.push_back(d5);
//    externalRange.push_back(d6);
//    
//    trainingData.setExternalRanges(externalRange);
//    trainingData.enableExternalRangeScaling(true);
//    
//    trainingData.saveDatasetToFile("extRange.txt");
    
    
    
}






