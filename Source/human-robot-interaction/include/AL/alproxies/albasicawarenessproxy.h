// Generated for ALBasicAwareness version 1.22

#ifndef ALBASICAWARENESSPROXY_H_
#define ALBASICAWARENESSPROXY_H_

#include <alproxies/api.h>
#include <boost/shared_ptr.hpp>
#include <alvalue/alvalue.h>
#include <qi/types.hpp>
#include <qitype/anyobject.hpp>
#include <string>
#include <vector>

namespace AL
{
  class ALBroker;
  class ALProxy;
  class ALBasicAwarenessProxy;

  namespace detail {
    class ALBasicAwarenessProxyPostHandler
    {
    protected:
      ALBasicAwarenessProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALBasicAwarenessProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Set engagement mode.
      /// </summary>
      /// <param name="modeName"> Name of the mode </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setEngagementMode(const std::string& modeName);

      /// <summary>
      /// Enable/Disable Head movements.
      /// </summary>
      /// <param name="enable"> Boolean value: true to enable, false to disable. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setHeadMotionEnabled(const bool& enable);

      /// <summary>
      /// Enable/Disable Movement Detection.
      /// </summary>
      /// <param name="isMovementDetectionEnabled"> Boolean value: true to enable, false to disable. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setMovementDetectionEnabled(const bool& isMovementDetectionEnabled);

      /// <summary>
      /// Set the specified parameter 
      /// </summary>
      /// <param name="paramName"> "ServoingSpeed" : Speed of servoing head moves
      ///  "LookStimulusSpeed" : Speed of head moves when looking at a stimulus
      ///  "LookBackSpeed" : Speed of head moves when looking back to previous position
      ///  "NobodyFoundTimeOut" : timeout to send HumanLost event when no blob isfound
      ///  "TimeSleepBeforeStimuli" : Slept time before waiting for stimuli
      ///  "TimeSleepBeforeResumeMS" : Slept time before automatically resuming BasicAwareness when an automatic pause has been made, in milliseconds
      ///  "AmplitudeYawTracking" : max absolute value for head yaw in tracking, in degrees
      ///  "HeadThreshold" : Threshold for tracking
      ///  "PeoplePerceptionPeriod" : Period for people perception, in milliseconds
      ///  "SlowPeoplePerceptionPeriod" : Period for people perception in FullyEngaged mode, in milliseconds
      ///   </param>
      /// <param name="newVal"> "ServoingSpeed" : Float in range [0.01;1]
      ///  "LookStimulusSpeed" : Float in range [0.01;1]
      ///  "LookBackSpeed" : Float in range [0.01;1]
      ///  "NobodyFoundTimeOut" : Float > 0
      ///  "TimeSleepBeforeStimuli" : Float > 0
      ///  "TimeSleepBeforeResumeMS" : Int > 0
      ///  "AmplitudeYawTracking" : Float in range [10;120]
      ///  "HeadThreshold" : Float in range [0;180]
      ///  "PeoplePerceptionPeriod" : Int > 1
      ///  "SlowPeoplePerceptionPeriod" : Int > 1
      ///   </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setParameter(const std::string& paramName, const AL::ALValue& newVal);

      /// <summary>
      /// Enable/Disable Sound Detection.
      /// </summary>
      /// <param name="isSoundDetectionEnabled"> Boolean value: true to enable, false to disable. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setSoundDetectionEnabled(const bool& isSoundDetectionEnabled);

      /// <summary>
      /// Enable/Disable Stimulus Detection.
      /// </summary>
      /// <param name="stimulusName"> Name of the stimulus to enable/disable </param>
      /// <param name="isStimulusDetectionEnabled"> Boolean value: true to enable, false to disable. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setStimulusDetectionEnabled(const std::string& stimulusName, const bool& isStimulusDetectionEnabled);

      /// <summary>
      /// Enable/Disable Touch Detection.
      /// </summary>
      /// <param name="isTouchDetectionEnabled"> Boolean value: true to enable, false to disable. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setTouchDetectionEnabled(const bool& isTouchDetectionEnabled);

      /// <summary>
      /// Set tracking mode.
      /// </summary>
      /// <param name="modeName"> Name of the mode </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setTrackingMode(const std::string& modeName);

      /// <summary>
      /// Start Basic Awareness.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int startAwareness();

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Stop Basic Awareness.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopAwareness();

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALBasicAwarenessProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALBasicAwarenessProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALBasicAwarenessProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALBasicAwarenessProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALBasicAwarenessProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

    /// <summary>
    /// Set engagement mode.
    /// </summary>
    /// <returns> Name of current engagement mode as a string </returns>
    std::string getEngagementMode();

    /// <summary>
    /// Retrieves a method's description.
    /// </summary>
    /// <param name="methodName"> The name of the method. </param>
    /// <returns> A structure containing the method's description. </returns>
    AL::ALValue getMethodHelp(const std::string& methodName);

    /// <summary>
    /// Retrieves the module's method list.
    /// </summary>
    /// <returns> An array of method names. </returns>
    std::vector<std::string> getMethodList();

    /// <summary>
    /// Retrieves the module's description.
    /// </summary>
    /// <returns> A structure describing the module. </returns>
    AL::ALValue getModuleHelp();

    /// <summary>
    /// Get the specified parameter.
    /// </summary>
    /// <param name="paramName"> "ServoingSpeed" : Speed of servoing head moves
    ///  "LookStimulusSpeed" : Speed of head moves when looking at a stimulus
    ///  "LookBackSpeed" : Speed of head moves when looking back to previous position
    ///  "NobodyFoundTimeOut" : timeout to send HumanLost event when no blob isfound
    ///  "TimeSleepBeforeStimuli" : Slept time before waiting for stimuli
    ///  "TimeSleepBeforeResumeMS" : Slept time before automatically resuming BasicAwareness when an automatic pause has been made, in milliseconds
    ///  "AmplitudeYawTracking" : max absolute value for head yaw in tracking, in degrees
    ///  "HeadThreshold" : Threshold for tracking
    ///  "PeoplePerceptionPeriod" : Period for people perception, in milliseconds
    ///  "SlowPeoplePerceptionPeriod" : Period for people perception in FullyEngaged mode, in milliseconds
    ///   </param>
    /// <returns> ALValue format for required parameter </returns>
    AL::ALValue getParameter(const std::string& paramName);

    /// <summary>
    /// Set tracking mode.
    /// </summary>
    /// <returns> Name of current tracking mode as a string </returns>
    std::string getTrackingMode();

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// Get the pause status of the module.
    /// </summary>
    bool isAwarenessPaused();

    /// <summary>
    /// Get the status (started or not) of the module.
    /// </summary>
    bool isAwarenessRunning();

    /// <summary>
    /// Get status enabled/disabled for Head Movements.
    /// </summary>
    /// <returns> Boolean value for status enabled/disabled </returns>
    bool isHeadMotionEnabled();

    /// <summary>
    /// Get status enabled/disabled for Movement Detection.
    /// </summary>
    /// <returns> Boolean value for status enabled/disabled </returns>
    bool isMovementDetectionEnabled();

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// Get status enabled/disabled for Sound Detection.
    /// </summary>
    /// <returns> Boolean value for status enabled/disabled </returns>
    bool isSoundDetectionEnabled();

    /// <summary>
    /// Get status enabled/disabled for Stimulus Detection.
    /// </summary>
    /// <param name="stimulusName"> Name of the stimulus to check </param>
    /// <returns> Boolean value for status enabled/disabled </returns>
    bool isStimulusDetectionEnabled(const std::string& stimulusName);

    /// <summary>
    /// Get status enabled/disabled for Touch Detection.
    /// </summary>
    /// <returns> Boolean value for status enabled/disabled </returns>
    bool isTouchDetectionEnabled();

    /// <summary>
    /// Pause BasicAwareness.
    /// </summary>
    bool pauseAwareness();

    /// <summary>
    /// Just a ping. Always returns true
    /// </summary>
    /// <returns> returns true </returns>
    bool ping();

    /// <summary>
    /// Resume BasicAwareness.
    /// </summary>
    bool resumeAwareness();

    /// <summary>
    /// Set engagement mode.
    /// </summary>
    /// <param name="modeName"> Name of the mode </param>
    void setEngagementMode(const std::string& modeName);

    /// <summary>
    /// Enable/Disable Head movements.
    /// </summary>
    /// <param name="enable"> Boolean value: true to enable, false to disable. </param>
    void setHeadMotionEnabled(const bool& enable);

    /// <summary>
    /// Enable/Disable Movement Detection.
    /// </summary>
    /// <param name="isMovementDetectionEnabled"> Boolean value: true to enable, false to disable. </param>
    void setMovementDetectionEnabled(const bool& isMovementDetectionEnabled);

    /// <summary>
    /// Set the specified parameter 
    /// </summary>
    /// <param name="paramName"> "ServoingSpeed" : Speed of servoing head moves
    ///  "LookStimulusSpeed" : Speed of head moves when looking at a stimulus
    ///  "LookBackSpeed" : Speed of head moves when looking back to previous position
    ///  "NobodyFoundTimeOut" : timeout to send HumanLost event when no blob isfound
    ///  "TimeSleepBeforeStimuli" : Slept time before waiting for stimuli
    ///  "TimeSleepBeforeResumeMS" : Slept time before automatically resuming BasicAwareness when an automatic pause has been made, in milliseconds
    ///  "AmplitudeYawTracking" : max absolute value for head yaw in tracking, in degrees
    ///  "HeadThreshold" : Threshold for tracking
    ///  "PeoplePerceptionPeriod" : Period for people perception, in milliseconds
    ///  "SlowPeoplePerceptionPeriod" : Period for people perception in FullyEngaged mode, in milliseconds
    ///   </param>
    /// <param name="newVal"> "ServoingSpeed" : Float in range [0.01;1]
    ///  "LookStimulusSpeed" : Float in range [0.01;1]
    ///  "LookBackSpeed" : Float in range [0.01;1]
    ///  "NobodyFoundTimeOut" : Float > 0
    ///  "TimeSleepBeforeStimuli" : Float > 0
    ///  "TimeSleepBeforeResumeMS" : Int > 0
    ///  "AmplitudeYawTracking" : Float in range [10;120]
    ///  "HeadThreshold" : Float in range [0;180]
    ///  "PeoplePerceptionPeriod" : Int > 1
    ///  "SlowPeoplePerceptionPeriod" : Int > 1
    ///   </param>
    void setParameter(const std::string& paramName, const AL::ALValue& newVal);

    /// <summary>
    /// Enable/Disable Sound Detection.
    /// </summary>
    /// <param name="isSoundDetectionEnabled"> Boolean value: true to enable, false to disable. </param>
    void setSoundDetectionEnabled(const bool& isSoundDetectionEnabled);

    /// <summary>
    /// Enable/Disable Stimulus Detection.
    /// </summary>
    /// <param name="stimulusName"> Name of the stimulus to enable/disable </param>
    /// <param name="isStimulusDetectionEnabled"> Boolean value: true to enable, false to disable. </param>
    void setStimulusDetectionEnabled(const std::string& stimulusName, const bool& isStimulusDetectionEnabled);

    /// <summary>
    /// Enable/Disable Touch Detection.
    /// </summary>
    /// <param name="isTouchDetectionEnabled"> Boolean value: true to enable, false to disable. </param>
    void setTouchDetectionEnabled(const bool& isTouchDetectionEnabled);

    /// <summary>
    /// Set tracking mode.
    /// </summary>
    /// <param name="modeName"> Name of the mode </param>
    void setTrackingMode(const std::string& modeName);

    /// <summary>
    /// Start Basic Awareness.
    /// </summary>
    void startAwareness();

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Stop Basic Awareness.
    /// </summary>
    void stopAwareness();

    /// <summary>
    /// Returns the version of the module.
    /// </summary>
    /// <returns> A string containing the version of the module. </returns>
    std::string version();

    /// <summary>
    /// Wait for the end of a long running method that was called using 'post'
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <param name="timeoutPeriod"> The timeout period in ms. To wait indefinately, use a timeoutPeriod of zero. </param>
    /// <returns> True if the timeout period terminated. False if the method returned. </returns>
    bool wait(const int& id, const int& timeoutPeriod);


    detail::ALBasicAwarenessProxyPostHandler post;
  };

}
#endif // ALBASICAWARENESSPROXY_H_
