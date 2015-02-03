/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 22/12/14.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */


#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using boost::asio::ip::udp;

enum { max_length = 1024 };
const char* SERVER_PORT = "50005";

void server(boost::asio::io_service& io_service, short port)
{
    udp::socket socket(io_service, udp::endpoint(udp::v4(), port));
    std::cout << "Server Started" << std::endl;
    
    char data[max_length];
    udp::endpoint sender_endpoint;
    socket.receive_from(boost::asio::buffer(data, 5), sender_endpoint);
    std::cout << "UDP Client is connected from the address " << sender_endpoint <<std::endl;
    
    for (;;)
    {
        strcpy(data, "hello");
        boost::asio::deadline_timer timer(io_service, boost::posix_time::seconds(1));
        timer.wait();
//        std::cout << data << sender_endpoint << std::endl;
        socket.send_to(boost::asio::buffer(data, 5), sender_endpoint);
    }
}

int main(int argc, char* argv[])
{
    try
    {
        boost::asio::io_service io_service;
        server(io_service, std::atoi(SERVER_PORT));
        
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    
    return 0;
}