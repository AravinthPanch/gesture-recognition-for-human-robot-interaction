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
    udp::socket sock(io_service, udp::endpoint(udp::v4(), port));
    std::cout << "Server Started" << std::endl;
    
    char data[max_length];
    udp::endpoint sender_endpoint;
    sock.receive_from(boost::asio::buffer(data, max_length), sender_endpoint);
    std::cout << "Client connected" <<std::endl;
    
    for (;;)
    {
        strcpy(data, "hello");
        boost::asio::deadline_timer timer(io_service, boost::posix_time::seconds(1));
        timer.wait();
        std::cout << data << std::endl;
        sock.send_to(boost::asio::buffer(data, sizeof(data)), sender_endpoint);
        
    }
}

int main(int argc, char* argv[])
{
    try
    {
        boost::asio::io_service io_service;
        
        using namespace std; // For atoi.
        server(io_service, atoi(SERVER_PORT));
        
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    
    return 0;
}