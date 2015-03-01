// Hands Gesture Recognition Application
//
// Copyright © Andrew Kirillov, 2008
// andrew.kirillov@gmail.com
//

namespace GesturesRecognition
{
	using System;
	using System.Drawing;
	using System.Threading;

    using AForge.Video;
    using AForge.GestureRecognition;

	/// <summary>
	/// Camera class.
	/// </summary>
    /// 
	public class Camera
	{
		private IVideoSource	videoSource = null;
		private Bitmap			lastFrame = null;
        private string          lastVideoSourceError = null;

        private GesturesRecognizerFromVideo gesturesRecognizer = new GesturesRecognizerFromVideo( );

		// image dimension
		private int width = -1;
        private int height = -1;

        private Gesture gesture = new Gesture( );
        private int gestureShowTime = 0;

		// public events
		public event EventHandler NewFrame;
        public event EventHandler VideoSourceError;

        // Last video frame
		public Bitmap LastFrame
		{
			get { return lastFrame; }
		}

        // Last video source error
        public string LastVideoSourceError
        {
            get { return lastVideoSourceError; }
        }

		// Video frame width
		public int Width
		{
			get { return width; }
		}

		// Vodeo frame height
		public int Height
		{
			get { return height; }
		}

		// Frames received from the last access to the property
		public int FramesReceived
		{
			get { return ( videoSource == null ) ? 0 : videoSource.FramesReceived; }
		}

        // Bytes received from the last access to the property
		public int BytesReceived
		{
			get { return ( videoSource == null ) ? 0 : videoSource.BytesReceived; }
		}

		// Running property
		public bool IsRunning
		{
			get { return ( videoSource == null ) ? false : videoSource.IsRunning; }
		}

		// Constructor
        public Camera( IVideoSource source )
		{
			this.videoSource = source;
			videoSource.NewFrame += new NewFrameEventHandler( video_NewFrame );
            videoSource.VideoSourceError += new VideoSourceErrorEventHandler( video_VideoSourceError );

            gesturesRecognizer.GestureDetected += new GestureDetectionEventHandler( recognizer_GestureDetected );
		}

		// Start video source
		public void Start( )
		{
			if ( videoSource != null )
			{
                gestureShowTime = 0;
				videoSource.Start( );
			}
		}

		// Siganl video source to stop
		public void SignalToStop( )
		{
			if ( videoSource != null )
			{
				videoSource.SignalToStop( );
            }
		}

		// Wait video source for stop
		public void WaitForStop( )
		{
			// lock
			Monitor.Enter( this );

			if ( videoSource != null )
			{
				videoSource.WaitForStop( );
			}
			// unlock
			Monitor.Exit( this );
		}

		// Abort camera
		public void Stop( )
		{
			// lock
			Monitor.Enter( this );

			if ( videoSource != null )
			{
				videoSource.Stop( );
			}

			// unlock
			Monitor.Exit( this );
		}

		// Lock it
		public void Lock( )
		{
			Monitor.Enter( this );
		}

		// Unlock it
		public void Unlock( )
		{
			Monitor.Exit( this );
		}

		// On new frame
		private void video_NewFrame( object sender, NewFrameEventArgs e )
		{
			try
			{
				// lock
				Monitor.Enter( this );

				// dispose old frame
				if ( lastFrame != null )
				{
					lastFrame.Dispose( );
				}

                // reset error
                lastVideoSourceError = null;
                // get new frame
				lastFrame = (Bitmap) e.Frame.Clone( );

				// apply gestures recognizer
                gesturesRecognizer.ProcessFrame( ref lastFrame );

                // check if we need to draw gesture information on top of image
                if ( gestureShowTime > 0 )
                {
                    if ( ( gesture.LeftHand != HandPosition.NotRaised ) || ( gesture.RightHand != HandPosition.NotRaised ) )
                    {
                        Graphics g = Graphics.FromImage( lastFrame );

                        string text = string.Format( "Left  = " + gesture.LeftHand + "\nRight = " + gesture.RightHand );
                        
                        Font drawFont = new Font( "Courier", 13, FontStyle.Bold );
                        SolidBrush drawBrush = new SolidBrush( Color.Blue );

                        g.DrawString( text, drawFont, drawBrush, new PointF( 0, 5 ) );

                        drawFont.Dispose( );
                        drawBrush.Dispose( );

                        g.Dispose( );
                    }
                    gestureShowTime--;
                }

                // image dimension
				width = lastFrame.Width;
				height = lastFrame.Height;
            }
			catch ( Exception )
			{
			}
			finally
			{
				// unlock
				Monitor.Exit( this );
			}

			// notify client
			if ( NewFrame != null )
				NewFrame( this, new EventArgs( ) );
		}

        // On video source error
        private void video_VideoSourceError( object sender, VideoSourceErrorEventArgs e )
        {
            // save video source error's description
            lastVideoSourceError = e.Description;

            // notify clients about the error
            if ( VideoSourceError != null )
            {
                VideoSourceError( this, new EventArgs( ) );
            }
        }

        // On gesture recognized
        private void recognizer_GestureDetected( object sender, Gesture gesture )
        {
            this.gesture = gesture;
            gestureShowTime = 15;
        }
	}
}
