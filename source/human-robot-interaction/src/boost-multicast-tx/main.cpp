/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 31/05/15.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include <iostream>
#include <sstream>
#include <string>
#include <boost/asio.hpp>
#include "boost/bind.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"

const short multicast_port = 5008;
const int max_message_count = 10;

class sender
{
public:
    sender(boost::asio::io_service& io_service, const boost::asio::ip::address& multicast_address):
    endpoint_(multicast_address, multicast_port),
    socket_(io_service, endpoint_.protocol()),
    timer_(io_service),
    message_count_(0)
    {
        std::ostringstream os;
        os << "Message " << message_count_++;
        message_ = os.str();
        
        socket_.async_send_to(
                              boost::asio::buffer(message_), endpoint_,
                              boost::bind(&sender::handle_send_to, this,
                                          boost::asio::placeholders::error));
    }
    
    void handle_send_to(const boost::system::error_code& error)
    {
        if (!error && message_count_ < max_message_count)
        {
            timer_.expires_from_now(boost::posix_time::seconds(1));
            timer_.async_wait(
                              boost::bind(&sender::handle_timeout, this,
                                          boost::asio::placeholders::error));
        }
    }
    
    void handle_timeout(const boost::system::error_code& error)
    {
        if (!error)
        {
            std::ostringstream os;
            os << "Message " << message_count_++;
            message_ = os.str();
            
            socket_.async_send_to(
                                  boost::asio::buffer(message_), endpoint_,
                                  boost::bind(&sender::handle_send_to, this,
                                              boost::asio::placeholders::error));
        }
    }
    
private:
    boost::asio::ip::udp::endpoint endpoint_;
    boost::asio::ip::udp::socket socket_;
    
    
    boost::asio::deadline_timer timer_;
    int message_count_;
    std::string message_;
};

int main(int argc, char* argv[])
{
    try
    {
        
        boost::asio::io_service io_service;
        sender s(io_service, boost::asio::ip::address::from_string("239.255.0.5"));
        io_service.run();
        
        std::cout << "Started";
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    
    return 0;
}