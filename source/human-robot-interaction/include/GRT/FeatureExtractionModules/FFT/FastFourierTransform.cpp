/*
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

/*
 This code is based on Dominic Mazzoni's c++ wrapper, which is based on a free implementation of an FFT
 by Don Cross (http://www.intersrv.com/~dcross/fft.html) and the FFT algorithms from Numerical Recipes.
 */

#include "FastFourierTransform.h"	


namespace GRT{

FastFourierTransform::FastFourierTransform(){
    initialized = false;
    computeMagnitude = true;
    computePhase = true;
    windowSize = 0;
    windowFunction = RECTANGULAR_WINDOW;
    averagePower = 0;
    
    infoLog.setProceedingText("[FastFourierTransform]");
    warningLog.setProceedingText("[WARNING FastFourierTransform]");
    errorLog.setProceedingText("[ERROR FastFourierTransform]");
    
    initFFT();
}
    
FastFourierTransform::FastFourierTransform(const FastFourierTransform &rhs){

    this->initialized = rhs.initialized;
    this->computeMagnitude = rhs.computeMagnitude;
    this->computePhase = rhs.computePhase;
    this->windowSize = rhs.windowSize;
    this->windowFunction = rhs.windowFunction;
    this->averagePower = 0;
    this->initFFT();
    this->infoLog = rhs.infoLog;
    this->warningLog = rhs.warningLog;
    this->errorLog = rhs.errorLog;
    
    if( rhs.initialized ){
        this->init(rhs.windowSize,rhs.windowFunction,rhs.computeMagnitude,rhs.computePhase);
        
        //Copy the fft results
        for(UINT i=0; i<this->windowSize; i++){
            this->fftReal[i] = rhs.fftReal[i];
            this->fftImag[i] = rhs.fftImag[i];
            this->magnitude[i] = rhs.magnitude[i];
            this->phase[i] = rhs.phase[i];
            this->power[i] = rhs.power[i];
        }
    }
}

FastFourierTransform::~FastFourierTransform() {

}
    
FastFourierTransform& FastFourierTransform::operator=(const FastFourierTransform &rhs){
    
    if( this != &rhs ){
        this->initialized = rhs.initialized;
        this->computeMagnitude = rhs.computeMagnitude;
        this->computePhase = rhs.computePhase;
        this->windowSize = rhs.windowSize;
        this->windowFunction = rhs.windowFunction;
        this->averagePower = 0;
        this->initFFT();
        
        if( rhs.initialized ){
            this->init(rhs.windowSize,rhs.windowFunction,rhs.computeMagnitude,rhs.computePhase);
            
            //Copy the fft results
            for(UINT i=0; i<this->windowSize; i++){
                this->fftReal[i] = rhs.fftReal[i];
                this->fftImag[i] = rhs.fftImag[i];
                this->magnitude[i] = rhs.magnitude[i];
                this->phase[i] = rhs.phase[i];
                this->power[i] = rhs.power[i];
            }
        }
    }
    return *this;
}
    
bool FastFourierTransform::init(const unsigned int windowSize,const unsigned int windowFunction,const bool computeMagnitude,const bool computePhase){
    
    initialized = false;
    averagePower = 0;
    
    //Validate the window size
    if( !isPowerOfTwo( windowSize ) ){
        return false;
    }
    
    if( windowFunction != RECTANGULAR_WINDOW && windowFunction != BARTLETT_WINDOW && 
        windowFunction != HAMMING_WINDOW && windowFunction != HANNING_WINDOW ){
        return false;
    }
    
    initFFT();
    
    this->windowSize = windowSize;
    this->windowFunction = windowFunction;
    this->computeMagnitude = computeMagnitude;
    this->computePhase = computePhase;
    
    //Init the memory
    fftReal.resize( windowSize );
    fftImag.resize( windowSize );
    tmpReal.resize( windowSize/2 );
    tmpImag.resize( windowSize/2 );
    magnitude.resize( windowSize );
    phase.resize( windowSize );
    power.resize( windowSize );
    averagePower = 0;
    
    //Zero the memory
    for(UINT i=0; i<windowSize/2; i++){
        tmpReal[i] = 0;
        tmpImag[i] = 0;
    }
    for(UINT i=0; i<windowSize; i++){
        fftReal[i] = 0;
        fftImag[i] = 0;
        magnitude[i] = 0;
        phase[i] = 0;
        power[i] = 0;
    }
    
    //Flag that the FFT has been initialized
    initialized = true;
    
    return true;
}

bool FastFourierTransform::computeFFT( VectorDouble &data ){
    
    if( !initialized ){
        return false;
    }
    
    //Window the input data
    if( !windowData( data ) ){
        return false;
    }
    
    //Perform the FFT
    realFFT(data, &fftReal[0], &fftImag[0]);
	
    averagePower = 0;
    
    for(unsigned int i = 0; i<windowSize/2; i++){
        
        if( computeMagnitude ){
            power[i] = fftReal[i]*fftReal[i] + fftImag[i]*fftImag[i];
            averagePower += power[i];
            magnitude[i] = 2.0*sqrt( power[i] );
        }
        
        if( computePhase ){
            phase[i] = atan2(fftImag[i],fftReal[i]);
        }
    }

    //Compute the average power
    averagePower = averagePower / (double)(windowSize/2);
    
    return true;
}
    
bool FastFourierTransform::windowData( VectorDouble &data ){
    
    if( data.size() != windowSize ){
        errorLog << "The size of the data vector (" << data.size() << ") does not match the windowSize: " << windowSize << endl;
        return false;
    }
    
    switch( windowFunction ){
        case RECTANGULAR_WINDOW:
            return true;
            break;
        case BARTLETT_WINDOW:
            for(unsigned int i=0; i<windowSize/2; i++) {
                data[i] *= (i / (double) (windowSize / 2));
                data[i + (windowSize/2)] *= (1.0 - (i / (double) (windowSize/2)));
            }
            return true;
            break;
        case HAMMING_WINDOW:
            for(unsigned int i=0; i<windowSize; i++)
                data[i] *= 0.54 - 0.46 * cos(2 * PI * i / (windowSize - 1));
            return true;
            break;
        case HANNING_WINDOW:
            for(unsigned int i=0; i <windowSize; i++)
                data[i] *= 0.50 - 0.50 * cos(2 * PI * i / (windowSize - 1));
            return true;
            break;
        default:
            return false;
            break;
    }
    
    return false;
}
    
VectorDouble FastFourierTransform::getMagnitudeData(){
    
    if( !initialized ) return VectorDouble();
    
    VectorDouble magnitudeData(windowSize/2);
    
    for(unsigned int i=0; i<windowSize/2; i++){
        magnitudeData[i] = magnitude[i];
    }
    
    return magnitudeData;
}

VectorDouble FastFourierTransform::getPhaseData(){
    if( !initialized ) return VectorDouble();
    
    VectorDouble phaseData(windowSize/2);
    
    for(unsigned int i=0; i<windowSize/2; i++){
        phaseData[i] = phase[i];
    }
    
    return phaseData;
}

VectorDouble FastFourierTransform::getPowerData(){
    if( !initialized ) return VectorDouble();
    
    VectorDouble powerData(windowSize/2);
    
    for(unsigned int i=0; i<windowSize/2; i++){
        powerData[i] = power[i];
    }
    
    return powerData;
}
    
double FastFourierTransform::getAveragePower(){
    return averagePower;
}
    
double* FastFourierTransform::getMagnitudeDataPtr(){
    return &magnitude[0];
}

double* FastFourierTransform::getPhaseDataPtr(){
    return &phase[0];
}

double* FastFourierTransform::getPowerDataPtr(){
    return &power[0];
}
    
/*
 * Real Fast Fourier Transform
 *
 * This function was based on the code in Numerical Recipes in C.
 * In Num. Rec., the inner loop is based on a single 1-based array
 * of interleaved real and imaginary numbers.  Because we have two
 * separate zero-based arrays, our indices are quite different.
 * Here is the correspondence between Num. Rec. indices and our indices:
 *
 * i1  <->  real[i]
 * i2  <->  imag[i]
 * i3  <->  real[n/2-i]
 * i4  <->  imag[n/2-i]
 */

bool FastFourierTransform::realFFT( const VectorDouble &realIn, double *realOut, double *imagOut ){
    int NumSamples = (int)windowSize;
    int Half = NumSamples / 2;
    int i;
    
    double theta = PI / Half;
    
    for (i = 0; i < Half; i++) {
        tmpReal[i] = realIn[2 * i];
        tmpImag[i] = realIn[2 * i + 1];
    }
    
    if( !FFT(Half, 0, &tmpReal[0], &tmpImag[0], realOut, imagOut) ){
        return false;
    }
    
    double wtemp = double(sin(0.5 * theta));
    
    double wpr = -2.0 * wtemp * wtemp;
    double wpi = double (sin(theta));
    double wr = 1.0 + wpr;
    double wi = wpi;
    
    int i3;
    
    double h1r, h1i, h2r, h2i;
    
    for (i = 1; i < Half / 2; i++) {
        
        i3 = Half - i;
        
        h1r = 0.5 * (realOut[i] + realOut[i3]);
        h1i = 0.5 * (imagOut[i] - imagOut[i3]);
        h2r = 0.5 * (imagOut[i] + imagOut[i3]);
        h2i = -0.5 * (realOut[i] - realOut[i3]);
        
        realOut[i] = h1r + wr * h2r - wi * h2i;
        imagOut[i] = h1i + wr * h2i + wi * h2r;
        realOut[i3] = h1r - wr * h2r + wi * h2i;
        imagOut[i3] = -h1i + wr * h2i + wi * h2r;
        
        wr = (wtemp = wr) * wpr - wi * wpi + wr;
        wi = wi * wpr + wtemp * wpi + wi;
    }
    
    realOut[0] = (h1r = realOut[0]) + imagOut[0];
    imagOut[0] = h1r - imagOut[0];
    
    return true;
}

bool FastFourierTransform::FFT(int numSamples,bool inverseTransform,double *realIn, double *imagIn, double *realOut, double *imagOut){
    int NumBits;                 /* Number of bits needed to store indices */
    int i, j, k, n;
    int BlockSize, BlockEnd;
    
    double angle_numerator = 2.0 * PI;
    double tr, ti;                /* temp real, temp imaginary */
    
    if( !isPowerOfTwo(numSamples) ) {
        fprintf(stderr, "%d is not a power of two\n", numSamples);
        return false;
    }
    
    if( bitTable.size() == 0 ) initFFT();
    
    if( inverseTransform ) angle_numerator = -angle_numerator;
    
    NumBits = numberOfBitsNeeded(numSamples);
    
    //Simultaneously data copy and bit-reversal ordering into outputs...
    for(i = 0; i < numSamples; i++) {
        j = fastReverseBits(i, NumBits);
        realOut[j] = realIn[i];
        imagOut[j] = (imagIn == NULL) ? 0.0 : imagIn[i];
    }
    
    //Do the FFT
    BlockEnd = 1;
    for (BlockSize = 2; BlockSize <= numSamples; BlockSize <<= 1) {
        
        double delta_angle = angle_numerator / (double) BlockSize;
        
        double sm2 = sin(-2 * delta_angle);
        double sm1 = sin(-delta_angle);
        double cm2 = cos(-2 * delta_angle);
        double cm1 = cos(-delta_angle);
        double w = 2 * cm1;
        double ar0, ar1, ar2, ai0, ai1, ai2;
        
        for (i = 0; i < numSamples; i += BlockSize) {
            ar2 = cm2;
            ar1 = cm1;
            
            ai2 = sm2;
            ai1 = sm1;
            
            for (j = i, n = 0; n < BlockEnd; j++, n++) {
                ar0 = w * ar1 - ar2;
                ar2 = ar1;
                ar1 = ar0;
                
                ai0 = w * ai1 - ai2;
                ai2 = ai1;
                ai1 = ai0;
                
                k = j + BlockEnd;
                tr = ar0 * realOut[k] - ai0 * imagOut[k];
                ti = ar0 * imagOut[k] + ai0 * realOut[k];
                
                realOut[k] = realOut[j] - tr;
                imagOut[k] = imagOut[j] - ti;
                
                realOut[j] += tr;
                imagOut[j] += ti;
            }
        }
        
        BlockEnd = BlockSize;
    }
    
    //Need to normalize the results if we are computing the inverse transform
    if( inverseTransform ){
        double denom = (double) numSamples;
        
        for(i = 0; i < numSamples; i++) {
            realOut[i] /= denom;
            imagOut[i] /= denom;
        }
    }
    
    return true;
}
    
int FastFourierTransform::numberOfBitsNeeded(int powerOfTwo)
{
    for (int i = 0;; i++){
        if (powerOfTwo & (1 << i)){
            return i;
        }
    }
    return 0;
}

int FastFourierTransform::reverseBits(int index, int numBits)
{
    int i, rev;
    
    for (i = rev = 0; i < numBits; i++) {
        rev = (rev << 1) | (index & 1);
        index >>= 1;
    }
    
    return rev;
}

void FastFourierTransform::initFFT()
{
    bitTable.resize( MAX_FAST_BITS );
    
    int len = 2;
    for (int b = 1; b <= MAX_FAST_BITS; b++) {
        
        bitTable[b - 1].resize(len);
        
        for (int i = 0; i < len; i++)
            bitTable[b - 1][i] = reverseBits(i, b);
        
        len <<= 1;
    }
}

inline int FastFourierTransform::fastReverseBits(const int i, const int numBits)
{
    if (numBits <= MAX_FAST_BITS)
        return bitTable[numBits - 1][i];
    else
        return reverseBits(i, numBits);
}
    
inline bool FastFourierTransform::isPowerOfTwo(const unsigned int x){
    if (x < 2) return false;
    if (x & (x - 1)) return false;
    return true;
}

}//End of namespace GRT