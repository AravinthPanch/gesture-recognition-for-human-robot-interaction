/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 31/05/15.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "boost/bind.hpp"

const short multicast_port = 5008;

class receiver
{
public:
    receiver(boost::asio::io_service& io_service, const boost::asio::ip::address& listen_address,const boost::asio::ip::address& multicast_address):
    socket_(io_service)
    {
        // Create the socket so that multiple may be bound to the same address.
        boost::asio::ip::udp::endpoint listen_endpoint(
                                                       listen_address, multicast_port);
        socket_.open(listen_endpoint.protocol());
        socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
        socket_.bind(listen_endpoint);
        
        // Join the multicast group.
        socket_.set_option(
                           boost::asio::ip::multicast::join_group(multicast_address));
        
        socket_.async_receive_from(
                                   boost::asio::buffer(data_, max_length), sender_endpoint_,
                                   boost::bind(&receiver::handle_receive_from, this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred));
    }
    
    void handle_receive_from(const boost::system::error_code& error,
                             size_t bytes_recvd)
    {
        if (!error)
        {
            std::cout.write(data_, bytes_recvd);
            std::cout << std::endl;
            
            socket_.async_receive_from(
                                       boost::asio::buffer(data_, max_length), sender_endpoint_,
                                       boost::bind(&receiver::handle_receive_from, this,
                                                   boost::asio::placeholders::error,
                                                   boost::asio::placeholders::bytes_transferred));
        }
    }
    
private:
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint sender_endpoint_;
    enum { max_length = 1024 };
    char data_[max_length];
};

int main(int argc, char* argv[])
{
    try
    {
        boost::asio::io_service io_service;
        receiver r(io_service,
                   boost::asio::ip::address::from_string("0.0.0.0"),
                   boost::asio::ip::address::from_string("239.255.0.5"));
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    
    return 0;
}