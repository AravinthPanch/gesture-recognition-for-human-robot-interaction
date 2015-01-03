/**
* @author Aldebaran Robotics
* Copyright (c) Aldebaran Robotics 2012 All Rights Reserved
*/

#pragma once

#ifndef _LIB_ALVALUEUTILS_H_
#define _LIB_ALVALUEUTILS_H_

#include <alvalue/alvalue.h>
#include <string>
#include <map>

#include <boost/function.hpp>

#include <almath/types/alaxismask.h>
#include <almath/types/alposition3d.h>
#include <almath/types/alposition6d.h>
#include <almath/types/alvelocity6d.h>
#include <almath/types/altransform.h>
#include <almath/types/alpose2d.h>

#include <almathinternal/interpolations/alinterpolationtypes.h>
#include <almathinternal/types/alframe.h>
#include <almathinternal/types/alpose2dandtime.h>
#include <almathinternal/trajectories/alpath2d.h>
#include <almathinternal/trajectories/altrajectorypose2d.h>
#include <almathinternal/trajectories/alpath2dfactory.h>
#include <almathinternal/trajectories/altrajectorypose2dfactory.h>
#include <almathinternal/navigation/alnavigationtypes.h>
#include <almathinternal/navigation/region2d.h>

#include <alagilityutils/types.hpp>

namespace AL
{
  namespace ValueUtils
  {
    /// <summary>
    /// Function check if:
    /// ALValue is valid.
    /// ALValue is an array.
    /// Size of the array is not null.
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    void checkArrayFromALValue(
        const ALValue&     pVal,
        const std::string& pSource);

    /// <summary>
    /// Function check if data is not duplicated inside the given vector.
    /// </summary>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The vector checked. </param>
    /// <param name="pSize"> The range of value tested. </param>
    void checkForDuplicates(
        const std::string&                 pSource,
        const std::vector<unsigned short>& pResult,
        const unsigned short&              pSize);

    /// <summary>
    /// Function to clip a float in place and print a warning if it was
    /// out of bounds.
    /// </summary>
    /// <param name="pMin"> Minimum  allowed value. </param>
    /// <param name="pMax"> Maximum allowed value. </param>
    /// <param name="pData"> The data, to be clipped in place. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pArgName"> Name of the ALValue parameter </param>
    /// <returns> Clipped value. </returns>
    void clipAndWarn(
        float pMin,
        float pMax,
        float& pData,
        const std::string& pSource,
        const std::string& pArgName);

    /// <summary>
    /// Function to extract a float from an ALValue int or float and
    /// clip it.
    /// Throw an ALError if the value is invalid. Log a warning if the value
    /// needs clipping.
    /// </summary>
    /// <param name="pVal"> The value. </param>
    /// <param name="pMin"> Minimum  allowed value. </param>
    /// <param name="pMax"> Maximum allowed value. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pArgName"> Name of the ALValue parameter </param>
    /// <returns> Extracted and clipped value. </returns>
    float extractFloatAndClip(
        const ALValue& pVal,
        const float& pMin,
        const float& pMax,
        const std::string& pSource,
        const std::string& pArgName=std::string("ALValue"));

    /// <summary>
    /// Function to extract a float from an ALValue int or float.
    /// Throw an std::runtime_error if the value is invalid.
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pArgName"> Name of the ALValue parameter. </param>
    /// <returns> The result float. </returns>
    float extractFloat(
        const AL::ALValue& pVal,
        const std::string& pSource,
        const std::string& pArgName=std::string("ALValue"));

    /// <summary>
    /// Function to extract an int from an ALValue int or float.
    /// Throw an std::runtime_error if the value is invalid.
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pArgName"> Name of the ALValue parameter. </param>
    /// <returns> The result int. </returns>
    int extractIntFromALValue(
        const AL::ALValue& pVal,
        const std::string& pSource,
        const std::string& pArgName=std::string("ALValue"));

    /// <summary>
    /// Function to extract an std::map<std::string, ALValue> from an ALValue.
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pFromXML">
    /// If true, decode [[string, description, value, type], ...]
    /// If false, decode [[string, value], ...]
    /// </param>
    /// <param name="pResult"> The return key value map.</param>
    void extractKeyValueMapFromALValue(
        const ALValue&                  pVal,
        const std::string&              pSource,
        bool                            pFromXML,
        std::map<std::string, ALValue>& pResult);

    /// <summary>
    /// Function to extract an AxisMask from an ALValue.
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return AL::Math::AXIS_MASK.</param>
    void extractAxisMaskFromALValue(
        const AL::ALValue&   pVal,
        const std::string&   pSource,
        AL::Math::AXIS_MASK& pResult);

    /// <summary>
    /// Function to extract a Frame from an ALValue.
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return AL::Math::FRAME.</param>
    void extractFrameFromALValue(
        const AL::ALValue& pVal,
        const std::string& pSource,
        AL::Math::FRAME&   pResult);

    /// <summary>
    /// Function to extract a vector of AxisMask from an ALValue.
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return vector of AL::Math::AXIS_MASK.</param>
    void extractVectorAxisMaskFromALValue(
        const AL::ALValue&                pVal,
        const std::string&                pSource,
        std::vector<AL::Math::AXIS_MASK>& pResult);

    /// <summary>
    /// Function to extract Pose2DAndTime from an ALValue.
    /// </summary>
    /// <param name="pVal"> The ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return AL::Math::Pose2DAndTime. </param>
    void extractPose2DAndTimeFromALValue(
        const ALValue&           pVal,
        const std::string&       pSource,
        AL::Math::Pose2DAndTime& pResult);


    /// <summary>
    /// Function to extract a AL::Math::Position3D from an ALValue.
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return AL::Math::Position3D.</param>
    void extractPosition3DFromALValue(
        const AL::ALValue&    pVal,
        const std::string&    pSource,
        AL::Math::Position3D& pResult);


    /// <summary>
    /// Function to extract a AL::Math::Position6D from an ALValue.
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return AL::Math::Position6D.</param>
    void extractPosition6DFromALValue(
        const AL::ALValue&    pVal,
        const std::string&    pSource,
        AL::Math::Position6D& pResult);


    /// <summary>
    /// Function to extract a transform from an ALValue.
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return AL::Math::Transform.</param>
    void extractTransformFromALValue(
        const AL::ALValue&   pVal,
        const std::string&   pSource,
        AL::Math::Transform& pResult);

    /// <summary>
    /// Function to extract vector position 3 d from an ALValue.
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return vector of AL::Math::Position3D.</param>
    void extractVectorPosition3DFromALValue(
        const AL::ALValue&                 pVal,
        const std::string&                 pSource,
        std::vector<AL::Math::Position3D>& pResult);

    /// <summary>
    /// Function to extract vector position6D from an ALValue.
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return vector of AL::Math::Position6D.</param>
    void extractVectorPosition6DFromALValue(
        const AL::ALValue&                 pVal,
        const std::string&                 pSource,
        std::vector<AL::Math::Position6D>& pResult);

    /// <summary>
    /// Function to extract vector vector position6D from an ALValue.
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pState">
    /// pos = [x, y, z, wx, wy, wz]
    /// if pState =  true
    ///   pVal = [pos0, ...]   then pResult = [[pos0, ...]]
    ///   pVal = [[pos0, ...]] then pResult = [[pos0, ...]]
    /// if pState = false
    ///   pVal = [pos0, ...]   then pResult = [[pos0],  ...]
    ///   pVal = [[pos0, ...]] then pResult = [[pos0], ...]
    /// </param>
    /// <param name="pResult"> The return vector vector of AL::Math::Position6D.</param>
    void extractVectorPosition6DFromALValue(
        const AL::ALValue& pVal,
        const std::string& pSource,
        const bool&        pState,
        std::vector<std::vector<AL::Math::Position6D> >& pResult);

    /// <summary>
    /// Function to extract vector of AL::Math::Transform from an ALValue.
    /// </summary>
    /// <param name="pVal"> The ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return vector of AL::Math::Transform.</param>
    void extractVectorTransformFromALValue(
        const AL::ALValue&                pVal,
        const std::string&                pSource,
        std::vector<AL::Math::Transform>& pResult);

    /// <summary>
    /// Function to extract vector vector of AL::Math::Transform from an ALValue.
    /// </summary>
    /// <param name="pVal"> The ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pState">
    /// tf0 = [r1_c1, ...]
    /// if pState =  true
    ///   pVal = [tf0, ...]   then pResult = [[tf0, ...]]
    ///   pVal = [[tf0, ...]] then pResult = [[tf0, ...]]
    /// if pState = false
    ///   pVal = [tf0, ...]   then pResult = [[tf0],  ...]
    ///   pVal = [[tf0, ...]] then pResult = [[tf0], ...]
    /// </param>
    /// <param name="pResult"> The return vector vector of AL::Math::Transform.</param>
    void extractVectorTransformFromALValue(
        const AL::ALValue& pVal,
        const std::string& pSource,
        const bool&        pState,
        std::vector<std::vector<AL::Math::Transform> >& pResult);

    /// <summary>
    /// Function to extract position 6d from vector.
    /// </summary>
    /// <param name="pVal"> A vector of float. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return AL::Math::Position6D.</param>
    void extractPosition6DFromVector(
        const std::vector<float>& pVal,
        const std::string&        pSource,
        AL::Math::Position6D&     pResult);


    /// <summary>
    /// Function to extract vector of floats from an ALValue.
    /// </summary>
    /// <param name="pVal"> The ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return vector of float.</param>
    void extractVectorFloatsFromALValue(
        const AL::ALValue&  pVal,
        const std::string&  pSource,
        std::vector<float>& pResult);

    /// <summary>
    /// Function to extract vector vector of floats from an ALValue.
    /// if pVal = [[a0, ...], [b0, ...], ...] then pResult = [[a0, ...], [b0, ...], ...]
    /// </summary>
    /// <param name="pVal"> The ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pState">
    /// if pState =  true
    ///   pVal = [a0, ...]   then pResult = [[a0, ...]]
    ///   pVal = [[a0, ...]] then pResult = [[a0, ...]]
    /// if pState = false
    ///   pVal = [a0, ...]   then pResult = [[a0],  ...]
    ///   pVal = [[a0, ...]] then pResult = [[a0], ...]
    /// </param>
    /// <param name="pResult"> The return vector vector of float.</param>
    void extractVectorFloatsFromALValue(
        const ALValue&                    pVal,
        const std::string&                pSource,
        const bool&                       pState,
        std::vector<std::vector<float> >& pResult);

    /// <summary>
    /// Function to extract vector of Pose2D from an ALValue.
    /// </summary>
    /// <param name="pVal"> The ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return vector of AL::Math::Pose2D. </param>
    void extractVectorPose2DFromALValue(
        const ALValue&     pVal,
        const std::string& pSource,
        std::vector<AL::Math::Pose2D>& pResult);

    /// <summary>
    /// Function to extract vector of Position2D from an ALValue.
    /// </summary>
    /// <param name="pVal"> The ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return vector of AL::Math::Position2D. </param>
    void extractVectorPosition2DFromALValue(
        const ALValue&                     pVal,
        const std::string&                 pSource,
        std::vector<AL::Math::Position2D>& pResult);


    /// <summary>
    /// Function to extract an ALValue from a vector of Position2D.
    /// </summary>
    /// <param name="pPosition2DVect">
    /// The input vector of AL::Math::Position2D. </param>
    /// <param name="pResult"> The ALValue result. </param>
    void extractALValueFromVectorPosition2D(
        const std::vector<AL::Math::Position2D>& pPosition2DVect,
        ALValue &pResult);

    /// <summary>
    /// Function to extract an ALValue from a Pose2D.
    /// </summary>
    /// <param name="pPose2D">
    /// The input AL::Math::Pose2D. </param>
    /// <param name="pResult"> The ALValue result. </param>
    void extractALValueFromPose2D(
        const AL::Math::Pose2D& pPose2D,
        ALValue& pResult);

    /// <summary>
    /// Function to extract an ALValue from a Pose2DPosVelAcc.
    /// </summary>
    /// <param name="pPose2DPosVelAcc">
    /// The input AL::Math::Pose2DPosVelAcc. </param>
    /// <param name="pResult"> The ALValue result. </param>
    void extractALValueFromPose2DPosVelAcc(
        const AL::Math::Pose2DPosVelAcc& pPose2DPosVelAcc,
        ALValue& pResult);

    /// <summary>
    /// Function to extract an ALValue from a vector of Pose2DPosVelAcc.
    /// </summary>
    /// <param name="pPose2DPosVelAccVect">
    /// The input vector of AL::Math::Pose2DPosVelAcc. </param>
    /// <param name="pResult"> The ALValue result. </param>
    void extractALValueFromVectorPose2DPosVelAcc(
        const std::vector<AL::Math::Pose2DPosVelAcc>& pPose2DPosVelAccVect,
        ALValue &pResult);


    /// <summary>
    /// Function to extract Position2D from an ALValue.
    /// </summary>
    /// <param name="pVal"> The ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return AL::Math::Position2D. </param>
    void extractPosition2DFromALValue(
        const ALValue&        pVal,
        const std::string&    pSource,
        AL::Math::Position2D& pResult);

    /// <summary>
    /// Function to extract ALValue from a Position2D.
    /// </summary>
    /// <param name="pPos"> The input AL::Math::Position2D. </param>
    /// <param name="pVal"> The ALValue result. </param>
    void extractALValueFromPosition2D(
        const AL::Math::Position2D& pPosition2D,
        ALValue &pResult);

    /// <summary>
    /// Function to extract Pose2D from an ALValue.
    /// </summary>
    /// <param name="pVal"> The ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return AL::Math::Pose2D. </param>
    void extractPose2DFromALValue(
        const ALValue&     pVal,
        const std::string& pSource,
        AL::Math::Pose2D&  pResult);

    /// <summary>
    /// Function to extract vector of Pose2DAndTime from an ALValue.
    /// </summary>
    /// <param name="pVal"> The ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return vector of AL::Math::Pose2DAndTime. </param>
    void extractVectorPose2DAndTimeFromALValue(
        const ALValue&     pVal,
        const std::string& pSource,
        std::vector<AL::Math::Pose2DAndTime>& pResult);

    /// <summary>
    /// Function to extract an AL::Math::FRAME from an ALValue.
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return vector of AL::Math::FRAME.</param>
    void extractVectorFrameFromALValue(
        const AL::ALValue&            pVal,
        const std::string&            pSource,
        std::vector<AL::Math::FRAME>& pResult);


    /// <summary>
    /// Function to extract Interpolation Key from an ALValue.
    /// </summary>
    /// <param name="pVal">   The ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return Key.</param>
    void extractKeyFromALValue(
        const AL::ALValue& pVal,
        const std::string& pSource,
        AL::Math::Interpolation::Key& pResult);

    /// <summary>
    /// Function to extract Generic Control Point from an ALValue.
    /// </summary>
    /// <param name="pTimes"> A vector of Times. </param>
    /// <param name="pVal"> The ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pThreadCycleSeconds"> The period in second. </param>
    /// <param name="pResult"> The return Generic Control Point.</param>
    /// <returns> Return true if the first frame is a wrong. </returns>
    bool extractVectorOfGenericControlPoints(
        const std::vector<float>& pTimes,
        const ALValue&            pVal,
        const std::string&        pSource,
        const float&              pThreadCycleSeconds,
        AL::Math::Interpolation::TALJointCommandVector& pResult);


    /// <summary>
    /// Function to extract a Touch Map from an ALValue.
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return map string bool.</param>
    void extractTouchFromALValue(
        const AL::ALValue& pVal,
        const std::string& pSource,
        std::map<std::string, bool>& pResult);

    /// <summary>
    /// Function to extract a Touch Map from an ALValue.
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return map string <bool, int>.</param>
    void extractTouchFromALValue(
        const AL::ALValue& pVal,
        const std::string& pSource,
        std::map<std::string, std::pair<bool, int> >& pResult);

    /// <summary>
    /// Function to create an ALValue from a vector of vector float.
    /// </summary>
    /// <param name="pVal"> A vector of vector float. </param>
    /// <param name="pResult"> The return ALValue.</param>
    void createALValueFromVectorVectorFloat(
        const std::vector<std::vector<float> >& pVal,
        AL::ALValue& pResult);

    /// <summary>
    /// Function to create an ALValue from a vector of Position3D.
    /// </summary>
    /// <param name="pVal"> A vector of AL::Math::Position3D ALValue. </param>
    /// <param name="pResult"> The return ALValue.</param>
    void createALValueFromVectorPosition3D(
        const std::vector<AL::Math::Position3D>& pVal,
        AL::ALValue& pResult);

    /// <summary>
    /// Function to extract Navigation data from an ALValue.
    /// [[string, string, [[float, float]]], ...]
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult"> The return vector of AL::Math::Position2D. </param>
    void extractNavigationFromALValue(
        const ALValue&                     pVal,
        const std::string&                 pSource,
        std::vector<AL::Math::Position2D>& pResult);

    /// <summary>
    /// Function to extract a DirectPath2D builder from an ALValue.
    /// [string (path type), path description]
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult">
    /// The result path builder
    /// </param>
    void extractDirectPath2DBuilderFromALValue(
        const ALValue& pVal,
        const std::string& pSource,
        boost::function<Math::Trajectory::ALDirectPath2D*
          (const Math::Pose2D&)>& pResult);

    /// <summary>
    /// Function to extract a Path2D builder from an ALValue.
    /// [string (path type), path description]
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult">
    /// The result path builder
    /// </param>
    void extractPath2DBuilderFromALValue(
        const ALValue& pVal,
        const std::string& pSource,
        boost::function<Math::Trajectory::ALPath2D*
          (const Math::Pose2D&)>& pResult);

    /// <summary>
    /// Function to extract a DirectPath2D from an ALValue into a trajectory factory.
    /// [string (path type), path description]
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pFactory">
    /// The trajectory factory into which to extract the path.
    /// </param>
    void extractDirectPath2DIntoTrajectoryFactory(
        const ALValue& pVal,
        const std::string& pSource,
        Math::Trajectory::TrajectoryFactory& pFactory);

    /// <summary>
    /// Function to extract a Path2D from an ALValue into a trajectory factory.
    /// [string (path type), path description]
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pFactory">
    /// The trajectory factory into which to extract the path.
    /// </param>
    void extractPath2DIntoTrajectoryFactory(
        const ALValue& pVal,
        const std::string& pSource,
        Math::Trajectory::TrajectoryFactory& pFactory);

    /// <summary>
    /// Function to extract a DirectTrajectoryPose2D builder from an ALValue
    /// [string (direct trajectory type), trajectory description]
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pPeriod">
    /// Time period (in s)
    /// <param name="pLimitsXY">
    /// Linear limits
    /// </param>
    /// <param name="pLimitsTheta">
    /// Angular limits
    /// </param>
    /// <param name="pScaleFactor">
    /// Scale factor to apply to the trajectory
    /// </param>
    /// <param name="pResult">
    /// A function that builds a direct Trajectory Pose2D from an initial Pose2DPosVelAcc.
    /// </param>
    void extractDirectTrajectoryPose2DBuilderFromALValue(
        const ALValue& pVal,
        const std::string& pSource,
        float pPeriod,
        const Math::Limits& pLimitsXY,
        const Math::Limits& pLimitsTheta,
        float pScaleFactor,
        boost::function<Math::Trajectory::ALDirectTrajectoryPose2D*
        (const Math::Pose2DPosVelAcc&)>& pResult);

    /// <summary>
    /// Function to extract a ComposedTrajectoryPose2D builder from an ALValue
    /// [string (direct trajectory type), trajectory description]
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pPeriod">
    /// Time period (in s)
    /// <param name="pLimitsXY">
    /// Linear limits
    /// </param>
    /// <param name="pLimitsTheta">
    /// Angular limits
    /// </param>
    /// <param name="pScaleFactor">
    /// Scale factor to apply to the trajectory
    /// </param>
    /// <param name="pResult">
    /// A function that builds a composed Trajectory Pose2D from an initial Pose2DPosVelAcc.
    /// </param>
    void extractTrajectoryPose2DComposedBuilderFromALValue(
        const ALValue& pVal,
        const std::string& pSource,
        float pPeriod,
        const Math::Limits& pLimitsXY,
        const Math::Limits& pLimitsTheta,
        float pScaleFactor,
        boost::function<Math::Trajectory::ALTrajectoryPose2DComposed*
        (const Math::Pose2DPosVelAcc&)>& pResult);

    /// <summary>
    /// Function to extract any TrajectoryPose2D builder from an ALValue, either a direct trajectory
    /// or a composed trajectory.
    /// [string (trajectory type), trajectory description]
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pPeriod">
    /// Time period (in s)
    /// <param name="pLimitsXY">
    /// Linear limits
    /// </param>
    /// <param name="pLimitsTheta">
    /// Angular limits
    /// </param>
    /// <param name="pScaleFactor">
    /// Scale factor to apply to the trajectory
    /// </param>
    /// <param name="pResult">
    /// A function that builds a generic Trajectory Pose2D from an initial Pose2DPosVelAcc.
    /// </param>
    void extractTrajectoryPose2DBuilderFromALValue(
        const ALValue& pVal,
        const std::string& pSource,
        float pPeriod,
        const Math::Limits& pLimitsXY,
        const Math::Limits& pLimitsTheta,
        float pScaleFactor,
        boost::function<Math::Trajectory::ALTrajectoryPose2D*
        (const Math::Pose2DPosVelAcc&)>& pResult);

    /// <summary>
    /// Function to extract an ALValue from CircularRegion.
    /// [string (region type), float radius]
    /// </summary>
    /// <param name="pCircularRegion"> The Circular Region. </param>
    /// <param name="pOutPut"> An ALValue with output data. </param>
    void extractALValueFromCircularRegion(
        const AL::Math::CircularRegion  &pCircularRegion,
        ALValue                         &pOutPut);

    /// <summary>
    /// Function to extract an ALValue from SquareRegion.
    /// [
    ///  string (region type),
    ///  float (region direction x),
    ///  float (region direction y),
    ///  float (left width),
    ///  float (right width)
    /// ]
    /// </summary>
    /// <param name="pCircularRegion"> The SquareRegion Region. </param>
    /// <param name="pOutPut"> An ALValue with output data. </param>
    void extractALValueFromSquareRegion(
        const AL::Math::SquareRegion  &pSquareRegion,
        ALValue                       &pOutPut);

    /// <summary>
    /// Function to extract an ALValue from ConvexHullRegion.
    /// [
    ///  string (region type),
    ///  [Position2D...]
    /// ]
    /// </summary>
    /// <param name="ConvexHullRegion"> The ConvexHullRegion Region. </param>
    /// <param name="pOutPut"> An ALValue with output data. </param>
    void extractALValueFromConvexHullRegion(
        const AL::Math::ConvexHullRegion  &pConvexHullRegion,
        ALValue                           &pOutPut);

    /// <summary>
    /// Function to extract any MetricalData builder from an ALValue
    /// </summary>
    /// <param name="pVal"> An ALValue. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pResult">
    /// Resulting MetricalData.
    /// </param>
    void extractMetricalDataFromALValue(
        const ALValue& pVal,
        const std::string& pSource,
        Math::MetricalData& pResult);

    /// <summary>
    /// Function to extract an ALValue builder from a MetricalData.
    /// </summary>
    /// <param name="pVal"> A source MetricalData. </param>
    /// <param name="pResult">
    /// Resulting ALValue.
    /// </param>
    void extractALValueFromMetricalData(const Math::MetricalData& pVal,
                                        ALValue& pResult);

    /// <summary>
    /// Function to extract an ALValue from a Region2D.
    /// </summary>
    /// <param name="pRegion"> A Region2D to serialize. </param>
    /// <param name="pOutput">
    /// Resulting ALValue.
    /// </param>
    void extractALValueFromRegion2D(Math::Region2D &pRegion, ALValue &pOutput);

    /// <summary>
    /// Function to convert a Temperature status to an ALValue.
    /// </summary>
    /// <param name="pStatus"> A TemepratureStatus to serialize. </param>
    /// <param name="pOutput">
    /// Resulting ALValue.
    /// </param>
    void convertTemperatureStatusToALValue(
        const TemperatureStatus  &pStatus,
        ALValue                  &pOutput);

    /// <summary>
    /// Function to extract an ALValue from a Temperature status.
    /// </summary>
    /// <param name="pValue"> A ALValue to deserialize. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    /// <param name="pStatus">
    /// Resulting TemperatureStatus.
    /// </param>
    void extractTemperatureStatusFromALValue(
        const ALValue     &pValue,
        TemperatureStatus &pStatus,
        const std::string &pSource);

    /// <summary>
    /// Function to extract diagnosis data from an ALValue.
    /// </summary>
    /// <param name="pValue"> An ALValue to deserialize. </param>
    /// <param name="pFailureSeverity"> Failure severity. </param>
    /// <param name="pDevices"> The list of devices in errors. </param>
    /// <param name="pSource">
    /// The name of the method to be used when throwing errors.
    /// </param>
    void extractDiagnosisFromALValue(
        const ALValue         &pValue,
        int                   &pFailureSeverity,
        std::set<std::string> &pDevices,
        const std::string     &pSource);

    /// <summary>
    /// Function to extract config data from an ALValue.
    /// </summary>
    /// <param name="pValue">The config value. </param>
    /// <param name="pName">The config name. </param>
    /// <param name="pConfigArray"> The list of output configs. </param>
    void decodeMotionConfig(const ALValue  &pValue,
                            const ALValue  &pName,
                            ALValue        &pConfigArray);
  }
}
#endif  // _LIB_ALVALUEUTILS_H_
