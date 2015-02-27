/**
 @file
 @author  Nicholas Gillian <ngillian@media.mit.edu>
 @version 1.0
 
 @brief The Softmax Classifier is a simple but effective classifier (based on logisitc regression) that works well on problems that are linearly separable.
 
 @example ClassificationModulesExamples/SoftmaxExample/SoftmaxExample.cpp
 
 @remark This implementation is based on Bishop, Christopher M. Pattern recognition and machine learning. Vol. 1. New York: springer, 2006.
 */

/**
 GRT MIT License
 Copyright (c) <2012> <Nicholas Gillian, Media Lab, MIT>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial
 portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef GRT_SOFTMAX_HEADER
#define GRT_SOFTMAX_HEADER

#include "../../CoreModules/Classifier.h"
#include "SoftmaxModel.h"

namespace GRT{

class Softmax : public Classifier
{
public:
    /**
     Default Constructor

     @param const bool useScaling: sets if the training and real-time data should be scaled between [0 1]. Default value = false
     @param double learningRate: the learningRate value used during the training phase. Default = 0.1
     @param double minChange: sets the minimum change that must be achieved between two training epochs for the training to continue. Default = 1.0e-10
     @param UINT maxNumEpochs: sets the maximum number of iterations that can be run during the training phase. Default = 1000
     */
	Softmax(const bool useScaling=false,const double learningRate = 0.1,const double minChange = 1.0e-10,const UINT maxNumEpochs = 1000);
    
    /**
     Defines the copy constructor.
     
     @param const Softmax &rhs: the instance from which all the data will be copied into this instance
     */
    Softmax(const Softmax &rhs);
    
    /**
     Default Destructor
     */
	virtual ~Softmax(void);
    
    /**
     Defines how the data from the rhs Softmax should be copied to this Softmax
     
     @param const Softmax &rhs: another instance of a Softmax
     @return returns a pointer to this instance of the Softmax
     */
	Softmax &operator=(const Softmax &rhs);
    
    /**
     This is required for the Gesture Recognition Pipeline for when the pipeline.setClassifier(...) method is called.  
     It clones the data from the Base Class Classifier pointer (which should be pointing to an Softmax instance) into this instance
     
     @param Classifier *classifier: a pointer to the Classifier Base Class, this should be pointing to another Softmax instance
     @return returns true if the clone was successfull, false otherwise
    */
	virtual bool deepCopyFrom(const Classifier *classifier);
    
    /**
     This trains the Softmax model, using the labelled classification data.
     This overrides the train function in the Classifier base class.
     
     @param ClassificationData trainingData: a reference to the training data
     @return returns true if the Softmax model was trained, false otherwise
    */
    virtual bool train_(ClassificationData &trainingData);
    
    /**
     This predicts the class of the inputVector.
     This overrides the predict function in the Classifier base class.
     
     @param VectorDouble inputVector: the input vector to classify
     @return returns true if the prediction was performed, false otherwise
    */
    virtual bool predict_(VectorDouble &inputVector);
    
    /**
     This overrides the clear function in the Classifier base class.
     It will completely clear the ML module, removing any trained model and setting all the base variables to their default values.
     
     @return returns true if the module was cleared succesfully, false otherwise
     */
    virtual bool clear();
    
    /**
     This saves the trained Softmax model to a file.
     This overrides the saveModelToFile function in the Classifier base class.
     
     @param fstream &file: a reference to the file the Softmax model will be saved to
     @return returns true if the model was saved successfully, false otherwise
     */
    virtual bool saveModelToFile(fstream &file) const;
    
    /**
     This loads a trained Softmax model from a file.
     This overrides the loadModelFromFile function in the Classifier base class.
     
     @param fstream &file: a reference to the file the Softmax model will be loaded from
     @return returns true if the model was loaded successfully, false otherwise
     */
    virtual bool loadModelFromFile(fstream &file);
    
    /**
     Get the softmax models for each class. The Softmax class must be trained first.
     
     @return returns a vector of softmax models, with each element representing the model for a specific class
     */
    vector< SoftmaxModel > getModels() const;
    
    //Tell the compiler we are using the base class train method to stop hidden virtual function warnings
    using MLBase::saveModelToFile;
    using MLBase::loadModelFromFile;
    
protected:
    bool trainSoftmaxModel(UINT classLabel,SoftmaxModel &model,ClassificationData &data);
    bool loadLegacyModelFromFile( fstream &file );
    
    vector< SoftmaxModel > models;
    
    static RegisterClassifierModule< Softmax > registerModule;
};

} //End of namespace GRT

#endif //GRT_SOFTMAX_HEADER

