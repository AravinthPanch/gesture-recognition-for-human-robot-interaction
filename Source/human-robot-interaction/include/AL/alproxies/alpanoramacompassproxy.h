// Generated for ALPanoramaCompass version 0

#ifndef ALPANORAMACOMPASSPROXY_H_
#define ALPANORAMACOMPASSPROXY_H_

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
  class ALPanoramaCompassProxy;

  namespace detail {
    class ALPanoramaCompassProxyPostHandler
    {
    protected:
      ALPanoramaCompassProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALPanoramaCompassProxy;

      /// <summary>
      /// Delete all panorama files in the current working directory
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int clearAllPanoramas();

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Changes the pause status of the extractor
      /// </summary>
      /// <param name="paused"> New pause satus </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int pause(const bool& paused);

      /// <summary>
      /// DEPRECATED: Sets pause and resolution
      /// </summary>
      /// <param name="paramName"> Name of the parameter to set </param>
      /// <param name="value"> New value </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setParameter(const std::string& paramName, const AL::ALValue& value);

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Make the robot stop every current operation
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopTasks();

      /// <summary>
      /// Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData("keyName"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
      /// </summary>
      /// <param name="name"> Name of the module which subscribes. </param>
      /// <param name="period"> Refresh period (in milliseconds) if relevant. </param>
      /// <param name="precision"> Precision of the extractor if relevant. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int subscribe(const std::string& name, const int& period, const float& precision);

      /// <summary>
      /// Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData("keyName"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
      /// </summary>
      /// <param name="name"> Name of the module which subscribes. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int subscribe(const std::string& name);

      /// <summary>
      /// Unsubscribes from the extractor.
      /// </summary>
      /// <param name="name"> Name of the module which had subscribed. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int unsubscribe(const std::string& name);

      /// <summary>
      /// Updates the period if relevant.
      /// </summary>
      /// <param name="name"> Name of the module which has subscribed. </param>
      /// <param name="period"> Refresh period (in milliseconds). </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int updatePeriod(const std::string& name, const int& period);

      /// <summary>
      /// Updates the precision if relevant.
      /// </summary>
      /// <param name="name"> Name of the module which has subscribed. </param>
      /// <param name="precision"> Precision of the extractor. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int updatePrecision(const std::string& name, const float& precision);

      /// <summary>
      /// Wait until all current operations are over
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int waitUntilOver();

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALPanoramaCompassProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALPanoramaCompassProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALPanoramaCompassProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALPanoramaCompassProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALPanoramaCompassProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Delete all panorama files in the current working directory
    /// </summary>
    void clearAllPanoramas();

    /// <summary>
    /// Delete all files related to a given panorama in the current working directory
    /// </summary>
    /// <param name="pIdentity"> Panorama identity </param>
    int clearPanorama(const int& pIdentity);

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// Gets extractor active camera
    /// </summary>
    /// <returns> Id of the current active camera of the extractor </returns>
    int getActiveCamera();

    /// <summary>
    /// Return base path for working directories
    /// </summary>
    std::string getBaseWorkingDirectory();

    /// <summary>
    /// Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

    /// <summary>
    /// 
    /// </summary>
    /// <returns> Return an ALValue containing Panorama identity and contained Frames identity. </returns>
    AL::ALValue getCurrentPanoramaDescriptor();

    /// <summary>
    /// Gets the current period.
    /// </summary>
    /// <returns> Refresh period (in milliseconds). </returns>
    int getCurrentPeriod();

    /// <summary>
    /// Return the current orientation of the robot in the current panorama.
    /// </summary>
    AL::ALValue getCurrentPosition();

    /// <summary>
    /// Gets the current precision.
    /// </summary>
    /// <returns> Precision of the extractor. </returns>
    float getCurrentPrecision();

    /// <summary>
    /// Get the list of events updated in ALMemory.
    /// </summary>
    /// <returns> Array of events updated by this extractor in ALMemory </returns>
    std::vector<std::string> getEventList();

    /// <summary>
    /// Return the Frame corresponding to the input identity. It have to be in the current Panorama
    /// </summary>
    /// <param name="id"> Identity of the resquested Frame. </param>
    /// <param name="arg2"> arg </param>
    /// <returns> ALValue containing the Frame image part. </returns>
    AL::ALValue getFrame(const int& id, const std::string& arg2);

    /// <summary>
    /// Gets extractor framerate
    /// </summary>
    /// <returns> Current value of the framerate of the extractor </returns>
    int getFrameRate();

    /// <summary>
    /// Return the id of the current panorama.
    /// </summary>
    int getId();

    /// <summary>
    /// Get the list of events updated in ALMemory.
    /// </summary>
    /// <returns> Array of events updated by this extractor in ALMemory </returns>
    std::vector<std::string> getMemoryKeyList();

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
    /// Gets the period for a specific subscription.
    /// </summary>
    /// <param name="name"> Name of the module which has subscribed. </param>
    /// <returns> Refresh period (in milliseconds). </returns>
    int getMyPeriod(const std::string& name);

    /// <summary>
    /// Gets the precision for a specific subscription.
    /// </summary>
    /// <param name="name"> name of the module which has subscribed </param>
    /// <returns> precision of the extractor </returns>
    float getMyPrecision(const std::string& name);

    /// <summary>
    /// Get the list of values updated in ALMemory.
    /// </summary>
    /// <returns> Array of values updated by this extractor in ALMemory </returns>
    std::vector<std::string> getOutputNames();

    /// <summary>
    /// Gets extractor resolution
    /// </summary>
    /// <returns> Current value of the resolution of the extractor </returns>
    int getResolution();

    /// <summary>
    /// Get an estimate of the location from the last known location and the odometry.
    /// </summary>
    /// <param name="pUseCompass"> If false, the odometry is always used. </param>
    /// <returns> Estimate of the location. </returns>
    std::vector<float> getRoughLocation(const bool& pUseCompass);

    /// <summary>
    /// Gets the parameters given by the module.
    /// </summary>
    /// <returns> Array of names and parameters of all subscribers. </returns>
    AL::ALValue getSubscribersInfo();

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// Go to the given angle in the current Panorama referential.
    /// </summary>
    /// <param name="angle"> Angle to reach in the current Panorama referential. </param>
    /// <returns> Error status. </returns>
    int goToPosition(const float& angle);

    /// <summary>
    /// Go to the given angle in the current Panorama referential.
    /// </summary>
    /// <param name="angle"> Angle to reach in the current Panorama referential. </param>
    /// <param name="useOdometryOnVisualEstimationFailure"> If set to true, the PanoramaCompass will refer to the odometry to find a best estimation when the pure visual estimation fail. </param>
    /// <returns> Error status. </returns>
    int goToPosition(const float& angle, const bool& useOdometryOnVisualEstimationFailure);

    /// <summary>
    /// Check if the robot is in the current Panorama.
    /// </summary>
    /// <returns> Error status. </returns>
    int isInPanorama();

    /// <summary>
    /// Check if the robot is in the current Panorama.
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <returns> Error status. </returns>
    int isInPanorama(const int& arg1);

    /// <summary>
    /// Gets extractor pause status
    /// </summary>
    /// <returns> True if the extractor is paused, False if not </returns>
    bool isPaused();

    /// <summary>
    /// Gets extractor running status
    /// </summary>
    /// <returns> True if the extractor is currently processing images, False if not </returns>
    bool isProcessing();

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// Load the panorama corresponding to the input identity from the hard drive. It has to exist.
    /// </summary>
    /// <param name="id"> Identity of the requested Panorama. </param>
    /// <returns> Error status. </returns>
    int loadPanorama(const int& id);

    /// <summary>
    /// Localize the robot using the scan.
    /// </summary>
    /// <param name="pMode"> Localization mode </param>
    std::vector<float> localize();

    /// <summary>
    /// Localize the robot using the scan.
    /// </summary>
    /// <param name="pMode"> Localization mode </param>
    std::vector<float> localize(const int& pMode);

    /// <summary>
    /// Localize the robot using the scan,without hint.
    /// </summary>
    std::vector<float> localizeNoHint();

    /// <summary>
    /// Changes the pause status of the extractor
    /// </summary>
    /// <param name="paused"> New pause satus </param>
    void pause(const bool& paused);

    /// <summary>
    /// Just a ping. Always returns true
    /// </summary>
    /// <returns> returns true </returns>
    bool ping();

    /// <summary>
    /// Sets extractor active camera
    /// </summary>
    /// <param name="cameraId"> Id of the camera that will become the active camera </param>
    /// <returns> True if the update succeeded, False if not </returns>
    bool setActiveCamera(const int& cameraId);

    /// <summary>
    /// Sets the coordinates of the current location.
    /// </summary>
    /// <param name="pos"> [x, y, theta] of the current location </param>
    int setCurrentLocation(const std::vector<float>& pos);

    /// <summary>
    /// Sets the coordinates of the current location.
    /// </summary>
    /// <param name="x"> x-coordinate </param>
    /// <param name="y"> y-coordinate </param>
    /// <param name="theta"> orientation </param>
    int setCurrentLocation(const float& x, const float& y, const float& theta);

    /// <summary>
    /// Sets the extractor framerate for a chosen subscriber
    /// </summary>
    /// <param name="subscriberName"> Name of the subcriber </param>
    /// <param name="framerate"> New framerate </param>
    /// <returns> True if the update succeeded, False if not </returns>
    bool setFrameRate(const std::string& subscriberName, const int& framerate);

    /// <summary>
    /// Sets the extractor framerate for all the subscribers
    /// </summary>
    /// <param name="framerate"> New framerate </param>
    /// <returns> True if the update succeeded, False if not </returns>
    bool setFrameRate(const int& framerate);

    /// <summary>
    /// DEPRECATED: Sets pause and resolution
    /// </summary>
    /// <param name="paramName"> Name of the parameter to set </param>
    /// <param name="value"> New value </param>
    void setParameter(const std::string& paramName, const AL::ALValue& value);

    /// <summary>
    /// Sets extractor resolution
    /// </summary>
    /// <param name="resolution"> New resolution </param>
    /// <returns> True if the update succeeded, False if not </returns>
    bool setResolution(const int& resolution);

    /// <summary>
    /// Set current working directory
    /// </summary>
    /// <param name="directory"> Directory name </param>
    bool setWorkingDirectory(const std::string& directory);

    /// <summary>
    /// Shoot a panorama at the current position.
    /// </summary>
    int setupPanorama();

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Make the robot stop every current operation
    /// </summary>
    void stopTasks();

    /// <summary>
    /// Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData("keyName"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
    /// </summary>
    /// <param name="name"> Name of the module which subscribes. </param>
    /// <param name="period"> Refresh period (in milliseconds) if relevant. </param>
    /// <param name="precision"> Precision of the extractor if relevant. </param>
    void subscribe(const std::string& name, const int& period, const float& precision);

    /// <summary>
    /// Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData("keyName"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
    /// </summary>
    /// <param name="name"> Name of the module which subscribes. </param>
    void subscribe(const std::string& name);

    /// <summary>
    /// Unsubscribes from the extractor.
    /// </summary>
    /// <param name="name"> Name of the module which had subscribed. </param>
    void unsubscribe(const std::string& name);

    /// <summary>
    /// Updates the period if relevant.
    /// </summary>
    /// <param name="name"> Name of the module which has subscribed. </param>
    /// <param name="period"> Refresh period (in milliseconds). </param>
    void updatePeriod(const std::string& name, const int& period);

    /// <summary>
    /// Updates the precision if relevant.
    /// </summary>
    /// <param name="name"> Name of the module which has subscribed. </param>
    /// <param name="precision"> Precision of the extractor. </param>
    void updatePrecision(const std::string& name, const float& precision);

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

    /// <summary>
    /// Wait until all current operations are over
    /// </summary>
    void waitUntilOver();


    detail::ALPanoramaCompassProxyPostHandler post;
  };

}
#endif // ALPANORAMACOMPASSPROXY_H_
