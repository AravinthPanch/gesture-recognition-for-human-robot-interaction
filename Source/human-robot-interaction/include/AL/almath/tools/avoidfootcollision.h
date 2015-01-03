/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#pragma once
#ifndef _LIBALMATH_ALMATH_TOOLS_AVOIDFOOTCOLLISION_H_
#define _LIBALMATH_ALMATH_TOOLS_AVOIDFOOTCOLLISION_H_

#include <almath/types/alpose2d.h>
#include <vector>

namespace AL
{
  namespace Math
  {
    /// <summary>
    /// Compute the best position(orientation) of the foot to avoid collision.
    /// </summary>
    /// <param name="pLFootBoundingBox">  vector<Pose2D> of the left footBoundingBox.</param>
    /// <param name="pRFootBoundingBox">  vector<Pose2D> of the right footBoundingBox.</param>
    /// <param name="pIsLeftSupport">     Bool true if left is the support leg. </param>
    /// <param name="pMove">              the desired and return Pose2D. </param>
    /// <returns>
    /// true if pMove is clamped.
    /// </returns>
    /// \ingroup Tools
    const bool avoidFootCollision(
        const std::vector<Pose2D>&  pLFootBoundingBox,
        const std::vector<Pose2D>&  pRFootBoundingBox,
        const bool&                 pIsLeftSupport,
        Pose2D&                     pMove);


    /// <summary>
    /// Clip foot move with ellipsoid function
    /// </summary>
    /// <param name="pMaxFootX">  float of the max step along x axis. </param>
    /// <param name="pMaxFootY">  float of the max step along y axis. </param>
    /// <param name="pMove">      the desired and return Pose2D. </param>
    /// <returns>
    /// true if pMove is clamped.
    /// </returns>
    /// \ingroup Tools
    const bool clipFootWithEllipse(
        const float&    pMaxFootX,
        const float&    pMaxFootY,
        Pose2D&         pMove);

  } // namespace Math
} // namespace AL

#endif  // _LIBALMATH_ALMATH_TOOLS_AVOIDFOOTCOLLISION_H_

