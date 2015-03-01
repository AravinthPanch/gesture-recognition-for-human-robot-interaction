// Gesture Recognition Module
//
// Copyright © Andrew Kirillov, 2008
// andrew.kirillov@gmail.com
//

namespace AForge.GestureRecognition
{
    using System;
    using System.Drawing;
    using System.Drawing.Imaging;
    using System.Runtime.InteropServices;

    using AForge.Imaging;
    using AForge.Imaging.Filters;

    /// <summary>
    /// Delegate to notify about detected and recognized gesture.
    /// </summary>
    /// 
    /// <param name="sender">Sender object.</param>
    /// <param name="gesture">Recognized gesture.</param>
    /// 
    public delegate void GestureDetectionEventHandler( object sender, Gesture gesture );

    /// <summary>
    /// Gesture recognizer from video feed.
    /// </summary>
    /// 
    /// <remarks><para>The class processes video feed recognizing gestures of human's bodies.
    /// The processing algorithm first of all tries to locate big object, which is presumably
    /// human body. When the object is not moving for a while, the algorithms tries to recognize
    /// its gesture. In the case of successfull recognition, the class fires an event.</para>
    /// 
    /// <para>Sample usage:</para>
    /// <code>
    /// // create motion detector with noise suppresion
    /// GesturesRecognizerFromVideo recognizer = new GesturesRecognizerFromVideo( );
    /// // register delagate for the event
    /// recognizer.GestureDetected += new GestureDetectionEventHandler( recognizer_GestureDetected );
    /// // feed images in the loop
    /// while ( ... )
    /// {
    ///     recognizer.ProcessFrame( image );
    /// }
    /// // ...
    /// 
    /// // On gesture recognized (somewhere in the code)
    /// private void recognizer_GestureDetected( object sender, Gesture gesture )
    /// {
    ///     // ... process recognized gesture
    /// }
    /// 
    /// </code>
    /// </remarks>
    /// 
    public class GesturesRecognizerFromVideo
    {
        // frame's dimension
        private int width;
        private int height;
        private int frameSize;

        // background and previous frames
        private Bitmap backgroundFrame = null;
        private Bitmap previousFrame = null;

        // filters used to do image processing
        private GrayscaleBT709 grayscaleFilter = new GrayscaleBT709( );
        private Difference differenceFilter = new Difference( );
        private Threshold thresholdFilter = new Threshold( 25 );
        private Erosion erosionFilter = new Erosion( );
        private Opening openingFilter = new Opening( );
        private MoveTowards moveTowardsFilter = new MoveTowards( );
        private BlobsFiltering blobsFilter = new BlobsFiltering( 50, 50, 1000, 1000 );

        // blobs counter
        private BlobCounter blobCounter = new BlobCounter( );

        // gesture recognizer from still image
        private GestureRecognizer gestureRecognizer = new GestureRecognizer( );

        // gesture detection flag
        private bool notDetected = true;
        // gesture detected on a previous video frame
        private Gesture previousGesture = new Gesture( );

        // number of frames passed without motion of big object
        private int framesWithoutMotion = 0;
        // number of frames passed without gesture change
        private int framesWithoutGestureChange = 0;

        // minimum body size
        private int minBodyWidth = 50;
        private int minBodyHeight = 50;

        // motion limit
        private double motionLimit = 0.005;

        // minimal amount of frames without motion
        private int minFramesWithoutMotion = 3;

        // minimal amount of frames without gesture change
        private int minFramesWithoutGestureChange = 1;

        /// <summary>
        /// Gestture recognizer from still images.
        /// </summary>
        ///
        /// <remarks>The property allows to access <see cref="GestureRecognizer"/> instance and alter its
        /// properties.</remarks>
        ///
        public GestureRecognizer GestureRecognizer
        {
            get { return gestureRecognizer; }
        }

        /// <summary>
        /// Minimum acceptable body width.
        /// </summary>
        /// 
        /// <remarks><para>The property sets minimum object's width, which is treated as human body. All objects
        /// with width less then this value are not treated as human body and are not passed to gesture
        /// recognition algorithm.</para>
        /// <para>Default value is set to 50.</para>
        /// </remarks>
        /// 
        public int MinBodyWidth
        {
            get { return minBodyWidth; }
            set
            {
                minBodyWidth = value;
                blobsFilter.MinWidth = minBodyWidth;
            }
        }

        /// <summary>
        /// Minimum acceptable body height.
        /// </summary>
        /// 
        /// <remarks><para>The property sets minimum object's height, which is treated as human body. All objects
        /// with height less then this value are not treated as human body and are not passed to gesture
        /// recognition algorithm.</para>
        /// <para>Default value is set to 50.</para>
        /// </remarks>
        /// 
        public int MinBodyHeight
        {
            get { return minBodyHeight; }
            set
            {
                minBodyHeight = value;
                blobsFilter.MinHeight = minBodyHeight;
            }
        }

        /// <summary>
        /// Motion limit, which is used to avoid gesture detection of moving object.
        /// </summary>
        /// 
        /// <remarks><para>Once a big moving object is detect (presumably human body), gesture recognition algorithm
        /// may try to recognize its gesture. To avoid gesture recognition of moving object, the video processing
        /// module waits certain amount of frames without motion (<see cref="MinFramesWithoutMotion"/>). When object
        /// is not moving for a while, gesture recognition algorithm tries to recognize the gesture.</para>
        /// <para>The property sets limit of changed pixels to detect motion. If number of changed pixels between
        /// two continuous frames is greater than this value, then object is supposed to be moving. Otherwise object
        /// is not moving and gesture recognition may occur.</para>
        /// <para>Minimal possible value is 0. Maximal possible value is 1. Default value is set 0.005 (0.5%).</para>
        /// </remarks>
        /// 
        public double MotionLimit
        {
            get { return motionLimit; }
            set { motionLimit = Math.Max( 0, Math.Min( 1, value ) ); }
        }

        /// <summary>
        /// Minimual amount of frames without motion before passing current frame to gesture recognition.
        /// </summary>
        /// 
        /// <remarks><para>The property sets the amount of frames, which should pass without motion detection,
        /// before gesture recognition algorithm starts to recognize gesture on a current frame.</para>
        /// <para>Default value is set to 3.</para>
        /// </remarks>
        /// 
        public int MinFramesWithoutMotion
        {
            get { return minFramesWithoutMotion; }
            set { minFramesWithoutMotion = value; }
        }

        /// <summary>
        /// Minimal amount of frames without gesture changes before signaling about recognized gesture.
        /// </summary>
        /// 
        /// <remarks><para>The property is required to avoid false gesture recognitions. If the same gesture
        /// is recognized during specified amount of continues frames, then it is supposed to be recognized
        /// correctly.</para>
        /// <para>Default value is set to 1.</para>
        /// <para><note>If the property is set to 0, then it means that first recognized gesture is treated as
        /// valid - further frames are not checked.</note></para>
        /// </remarks>
        /// 
        public int MinFramesWithoutGestureChange
        {
            get { return minFramesWithoutGestureChange; }
            set { minFramesWithoutGestureChange = value; }
        }

        /// <summary>
        /// Event to notify about detected and recognized gesture.
        /// </summary>
        public event GestureDetectionEventHandler GestureDetected;

        /// <summary>
        /// Initializes a new instance of the <see cref="GesturesRecognizerFromVideo"/> class.
        /// </summary>
        /// 
        public GesturesRecognizerFromVideo( )
        {
            blobsFilter.MinWidth  = minBodyWidth;
            blobsFilter.MinHeight = minBodyHeight;
        }

        /// <summary>
        /// Reset gesture recognition engine to initial state.
        /// </summary>
        /// 
        /// <remarks>The method resets the engine to initial state, resetting all internal variable
        /// to the same state like after class instantiation.</remarks>
        /// 
        public void Reset( )
        {
            // dispose background frame
            if ( backgroundFrame != null )
            {
                backgroundFrame.Dispose( );
                backgroundFrame = null;
            }

            // dispose previous frame
            if ( previousFrame != null )
            {
                previousFrame.Dispose( );
                previousFrame = null;
            }

            // reset counters
            framesWithoutMotion = 0;
            framesWithoutGestureChange = 0;
            notDetected = true;
        }

        /// <summary>
        /// Process new frame.
        /// </summary>
        /// 
        /// <remarks>Process new frame of video source and try to recognize gesture.</remarks>
        /// 
        public void ProcessFrame( ref Bitmap image )
        {
            // check background frame
            if ( backgroundFrame == null )
            {
                // save image dimension
                width     = image.Width;
                height    = image.Height;
                frameSize = width * height;

                // create initial backgroung image
                backgroundFrame = grayscaleFilter.Apply( image );

                return;
            }

            // check image dimension
            if ( ( image.Width != width ) || ( image.Height != height ) )
                return;

            // apply the grayscale filter
            Bitmap currentFrame = grayscaleFilter.Apply( image );

            // set backgroud frame as an overlay for difference filter
            differenceFilter.OverlayImage = backgroundFrame;

            // apply difference filter
            Bitmap motionObjectsImage = differenceFilter.Apply( currentFrame );

            // lock motion objects image for further faster processing
            BitmapData motionObjectsData = motionObjectsImage.LockBits(
                new Rectangle( 0, 0, width, height ),
                ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed );
            
            // apply threshold filter
            thresholdFilter.ApplyInPlace( motionObjectsData );

            // apply opening filter to remove noise
            openingFilter.ApplyInPlace( motionObjectsData );

            // process blobs
            blobCounter.ProcessImage( motionObjectsData );
            Blob[] blobs = blobCounter.GetObjectInformation( );

            int maxSize = 0;
            Blob maxObject = new Blob( 0, new Rectangle( 0, 0, 0, 0 ) );

            // find biggest blob
            if ( blobs != null )
            {
                foreach ( Blob blob in blobs )
                {
                    int blobSize = blob.Rectangle.Width * blob.Rectangle.Height;

                    if ( blobSize > maxSize )
                    {
                        maxSize = blobSize;
                        maxObject = blob;
                    }
                }
            }

            // if we have only small objects then let's adopt to changes in the scene
            if ( ( maxObject.Rectangle.Width < 20 ) || ( maxObject.Rectangle.Height < 20 ) )
            {
                // move background towards current frame
                moveTowardsFilter.OverlayImage = currentFrame;
                moveTowardsFilter.ApplyInPlace( backgroundFrame );
            }

            if ( ( maxObject.Rectangle.Width >= minBodyWidth ) && ( maxObject.Rectangle.Height >= minBodyHeight ) && ( previousFrame != null ) )
            {
                // check motion level between frames
                differenceFilter.OverlayImage = previousFrame;

                // apply difference filter
                Bitmap betweenFramesMotion = differenceFilter.Apply( currentFrame );

                // lock image with between frames motion for faster further processing
                BitmapData betweenFramesMotionData = betweenFramesMotion.LockBits(
                    new Rectangle( 0, 0, width, height ),
                    ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed );

                // apply threshold filter
                thresholdFilter.ApplyInPlace( betweenFramesMotionData );

                // apply opening filter to remove noise
                openingFilter.ApplyInPlace( betweenFramesMotionData );

                // calculate amount of changed pixels
                VerticalIntensityStatistics vis = new VerticalIntensityStatistics( betweenFramesMotionData );

                int[] histogram = vis.Gray.Values;
                int   changedPixels = 0;

                for ( int i = 0, n = histogram.Length; i < n; i++ )
                {
                    changedPixels += histogram[i] / 255;
                }

                // free temporary image
                betweenFramesMotion.UnlockBits( betweenFramesMotionData );
                betweenFramesMotion.Dispose( );

                // check motion level
                if ( (double) changedPixels / frameSize <= motionLimit )
                {
                    framesWithoutMotion++;
                }
                else
                {
                    // reset counters
                    framesWithoutMotion = 0;
                    framesWithoutGestureChange = 0;
                    notDetected = true;
                }

                // check if we don't have motion for a while
                if ( framesWithoutMotion >= minFramesWithoutMotion )
                {
                    if ( notDetected )
                    {
                        // extract the biggest blob
                        blobCounter.ExtractBlobsImage( motionObjectsData, maxObject );

                        // recognize gesture from the image
                        Gesture gesture = gestureRecognizer.Recognize( maxObject.Image, true );
                        maxObject.Image.Dispose( );

                        // check if gestures has changed since the previous frame
                        if (
                            ( gesture.LeftHand == previousGesture.LeftHand ) &&
                            ( gesture.RightHand == previousGesture.RightHand )
                            )
                        {
                            framesWithoutGestureChange++;
                        }
                        else
                        {
                            framesWithoutGestureChange = 0;
                        }

                        // check if gesture was not changing for a while
                        if ( framesWithoutGestureChange >= minFramesWithoutGestureChange )
                        {
                            if ( GestureDetected != null )
                            {
                                GestureDetected( this, gesture );
                            }
                            notDetected = false;
                        }

                        previousGesture = gesture;
                    }
                }
            }
            else
            {
                // reset counters
                framesWithoutMotion = 0;
                framesWithoutGestureChange = 0;
                notDetected = true;
            }

            // free motion objects' image
            motionObjectsImage.UnlockBits( motionObjectsData );
            motionObjectsImage.Dispose( );

            // dispose previous frame
            if ( previousFrame != null )
            {
                previousFrame.Dispose( );
            }

            // set current frame to previous
            previousFrame = currentFrame;
        }
    }
}
