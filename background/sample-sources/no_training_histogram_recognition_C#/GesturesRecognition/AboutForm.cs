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

namespace GesturesRecognition
{
    public partial class AboutForm : Form
    {
        public AboutForm( )
        {
            InitializeComponent( );

            // initialize links
            emailLabel.Links.Add( 0, emailLabel.Text.Length, "mailto:andrew.kirillov@gmail.com" );
            aforgeLabel.Links.Add( 0, aforgeLabel.Text.Length, "http://code.google.com/p/aforge/" );
        }

        // Link clicked
        private void LinkClicked( object sender, LinkLabelLinkClickedEventArgs e )
        {
            System.Diagnostics.Process.Start( e.Link.LinkData.ToString( ) );
        }
    }
}