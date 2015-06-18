#include "GRT.h"
using namespace GRT;

int main (int argc, const char * argv[])
{    
    GestureRecognitionPipeline pipeline;    
    ANBC anbc;    
    ClassificationData trainingData;
  
    trainingData.loadDatasetFromFile("training-data.txt") 
    pipeline.setClassifier(anbc);
    pipeline.train(trainingData);
    
    VectorDouble inputVector(SAMPLE_DIMENSION) = getDataFromSensor();

    pipeline.predict(inputVector);
    
    UINT predictedClassLabel = pipeline.getPredictedClassLabel();
    double maxLikelihood =  pipeline.getMaximumLikelihood();
    printf("predictedClassLabel : %d , MaximumLikelihood : %f \n", predictedClassLabel, maxLikelihood);
   
    return EXIT_SUCCESS;
}