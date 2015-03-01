// Gesture Recognition Module
//
// Copyright © Andrew Kirillov, 2008
// andrew.kirillov@gmail.com
//

namespace AForge.GestureRecognition
{
    using System;

    /// <summary>
    /// Set of recognizable hand positions.
    /// </summary>
    /// 
    public enum HandPosition
    {
        /// <summary>
        /// Hand is not raized.
        /// </summary>
        NotRaised,

        /// <summary>
        /// Hand is raised straight.
        /// </summary>
        RaisedStraigh,

        /// <summary>
        /// Hand is raised diagonally up.
        /// </summary>
        RaisedDiagonallyUp,

        /// <summary>
        /// Hand is raised diagonally down.
        /// </summary>
        RaisedDiagonallyDown
    }

    /// <summary>
    /// Two hands gesture.
    /// </summary>
    /// 
    public struct Gesture
    {
        /// <summary>
        /// Position of left hand.
        /// </summary>
        public HandPosition LeftHand;

        /// <summary>
        /// Position of right hand.
        /// </summary>
        public HandPosition RightHand;

        /// <summary>
        /// Initializes a new instance of the <see cref="Gesture"/> structure.
        /// </summary>
        /// 
        /// <param name="leftHand">Left hand's position.</param>
        /// <param name="rightHand">Right hand's position.</param>
        /// 
        public Gesture( HandPosition leftHand, HandPosition rightHand )
        {
            LeftHand  = leftHand;
            RightHand = rightHand;
        }
    }
}