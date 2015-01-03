// Generated for ALLocalization version 0

#ifndef ALLOCALIZATIONPROXY_H_
#define ALLOCALIZATIONPROXY_H_

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
  class ALLocalizationProxy;

  namespace detail {
    class ALLocalizationProxyPostHandler
    {
    protected:
      ALLocalizationProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALLocalizationProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Stops all tasks.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopTasks();

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALLocalizationProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALLocalizationProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALLocalizationProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALLocalizationProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALLocalizationProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Delete all panoramas in a directory.
    /// </summary>
    /// <param name="pDirectory"> Name of the directory </param>
    int clear(const std::string& pDirectory);

    /// <summary>
    /// Erases a node.
    /// </summary>
    /// <param name="pId"> Id of the node </param>
    int eraseNode(const int& pId);

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// Shoots a partial panorama and use it to find the location.
    /// </summary>
    /// <param name="pId"> Id of a node </param>
    /// <param name="pMode"> Localization mode </param>
    std::vector<float> findCurrentLocationInNode(const int& pId, const int& pMode);

    /// <summary>
    /// Shoots a partial panorama and use it to find the location.
    /// </summary>
    /// <param name="pMode"> Localization mode </param>
    std::vector<float> findCurrentLocationInWorld(const int& pMode);

    /// <summary>
    /// Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

    /// <summary>
    /// Returns closest panorama to the hinted position.
    /// </summary>
    /// <param name="pId"> Id of a node </param>
    /// <param name="pX"> x-coordinate </param>
    /// <param name="pY"> y-coordinate </param>
    AL::ALValue getClosestNodeInNode(const int& pId, const float& pX, const float& pY);

    /// <summary>
    /// Returns closest panorama to the hinted position.
    /// </summary>
    /// <param name="pX"> x-coordinate </param>
    /// <param name="pY"> y-coordinate </param>
    AL::ALValue getClosestNodeInWorld(const float& pX, const float& pY);

    /// <summary>
    /// Returns the current node.
    /// </summary>
    int getCurrentNode();

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
    /// Returns the location of a given node.
    /// </summary>
    /// <param name="pRefNode"> Id of the reference node </param>
    /// <param name="pNodeId"> Id of the node </param>
    std::vector<float> getNodeLocationInNode(const int& pRefNode, const int& pNodeId);

    /// <summary>
    /// Returns the location of a given node.
    /// </summary>
    /// <param name="pNodeId"> Id of the node </param>
    std::vector<float> getNodeLocationInWorld(const int& pNodeId);

    /// <summary>
    /// Returns the list of all node ids.
    /// </summary>
    std::vector<int> getNodes();

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// Go to a position while shooting partial panoramas to keep track of the current position.
    /// </summary>
    /// <param name="pNodeId"> Id of a node </param>
    /// <param name="pX"> x-coordinate </param>
    /// <param name="pY"> y-coordinate </param>
    /// <param name="pTheta"> theta-coordinate </param>
    /// <param name="pMode"> Localization mode </param>
    /// <param name="pPrecision"> Expected precision </param>
    int goToLocationInNode(const int& pNodeId, const float& pX, const float& pY, const float& pTheta, const int& pMode, const float& pPrecision);

    /// <summary>
    /// Go to a position while shooting partial panoramas to keep track of the current position.
    /// </summary>
    /// <param name="pX"> x-coordinate </param>
    /// <param name="pY"> y-coordinate </param>
    /// <param name="pTheta"> theta-coordinate </param>
    /// <param name="pMode"> Localization mode </param>
    /// <param name="pPrecision"> Expected precision </param>
    int goToLocationInWorld(const float& pX, const float& pY, const float& pTheta, const int& pMode, const float& pPrecision);

    /// <summary>
    /// Move to a node.
    /// </summary>
    /// <param name="pId"> Id of the node </param>
    /// <param name="pMode"> Localization mode </param>
    /// <param name="pPrecision"> Expected precision </param>
    int goToNode(const int& pId, const int& pMode, const float& pPrecision);

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// Acquires a node at the current position.
    /// </summary>
    AL::ALValue learnNode();

    /// <summary>
    /// Loads panoramas from a directory in the default one.
    /// </summary>
    /// <param name="pDirectory"> Name of the directory </param>
    int load(const std::string& pDirectory);

    /// <summary>
    /// Just a ping. Always returns true
    /// </summary>
    /// <returns> returns true </returns>
    bool ping();

    /// <summary>
    /// Reacquires a node at the current position.
    /// </summary>
    /// <param name="pId"> Id of the node </param>
    AL::ALValue relearnNode(const int& pId);

    /// <summary>
    /// Save the temporary panoramas in a directory from the default one.
    /// </summary>
    /// <param name="pDirectory"> Name of the directory </param>
    int save(const std::string& pDirectory);

    /// <summary>
    /// Sets the current location.
    /// </summary>
    /// <param name="pNodeId"> Id of a node </param>
    /// <param name="pX"> x-coordinate </param>
    /// <param name="pY"> y-coordinate </param>
    /// <param name="pTheta"> theta-coordinate </param>
    int setCurrentLocationInNode(const int& pNodeId, const float& pX, const float& pY, const float& pTheta);

    /// <summary>
    /// Sets the current location.
    /// </summary>
    /// <param name="pX"> x-coordinate </param>
    /// <param name="pY"> y-coordinate </param>
    /// <param name="pTheta"> theta-coordinate </param>
    int setCurrentLocationInWorld(const float& pX, const float& pY, const float& pTheta);

    /// <summary>
    /// Sets the current node.
    /// </summary>
    /// <param name="pId"> Id of a node </param>
    int setCurrentNode(const int& pId);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Stops all tasks.
    /// </summary>
    void stopTasks();

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


    detail::ALLocalizationProxyPostHandler post;
  };

}
#endif // ALLOCALIZATIONPROXY_H_
