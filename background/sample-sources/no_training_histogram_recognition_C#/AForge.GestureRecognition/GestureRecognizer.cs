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

    using AForge;
    using AForge.Imaging;
    using AForge.Imaging.Filters;
    using AForge.Math;

    /// <summary>
    /// Gesture recognizer from still image.
    /// </summary>
    /// 
    /// <remarks>
    /// <para>The class processes specified image of human's body, trying to recognize hands'
    /// gesture.</para>
    /// 
    /// <para><note>The class processes only binary (8 bpp indexed) images, where white color
    /// is represented by 255 value (black is 0).</note></para>
    /// 
    /// <para>Sample usage:</para>
    /// <code>
    /// // create gesture recognizer instance
    /// GestureRecognizer recognizer = new GestureRecognizer( );
    /// // recognize gesture
    /// Gesture gesture = recognizer.Recognize( image );
    /// // process gesture
    /// if (
    ///     ( gesture.LeftHand  != HandPosition.NotRaised ) ||
    ///     ( gesture.RightHand != HandPosition.NotRaised )
    ///     )
    /// {
    ///     // ...
    /// }
    /// </code>
    /// </remarks>
    /// 
    public class GestureRecognizer
    {
        // the coefficient to build map of hands and torso
        private double torsoCoefficient = 0.3;

        // minimal raised hands proportion
        private double handsMinProportion = 0.3;

        // minimal straight hand proportion
        private double minStraightHandProportion = 1.33;

        // maximal raised up hand proportion
        private double maxRaisedUpHandProportion = 0.35;

        /// <summary>
        /// Torso coefficient.
        /// </summary>
        /// 
        /// <remarks>
        /// <para>The coefficient is used to find hands and torso on the initial image.
        /// Horizontal image histogram is scanned and all areas, where proportion
        /// of object's height to image height is greater then the this coefficient, are
        /// treated as torso are.</para>
        /// <para>Minimal possible value is 0. Maximal possible value is 1. Default value is
        /// set to 0.3.</para>
        /// </remarks>
        /// 
        public double TorsoCoefficient
        {
            get { return torsoCoefficient; }
            set { torsoCoefficient = Math.Max( 0, Math.Min( 1, value ) ); }
        }

        /// <summary>
        /// Minimal raised hands proportion.
        /// </summary>
        /// 
        /// <remarks>
        /// <para>The value sets minimal proportion of hand to torso width. If hand
        /// on the processing image has proportion, which is less then this value, then
        /// this hand is treated as not raised.</para>
        /// 
        /// <para>Minimal possible value is 0. Default value is set to 0.3.</para>
        /// </remarks>
        /// 
        public double HandsMinProportion
        {
            get { return handsMinProportion; }
            set { handsMinProportion = Math.Max( 0, value ); }
        }

        /// <summary>
        /// Minimal straight hand proportion.
        /// </summary>
        /// 
        /// <remarks>
        /// <para>The value sets minimal proportion of straight hand's width to its height.
        /// If hand on a processing image has proportion greater then this value, then the
        /// hand is treated as straight. Otherwise it is treated as diagonal.</para>
        /// 
        /// <para>Minimal possible value is 0. Default value is set to 1.3.</para>
        /// </remarks>
        /// 
        public double MinStraightHandProportion
        {
            get { return minStraightHandProportion; }
            set { minStraightHandProportion = Math.Max( 0, value ); }
        }

        /// <summary>
        /// Maximal raised up hand proportion.
        /// </summary>
        /// 
        /// <remarks>
        /// <para>The value sets maximal proportion of free space above raised hand
        /// on the image to hand's height. If proportion of free space above raised
        /// hand on the image is less than this value, then the hand is supposed to
        /// be raised diagonally up. Otherwise it is supposed to be raised diagonally
        /// down.</para>
        /// 
        /// <para>Minimal possible value is 0. Default value is set to 0.35.</para>
        /// </remarks>
        /// 
        public double MaxRaisedUpHandProportion
        {
            get { return maxRaisedUpHandProportion; }
            set { maxRaisedUpHandProportion = Math.Max( 0, value ); }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="GestureRecognizer"/> class.
        /// </summary>
        public GestureRecognizer( ) { }

        /// <summary>
        /// Recognize hands gesture.
        /// </summary>
        /// 
        /// <param name="image">Source image to recognize hands gesture on.</param>
        /// <param name="bodyImageOnly">Specifies if the passed image data contain only human's body or not.</param>
        /// 
        /// <returns>Returns gesture structure, which specifies position of both hands.</returns>
        /// 
        /// <remarks><para>The <b>bodyImageOnly</b>> parameter specifies if human's body occupies the
        /// passes image from top to down and from left to rigth. If the value is set to <b>false</b>,
        /// then humans' body may occupy only part of the image, what will require image shrinking.</para></remarks>
        /// 
        public Gesture Recognize( Bitmap image, bool bodyImageOnly )
        {
            // check source image format
            if ( image.PixelFormat != PixelFormat.Format8bppIndexed )
            {
                throw new ArgumentException( "Source image can be binary (8 bpp indexed) only" );
            }

            // lock source image
            BitmapData imageData = image.LockBits(
                new Rectangle( 0, 0, image.Width, image.Height ),
                ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed );

            // process the image
            Gesture gesture = Recognize( imageData, bodyImageOnly );

            // unlock image
            image.UnlockBits( imageData );

            return gesture;
        }

        /// <summary>
        /// Recognize hands gesture.
        /// </summary>
        /// 
        /// <param name="imageData">Source image data to recognize hands gesture on.</param>
        /// <param name="bodyImageOnly">Specifies if the passed image data contain only human's body or not.</param>
        /// 
        /// <returns>Returns gesture structure, which specifies position of both hands.</returns>
        /// 
        /// <remarks><para>The <b>bodyImageOnly</b>> parameter specifies if human's body occupies the
        /// passes image from top to down and from left to rigth. If the value is set to <b>false</b>,
        /// then humans' body may occupy only part of the image, what will require image shrinking.</para></remarks>
        /// 
        public Gesture Recognize( BitmapData imageData, bool bodyImageOnly )
        {
            // check source image format
            if ( imageData.PixelFormat != PixelFormat.Format8bppIndexed )
            {
                throw new ArgumentException( "Source image can be binary (8 bpp indexed) only" );
            }

            // recognized gesture
            Gesture gesture = new Gesture( HandPosition.NotRaised, HandPosition.NotRaised );

            Bitmap bodyImage = null;
            BitmapData bodyImageData = null;

            if ( bodyImageOnly == false )
            {
                // use shrink filter to extract only body image
                Shrink shrinkFilter = new Shrink( );
                bodyImage = shrinkFilter.Apply( imageData );

                // lock body image for further processing
                bodyImageData = bodyImage.LockBits(
                    new Rectangle( 0, 0, bodyImage.Width, bodyImage.Height ),
                    ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed );
            }
            else
            {
                // use passed image as body image
                bodyImageData = imageData;
            }

            int bodyWidth = bodyImageData.Width;
            int bodyHeight = bodyImageData.Height;

            // get statistics about horizontal pixels distribution 
            HorizontalIntensityStatistics his = new HorizontalIntensityStatistics( bodyImageData );
            int[] hisValues = (int[]) his.Gray.Values.Clone( );

            // build map of hands (0) and torso (1)
            double torsoLimit = torsoCoefficient * bodyHeight;

            for ( int i = 0; i < bodyWidth; i++ )
            {
                hisValues[i] = ( (double) hisValues[i] / 255 > torsoLimit ) ? 1 : 0;
            }

            // get hands' length
            int leftHand = 0;
            while ( ( hisValues[leftHand] == 0 ) && ( leftHand < bodyWidth ) )
                leftHand++;

            int rightHand = bodyWidth - 1;
            while ( ( hisValues[rightHand] == 0 ) && ( rightHand > 0 ) )
                rightHand--;
            rightHand = bodyWidth - ( rightHand + 1 );

            // get torso's width
            int torsoWidth = bodyWidth - leftHand - rightHand;

            // process left hand
            if ( ( (double) leftHand / torsoWidth ) >= handsMinProportion )
            {
                // extract left hand's image
                Crop cropFilter = new Crop( new Rectangle( 0, 0, leftHand, bodyHeight ) );
                Bitmap leftHandImage = cropFilter.Apply( bodyImageData );

                // get left hand's position
                gesture.LeftHand = GetHandPosition( leftHandImage );
            }

            // process right hand
            if ( ( (double) rightHand / torsoWidth ) >= handsMinProportion )
            {
                // extract right hand's image
                Crop cropFilter = new Crop( new Rectangle( bodyWidth - rightHand, 0, rightHand, bodyHeight ) );
                Bitmap rightHandImage = cropFilter.Apply( bodyImageData );

                // get right hand's position
                gesture.RightHand = GetHandPosition( rightHandImage );
            }

            if ( !bodyImageOnly )
            {
                // unlock body image and dispose it
                bodyImage.UnlockBits( bodyImageData );
                bodyImage.Dispose( );
            }

            return gesture;
        }

        /// <summary>
        /// Estimate hand position on the specified image.
        /// </summary>
        /// 
        /// <param name="handImage">Hand image to processþ</param>
        /// 
        /// <returns>Returns detected hand's position.</returns>
        /// 
        private HandPosition GetHandPosition( Bitmap handImage )
        {
            HandPosition handPosition = HandPosition.NotRaised;

            // get vertical intensity statistics of the hand
            VerticalIntensityStatistics stat = new VerticalIntensityStatistics( handImage );
            Histogram histogram = stat.Gray;

            // do histogram's preprocessing
            FilterLowValues( histogram );
            FilterNoisyPeaks( histogram );

            if ( ( (double) handImage.Width / ( histogram.Max - histogram.Min + 1 ) ) > minStraightHandProportion )
            {
                handPosition = HandPosition.RaisedStraigh;
            }
            else
            {
                if ( ( (double) histogram.Min / ( histogram.Max - histogram.Min + 1 ) ) < maxRaisedUpHandProportion )
                {
                    handPosition = HandPosition.RaisedDiagonallyUp;
                }
                else
                {
                    handPosition = HandPosition.RaisedDiagonallyDown;
                }
            }

            return handPosition;
        }

        /// <summary>
        /// Filter histogram's low values.
        /// </summary>
        /// 
        /// <param name="histogram">Histogram to filter.</param>
        /// 
        private void FilterLowValues( Histogram histogram )
        {
            int[] values = histogram.Values;
            int   globalMax = 0;

            // find global maximum value
            for ( int k = 0; k < values.Length; k++ )
            {
                if ( values[k] > globalMax )
                {
                    globalMax = values[k];
                }
            }

            // filter values, which are below 10% of max
            int filterLevel = (int) ( (double) globalMax / 10 );

            // do filtering
            for ( int k = 0; k < values.Length; k++ )
            {
                if ( values[k] <= filterLevel )
                {
                    values[k] = 0;
                }
            }

            histogram.Update( );
        }

        /// <summary>
        /// Remove peaks from the histogram, which don't contain maximum value.
        /// </summary>
        /// 
        /// <param name="histogram">Histogram to process.</param>
        /// 
        private void FilterNoisyPeaks( Histogram histogram )
        {
            int[] values = histogram.Values;
            int   globalMax = 0;

            // find global maximum value
            for ( int k = 0; k < values.Length; k++ )
            {
                if ( values[k] > globalMax )
                {
                    globalMax = values[k];
                }
            }

            int i = 0;

            // process all peaks
            while ( i < values.Length )
            {
                // find start of next peak
                while ( ( i < values.Length ) && ( values[i] == 0 ) )
                {
                    i++;
                }

                int localMax = 0;

                // find peak's maximum value
                while ( ( i < values.Length ) && ( values[i] != 0 ) )
                {
                    if ( values[i] > localMax )
                    {
                        localMax = values[i];
                    }
                    i++;
                }

                // remove this peak if it does not contain global maximum
                if ( localMax < globalMax )
                {
                    int j = i - 1;

                    while ( ( j >= 0 ) && ( values[j] != 0 ) )
                    {
                        values[j] = 0;
                        j--;
                    }
                }
            }

            histogram.Update( );
        }
    }
}
