// Hands Gesture Recognition Application
//
// Copyright © Andrew Kirillov, 2008
// andrew.kirillov@gmail.com
//

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;

using AForge.Video;
using AForge.Video.DirectShow;

namespace GesturesRecognition
{
    public partial class MainForm : Form
    {
        // statistics length
        private const int statLength = 15;
        // current statistics index
        private int statIndex = 0;
        // ready statistics values
        private int statReady = 0;
        // statistics array
        private int[] statCount = new int[statLength];

        // Constructor
        public MainForm( )
        {
            InitializeComponent( );

            cameraWindow.AutoSizeControl = true;
        }

        // Application's main form is closing
        private void MainForm_FormClosing( object sender, FormClosingEventArgs e )
        {
            CloseVideoSource( );
        }

        // "Exit" menu item clicked
        private void exitToolStripMenuItem_Click( object sender, EventArgs e )
        {
            this.Close( );
        }

        // "About" menu item clicked
        private void aboutToolStripMenuItem_Click( object sender, EventArgs e )
        {
            AboutForm form = new AboutForm( );

            form.ShowDialog( );
        }

        // Open video file
        private void openvideoToolStripMenuItem_Click( object sender, EventArgs e )
        {
            if ( openFileDialog.ShowDialog( ) == DialogResult.OK )
            {
                // create video source
                FileVideoSource fileSource = new FileVideoSource( openFileDialog.FileName );

                // open it
                OpenVideoSource( fileSource );
            }
        }

        // Open local video camera
        private void openLocalcameraToolStripMenuItem_Click( object sender, EventArgs e )
        {
            VideoCaptureDeviceForm form = new VideoCaptureDeviceForm( );

            if ( form.ShowDialog( this ) == DialogResult.OK )
            {
                // create video source
                VideoCaptureDevice videoSource = new VideoCaptureDevice( form.VideoDevice );

                // open it
                OpenVideoSource( videoSource );
            }
        }

        // Open video source
        private void OpenVideoSource( IVideoSource source )
        {
            // set busy cursor
            this.Cursor = Cursors.WaitCursor;

            // close previous video source
            CloseVideoSource( );

            // create camera
            Camera camera = new Camera( source );
            // start camera
            camera.Start( );

            // attach camera to camera window
            cameraWindow.Camera = camera;

            // reset statistics
            statIndex = statReady = 0;

            // start timer
            timer.Start( );

            this.Cursor = Cursors.Default;
        }

        // Close current video source
        private void CloseVideoSource( )
        {
            Camera camera = cameraWindow.Camera;

            if ( camera != null )
            {
                // stop timer
                timer.Stop( );

                // detach camera from camera window
                cameraWindow.Camera = null;
                Application.DoEvents( );

                // signal camera to stop
                camera.SignalToStop( );
                // wait 2 seconds until camera stops
                for ( int i = 0; ( i < 20 ) && ( camera.IsRunning ); i++ )
                {
                    Thread.Sleep( 100 );
                }
                if ( camera.IsRunning )
                {
                    camera.Stop( );
                }
                camera = null;
           }
        }

        // On timer event - gather statistics
        private void timer_Tick( object sender, EventArgs e )
        {
            Camera camera = cameraWindow.Camera;

            if ( camera != null )
            {
                // get number of frames for the last second
                statCount[statIndex] = camera.FramesReceived;

                // increment indexes
                if ( ++statIndex >= statLength )
                    statIndex = 0;
                if ( statReady < statLength )
                    statReady++;

                float fps = 0;

                // calculate average value
                for ( int i = 0; i < statReady; i++ )
                {
                    fps += statCount[i];
                }
                fps /= statReady;

                statCount[statIndex] = 0;

                fpsLabel.Text = fps.ToString( "F2" ) + " fps";
            }
        }

        // Main window was resized
        private void MainForm_SizeChanged( object sender, EventArgs e )
        {
            cameraWindow.UpdatePosition( );
        }
    }
}