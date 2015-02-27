/**
 @file
 @author  Nicholas Gillian <ngillian@media.mit.edu>
 @version 1.0
 
 @brief The class implements a low pass filter.
 
 @example PreprocessingModulesExamples/LowPassFilterExample/LowPassFilterExample.cpp
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

#ifndef GRT_LOW_PASS_FILTER_HEADER
#define GRT_LOW_PASS_FILTER_HEADER

#include "../CoreModules/PreProcessing.h"

namespace GRT{
    
class LowPassFilter : public PreProcessing{
public:
    /**
     Constructor, sets the filter factor, gain and dimensionality of the low pass filter.
     If the cutoffFrequency and delta values are set then the filter will be initialized with these values rather than the filterFactor.
     If the cutoffFrequency and delta values are kept at their default values of -1 then the values will be ignored and the filter factor will be used instead.
     Otherwise the fiterFactor will control the low pass filter, with a smaller filterFactor (i.e. 0.1) resulting in a more aggresive smoothing
     of the input signal.  The filterFactor should be in the range [0.0 1.0].
	 
     @param double filterFactor: controls the low pass filter, a smaller value will result in a more aggresive smoothing of the input signal. Default value filterFactor = 0.1
     @param double gain: multiples the filtered values by a constant ampltidue. Default value = 1.0
     @param UINT numDimensions: the dimensionality of the input data to filter.  Default numDimensions = 1
     @param double cutoffFrequency: sets the cutoffFrequency of the filter (in Hz). If the cutoffFrequency and delta values are set then the filter will be initialized with these values rather than the filterFactor.  Default value cutoffFrequency = -1.0
     @param double delta: the sampling rate of your sensor, delta should be set as 1.0/SR, where SR is the sampling rate of your sensor.  Default value delta = -1.0
     */
    LowPassFilter(double filterFactor = 0.1,double gain = 1,UINT numDimensions = 1,double cutoffFrequency = -1,double delta = -1);
    
    /**
     Copy Constructor, copies the LowPassFilter from the rhs instance to this instance
     
	 @param const LowPassFilter &rhs: another instance of the LowPassFilter class from which the data will be copied to this instance
     */
    LowPassFilter(const LowPassFilter &rhs);
    
    /**
     Default Destructor
     */
	virtual ~LowPassFilter();
    
    /**
     Sets the equals operator, copies the data from the rhs instance to this instance
     
	 @param const LowPassFilter &rhs: another instance of the LowPassFilter class from which the data will be copied to this instance
	 @return a reference to this instance of LowPassFilter
     */
	LowPassFilter& operator=(const LowPassFilter &rhs);
    
    /**
     Sets the PreProcessing deepCopyFrom function, overwriting the base PreProcessing function.
     This function is used to deep copy the values from the input pointer to this instance of the PreProcessing module.
     This function is called by the GestureRecognitionPipeline when the user adds a new PreProcessing module to the pipeline.
     
	 @param const PreProcessing *preProcessing: a pointer to another instance of a LowPassFilter, the values of that instance will be cloned to this instance
	 @return true if the deep copy was successful, false otherwise
     */
    virtual bool deepCopyFrom(const PreProcessing *preProcessing);
    
    /**
     Sets the PreProcessing process function, overwriting the base PreProcessing function.
     This function is called by the GestureRecognitionPipeline when any new input data needs to be processed (during the prediction phase for example).
     This function calls the LowPassFilter's filter function.
     
	 @param const VectorDouble &inputVector: the inputVector that should be processed.  Must have the same dimensionality as the PreProcessing module
	 @return true if the data was processed, false otherwise
     */
    virtual bool process(const VectorDouble &inputVector);
    
    /**
     Sets the PreProcessing reset function, overwriting the base PreProcessing function.
     This function is called by the GestureRecognitionPipeline when the pipelines main reset() function is called.
     This function resets the filter values by re-initiliazing the filter.
     
	 @return true if the filter was reset, false otherwise
     */
    virtual bool reset();
    
    /**
     This saves the current settings of the LowPassFilter to a file.
     This overrides the saveModelToFile function in the PreProcessing base class.
     
     @param string filename: the name of the file to save the settings to
     @return returns true if the model was saved successfully, false otherwise
     */
    virtual bool saveModelToFile(string filename) const;
    
    /**
     This saves the current settings of the LowPassFilter to a file.
     This overrides the saveModelToFile function in the PreProcessing base class.
     
     @param fstream &file: a reference to the file the settings will be saved to
     @return returns true if the settings were saved successfully, false otherwise
     */
    virtual bool saveModelToFile(fstream &file) const;
    
    /**
     This loads the LowPassFilter settings from a file.
     This overrides the loadModelFromFile function in the PreProcessing base class.
     
     @param string filename: the name of the file to load the settings from
     @return returns true if the settings were loaded successfully, false otherwise
     */
    virtual bool loadModelFromFile(string filename);
    
    /**
     This loads the LowPassFilter settings from a file.
     This overrides the loadModelFromFile function in the PreProcessing base class.
     
     @param fstream &file: a reference to the file to load the settings from
     @return returns true if the model was loaded successfully, false otherwise
     */
    virtual bool loadModelFromFile(fstream &file);

    /**
     Initializes the filter, setting the filter size and dimensionality of the data it will filter.
     Sets all the filter values to zero.
     
     @param double filterFactor: controls the low pass filter, a smaller value will result in a more aggresive smoothing of the input signal
     @param double gain: multiples the filtered values by a constant ampltidue
     @param UINT numDimensions: the dimensionality of the input data to filter
	 @return true if the filter was initiliazed, false otherwise
     */
    bool init(double filterFactor,double gain,UINT numDimensions);
    
    /**
     Filters the input, this should only be called if the dimensionality of the filter was set to 1.
     
     @param const double x: the value to filter, this should only be called if the dimensionality of the filter was set to 1
	 @return the filtered value.  Zero will be returned if the value was not filtered
     */
    double filter(const double x);
    
    /**
     Filters the input, the dimensionality of the input vector should match that of the filter.
     
     @param const VectorDouble  &x: the values to filter, the dimensionality of the input vector should match that of the filter
	 @return the filtered values.  An empty vector will be returned if the values were not filtered
     */
    VectorDouble filter(const VectorDouble &x);
    
    /**
     Sets the gain of the low pass filter.
     This will also reset the filter.
     
     @param double gain: the new gain value, this multiples the filtered values by a constant ampltidue
	 @return true if the gain value was set, false otherwise
     */
    bool setGain(double gain);
    
    /**
     Sets the filter factor, this controls the low pass filter, a smaller value will result in a more aggresive smoothing of the input signal. 
     This should be a value in the range [0.0 1.0].
     This will also reset the filter.
     
     @param double filterFactor: the new filterFactor value
	 @return true if the filterFactor value was set, false otherwise
     */
    bool setFilterFactor(double filterFactor);
    
    /**
     Sets the cutoff frequency of the filter, this updates the filterFactor.  The cutoffFrequency should in Hz.
     This will also reset the filter.
     
     @param double cutoffFrequency: the cutoff frequency of the filter in Hz
     @param double delta: the sampling rate of your sensor, delta should be set as 1.0/SR, where SR is the sampling rate of your sensor
	 @return true if the filterFactor value was set, false otherwise
     */
    bool setCutoffFrequency(double cutoffFrequency,double delta);
    
    /**
     Gets the current filter factor if the filter has been initialized.
     
	 @return the current filter factor if the filter has been initialized, zero otherwise
     */
    double getFilterFactor(){ if( initialized ){ return filterFactor; } return 0; }
    
    /**
     Gets the current gain value if the filter has been initialized.
     
	 @return the currentgain value if the filter has been initialized, zero otherwise
     */
    double getGain(){ if( initialized ){ return gain; } return 0; }
    
    /**
     Returns the last value(s) that were filtered.
     
	 @return the filtered values.  An empty vector will be returned if the values were not filtered
     */
    VectorDouble getFilteredValues(){ if( initialized ){ return yy; } return vector< double >(); }

protected:
    double filterFactor;                ///< The filter factor (alpha) of the filter
    double gain;                        ///< The gain factor of the filter
	VectorDouble yy;                ///< The previous output value(s)
    
    static RegisterPreProcessingModule< LowPassFilter > registerModule;
};

}//End of namespace GRT

#endif //GRT_LOW_PASS_FILTER_HEADER
