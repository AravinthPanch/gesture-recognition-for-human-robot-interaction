/**
 @file
 @author  Nicholas Gillian <ngillian@media.mit.edu>
 @version 1.0
 
 @brief This class implements a Random Decision Forest classifier.

 Random Forests are an ensemble learning method that operate by building a number of decision 
 trees at training time and outputting the class with the majority vote over all the trees in the ensemble.
 
 @example ClassificationModulesExamples/RandomForestsExample/RandomForestsExample.cpp
 
 @remark This implementation is based on Breiman, Leo. "Random forests." Machine learning 45, no. 1 (2001): 5-32.
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

#ifndef GRT_RANDOM_FORESTS_HEADER
#define GRT_RANDOM_FORESTS_HEADER

#include "../DecisionTree/DecisionTree.h"

namespace GRT{

class RandomForests : public Classifier
{
public:
    /**
     Default Constructor
     
     @param const DecisionTreeNode &decisionTreeNode: sets the type of decision tree node that will be used when training a new RandomForest model. Default: DecisionTreeClusterNode
     @param const UINT forestSize: sets the number of decision trees that will be trained. Default value = 10
     @param const UINT numRandomSplits: sets the number of random spilts that will be used to search for the best spliting value for each node. Default value = 100
     @param const UINT minNumSamplesPerNode: sets the minimum number of samples that are allowed per node, if the number of samples is below that, the node will become a leafNode.  Default value = 5
     @param const UINT maxDepth: sets the maximum depth of the tree. Default value = 10
     @param const bool removeFeaturesAtEachSpilt: sets if features are removed at each stage in the tree
     @param const bool useScaling: sets if the training and real-time data should be scaled between [0 1]. Default value = false
     */
	RandomForests(const DecisionTreeNode &decisionTreeNode = DecisionTreeClusterNode(),const UINT forestSize=10,const UINT numRandomSplits=100,const UINT minNumSamplesPerNode=5,const UINT maxDepth=10,const UINT trainingMode = DecisionTree::BEST_RANDOM_SPLIT,const bool removeFeaturesAtEachSpilt = true,const bool useScaling=false);
    
    /**
     Defines the copy constructor.
     
     @param const RandomForests &rhs: the instance from which all the data will be copied into this instance
     */
    RandomForests(const RandomForests &rhs);
    
    /**
     Default Destructor
     */
	virtual ~RandomForests(void);
    
    /**
     Defines how the data from the rhs RandomForests should be copied to this RandomForests
     
     @param const RandomForests &rhs: another instance of a RandomForests
     @return returns a pointer to this instance of the RandomForests
     */
	RandomForests &operator=(const RandomForests &rhs);
    
    /**
     This is required for the Gesture Recognition Pipeline for when the pipeline.setClassifier(...) method is called.  
     It clones the data from the Base Class Classifier pointer (which should be pointing to an RandomForests instance) into this instance
     
     @param Classifier *classifier: a pointer to the Classifier Base Class, this should be pointing to another RandomForests instance
     @return returns true if the clone was successfull, false otherwise
    */
	virtual bool deepCopyFrom(const Classifier *classifier);
    
    /**
     This trains the RandomForests model, using the labelled classification data.
     This overrides the train function in the Classifier base class.
     
     @param ClassificationData trainingData: a reference to the training data
     @return returns true if the RandomForests model was trained, false otherwise
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
     This function clears the RandomForests module, removing any trained model and setting all the base variables to their default values.
     
     @return returns true if the class was cleared succesfully, false otherwise
     */
    virtual bool clear();
    
    /**
     This function will print the model and settings to the display log.
     
     @return returns true if the model was printed succesfully, false otherwise
     */
    virtual bool print() const;
    
    /**
     This saves the trained RandomForests model to a file.
     This overrides the saveModelToFile function in the Classifier base class.
     
     @param fstream &file: a reference to the file the RandomForests model will be saved to
     @return returns true if the model was saved successfully, false otherwise
     */
    virtual bool saveModelToFile(fstream &file) const;
    
    /**
     This loads a trained RandomForests model from a file.
     This overrides the loadModelFromFile function in the Classifier base class.
     
     @param fstream &file: a reference to the file the RandomForests model will be loaded from
     @return returns true if the model was loaded successfully, false otherwise
     */
    virtual bool loadModelFromFile(fstream &file);
    
    /**
     Gets the number of trees in the random forest.
     
     @return returns the number of trees in the random forest
     */
    UINT getForestSize() const;
    
    /**
     Gets the number of random splits that will be used to search for the best spliting value for each node.
     
     @return returns the number of steps that will be used to search for the best spliting value for each node
     */
    UINT getNumRandomSplits() const;
    
    /**
     Gets the minimum number of samples that are allowed per node, if the number of samples at a node is below 
     this value then the node will automatically become a leaf node.
     
     @return returns the minimum number of samples that are allowed per node
     */
    UINT getMinNumSamplesPerNode() const;
    
    /**
     Gets the maximum depth of the tree.
     
     @return returns the maximum depth of the tree
     */
    UINT getMaxDepth() const;
    
    /**
     Gets the training mode that will be used to train each DecisionTree in the forest.
     
     @return returns the trainingMode
     */
    UINT getTrainingMode() const;
    
    const vector< DecisionTreeNode* > getForest() const;
    
    /**
     Gets if a feature is removed at each spilt so it can not be used again.  If true then the best feature selected at each node will be
     removed so it can not be used in any children of that node.  If false, then the feature that provides the best spilt at each node will
     be used, regardless of how many times it has been used again.
     
     @return returns the removeFeaturesAtEachSpilt parameter
     */
    bool getRemoveFeaturesAtEachSpilt() const;
    
    /**
     Gets a pointer to the decision tree node. NULL will be returned if the decision tree node has not been set.
     
     @return returns a pointer to a deep copy of the decision tree node
     */
    DecisionTreeNode* deepCopyDecisionTreeNode() const;
    
    /**
     Sets the number of trees in the forest.  Changing this value will clear any previously trained model.
     
     @param UINT forestSize: sets the number of trees in the forest.
     @return returns true if the parameter was set, false otherwise
     */
    bool setForestSize(const UINT forestSize);
    
    /**
     Sets the number of steps that will be used to search for the best spliting value for each node.
     
     A higher value will increase the chances of building a better model, but will take longer to train the model.
     Value must be larger than zero.
     
     @param UINT numSplittingSteps: sets the number of steps that will be used to search for the best spliting value for each node.
     @return returns true if the parameter was set, false otherwise
     */
    bool setNumRandomSplits(const UINT numSplittingSteps);
    
    /**
     Sets the minimum number of samples that are allowed per node, if the number of samples at a node is below this value then the node will automatically 
     become a leaf node.
     Value must be larger than zero.
     
     @param UINT minNumSamplesPerNode: the minimum number of samples that are allowed per node
     @return returns true if the parameter was set, false otherwise
     */
    bool setMinNumSamplesPerNode(const UINT minNumSamplesPerNode);
    
    /**
     Sets the maximum depth of the tree, any node that reaches this depth will automatically become a leaf node.
     Value must be larger than zero.
     
     @param UINT maxDepth: the maximum depth of the tree
     @return returns true if the parameter was set, false otherwise
     */
    bool setMaxDepth(const UINT maxDepth);
    
    /**
     Sets if a feature is removed at each spilt so it can not be used again.  If true then the best feature selected at each node will be
     removed so it can not be used in any children of that node.  If false, then the feature that provides the best spilt at each node will
     be used, regardless of how many times it has been used again.
     
     @param bool removeFeaturesAtEachSpilt: if true, then each feature is removed at each spilt so it can not be used again
     @return returns true if the parameter was set, false otherwise
     */
    bool setRemoveFeaturesAtEachSpilt(const bool removeFeaturesAtEachSpilt);
    
    /**
     Sets the training mode used to train each DecisionTree in the forest, this should be one of the DecisionTree::TrainingModes enums.
     
     @param const UINT trainingMode: the new trainingMode, this should be one of the DecisionTree::TrainingModes enums
     @return returns true if the trainingMode was set successfully, false otherwise
     */
    bool setTrainingMode(const UINT trainingMode);
    
    /**
     Sets the decision tree node, this will be used as the starting node the next time the RandomForest model is trained.
     
     @return returns true if the decision tree node was updated, false otherwise
     */
    bool setDecisionTreeNode( const DecisionTreeNode &node );
    
    //Tell the compiler we are using the base class train method to stop hidden virtual function warnings
    using MLBase::saveModelToFile;
    using MLBase::loadModelFromFile;
    
protected:
    
    UINT forestSize;
    UINT numRandomSplits;
    UINT minNumSamplesPerNode;
    UINT maxDepth;
    UINT trainingMode;
    bool removeFeaturesAtEachSpilt;
    DecisionTreeNode* decisionTreeNode;
    vector< DecisionTreeNode* > forest;
    
private:
    static RegisterClassifierModule< RandomForests > registerModule;
    
};

} //End of namespace GRT

#endif //GRT_RANDOM_FORESTS_HEADER

