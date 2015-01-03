// Generated for ALConnectionManager version 0

#ifndef ALCONNECTIONMANAGERPROXY_H_
#define ALCONNECTIONMANAGERPROXY_H_

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
  class ALConnectionManagerProxy;

  namespace detail {
    class ALConnectionManagerProxyPostHandler
    {
    protected:
      ALConnectionManagerProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALConnectionManagerProxy;

      /// <summary>
      /// Request a connection to the service. If some input is needed for the connection to succeed, an event will be raised
      /// </summary>
      /// <param name="serviceId"> Service identifier </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int connect(const std::string& serviceId);

      /// <summary>
      /// Destroy the Access Point created on a given technology
      /// </summary>
      /// <param name="technology"> The technology to disable tethering </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int disableTethering(const std::string& technology);

      /// <summary>
      /// Disconnect a service
      /// </summary>
      /// <param name="serviceId"> Service identifier </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int disconnect(const std::string& serviceId);

      /// <summary>
      /// Create a Network Access Point on a given technology and share internet connection if any
      /// </summary>
      /// <param name="technology"> Technology on which enabling tethering </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int enableTethering(const std::string& technology);

      /// <summary>
      /// Create a Network Access Point on a given technology and share internet connection if any
      /// </summary>
      /// <param name="technology"> The technology on which enabling tethering </param>
      /// <param name="name"> The name of the network to create </param>
      /// <param name="Passphrase"> The WPA2 passphrase to connect to the created network </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int enableTethering(const std::string& technology, const std::string& name, const std::string& Passphrase);

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Forget stored information about the service
      /// </summary>
      /// <param name="serviceId"> Service identifier </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int forget(const std::string& serviceId);

      /// <summary>
      /// scan all available services on registered technologies
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int scan();

      /// <summary>
      /// scan for available services on a given technology
      /// </summary>
      /// <param name="technology"> The type of technology to scan </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int scan(const std::string& technology);

      /// <summary>
      /// Set the service configuration
      /// </summary>
      /// <param name="service"> The service to configure </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setServiceConfiguration(const AL::ALValue& service);

      /// <summary>
      /// provide input for pending connection
      /// </summary>
      /// <param name="reply"> The required input requested by the connection manager to finalize the pending connection </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setServiceInput(const AL::ALValue& reply);

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALConnectionManagerProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALConnectionManagerProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALConnectionManagerProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALConnectionManagerProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALConnectionManagerProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Request a connection to the service. If some input is needed for the connection to succeed, an event will be raised
    /// </summary>
    /// <param name="serviceId"> Service identifier </param>
    void connect(const std::string& serviceId);

    /// <summary>
    /// Destroy the Access Point created on a given technology
    /// </summary>
    /// <param name="technology"> The technology to disable tethering </param>
    void disableTethering(const std::string& technology);

    /// <summary>
    /// Disconnect a service
    /// </summary>
    /// <param name="serviceId"> Service identifier </param>
    void disconnect(const std::string& serviceId);

    /// <summary>
    /// Create a Network Access Point on a given technology and share internet connection if any
    /// </summary>
    /// <param name="technology"> Technology on which enabling tethering </param>
    void enableTethering(const std::string& technology);

    /// <summary>
    /// Create a Network Access Point on a given technology and share internet connection if any
    /// </summary>
    /// <param name="technology"> The technology on which enabling tethering </param>
    /// <param name="name"> The name of the network to create </param>
    /// <param name="Passphrase"> The WPA2 passphrase to connect to the created network </param>
    void enableTethering(const std::string& technology, const std::string& name, const std::string& Passphrase);

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// Forget stored information about the service
    /// </summary>
    /// <param name="serviceId"> Service identifier </param>
    void forget(const std::string& serviceId);

    /// <summary>
    /// Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

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
    /// 
    /// </summary>
    /// <param name="technology"> The technology </param>
    /// <returns> Return whether tethering mode is enabled for the given technology. </returns>
    bool getTetheringEnable(const std::string& technology);

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// Just a ping. Always returns true
    /// </summary>
    /// <returns> returns true </returns>
    bool ping();

    /// <summary>
    /// scan all available services on registered technologies
    /// </summary>
    void scan();

    /// <summary>
    /// scan for available services on a given technology
    /// </summary>
    /// <param name="technology"> The type of technology to scan </param>
    void scan(const std::string& technology);

    /// <summary>
    /// Return the service properties
    /// </summary>
    /// <param name="serviceId"> Service identifier </param>
    /// <returns> Return the service properties </returns>
    AL::ALValue service(const std::string& serviceId);

    /// <summary>
    /// Return the list of all network services with their properties
    /// </summary>
    /// <returns> An array of NetworkInfo </returns>
    AL::ALValue services();

    /// <summary>
    /// Set the service configuration
    /// </summary>
    /// <param name="service"> The service to configure </param>
    void setServiceConfiguration(const AL::ALValue& service);

    /// <summary>
    /// provide input for pending connection
    /// </summary>
    /// <param name="reply"> The required input requested by the connection manager to finalize the pending connection </param>
    void setServiceInput(const AL::ALValue& reply);

    /// <summary>
    /// Return the current global state of the connection manager
    /// </summary>
    /// <returns> A string containing the current state </returns>
    std::string state();

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// return the list of all available technologies
    /// </summary>
    /// <returns> An AL::Value containing an array of string </returns>
    AL::ALValue technologies();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="technology"> The technology </param>
    /// <returns> The name of the network used by the tethering mode </returns>
    std::string tetheringName(const std::string& technology);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="technology"> The technology </param>
    /// <returns> The passphrase of the network used by the tethering mode </returns>
    std::string tetheringPassphrase(const std::string& technology);

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


    detail::ALConnectionManagerProxyPostHandler post;
  };

}
#endif // ALCONNECTIONMANAGERPROXY_H_
