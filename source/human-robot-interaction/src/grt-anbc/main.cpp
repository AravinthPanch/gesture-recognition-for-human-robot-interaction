//Include the main GRT header, you might need to edit the path of this to match the location of the main GRT folder
#include "GRT.h"
using namespace GRT;

int main (int argc, const char * argv[])
{
    //Load some training data from a file
    ClassificationData trainingData;
    
    if( !trainingData.loadDatasetFromFile("anbc-training-data.txt") ){
        cout << "ERROR: Failed to load training data from file\n";
        return EXIT_FAILURE;
    }
    
    cout << "Data Loaded\n";
    
    //Print out some stats about the training data
    trainingData.printStats();
    
    //Partition the training data into a training dataset and a test dataset. 80 means that 80%
    //of the data will be used for the training data and 20% will be returned as the test dataset
    ClassificationData testData = trainingData.partition(80);
    
    //Create a new Gesture Recognition Pipeline using an Adaptive Naive Bayes Classifier
    GestureRecognitionPipeline pipeline;
    pipeline.setClassifier( ANBC() );
    
    //Train the pipeline using the training data
    if( !pipeline.train( trainingData ) ){
        cout << "ERROR: Failed to train the pipeline!\n";
        return EXIT_FAILURE;
    }
    
    //Save the pipeline to a file
    if( !pipeline.savePipelineToFile( "HelloWorldPipeline" ) ){
        cout << "ERROR: Failed to save the pipeline!\n";
        return EXIT_FAILURE;
    }
    
    //Load the pipeline from a file
    if( !pipeline.loadPipelineFromFile( "HelloWorldPipeline" ) ){
        cout << "ERROR: Failed to load the pipeline!\n";
        return EXIT_FAILURE;
    }
    
    //Test the pipeline using the test data
    if( !pipeline.test( testData ) ){
        cout << "ERROR: Failed to test the pipeline!\n";
        return EXIT_FAILURE;
    }
    
    //Print some stats about the testing
    cout << "Test Accuracy: " << pipeline.getTestAccuracy() << endl;
    
    cout << "Precision: ";
    for(UINT k=0; k<pipeline.getNumClassesInModel(); k++){
        UINT classLabel = pipeline.getClassLabels()[k];
        cout << "\t" << pipeline.getTestPrecision(classLabel);
    }cout << endl;
    
    cout << "Recall: ";
    for(UINT k=0; k<pipeline.getNumClassesInModel(); k++){
        UINT classLabel = pipeline.getClassLabels()[k];
        cout << "\t" << pipeline.getTestRecall(classLabel);
    }cout << endl;
    
    cout << "FMeasure: ";
    for(UINT k=0; k<pipeline.getNumClassesInModel(); k++){
        UINT classLabel = pipeline.getClassLabels()[k];
        cout << "\t" << pipeline.getTestFMeasure(classLabel);
    }cout << endl;
    
    Matrix< double > confusionMatrix = pipeline.getTestConfusionMatrix();
    cout << "ConfusionMatrix: \n";
    for(UINT i=0; i<confusionMatrix.getNumRows(); i++){
        for(UINT j=0; j<confusionMatrix.getNumCols(); j++){
            cout << confusionMatrix[i][j] << "\t";
        }cout << endl;
    }
    
    return EXIT_SUCCESS;
}