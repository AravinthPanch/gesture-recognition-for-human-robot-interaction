#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>


enum { max_length = 1024 };
const char* SERVER_PORT = "50005";
//const char* SERVER_HOST_NAME = "nao5.local";
const char* SERVER_HOST_NAME = "localhost";

int main(int argc, char* argv[])
{
    try
    {
        using boost::asio::ip::udp;
        
        boost::asio::io_service io_service;
        udp::socket socket(io_service, udp::endpoint(udp::v4(), 0));
        udp::resolver resolver(io_service);
        udp::resolver::query query(udp::v4(), SERVER_HOST_NAME, SERVER_PORT);
        udp::resolver::iterator iterator = resolver.resolve(query);
        
        char request[max_length]= "start";
        socket.send_to(boost::asio::buffer(request, std::strlen(request)), *iterator);
        udp::endpoint sender_endpoint;
        
        std::cout << "Client Started" <<std::endl;
        
        for(;;){
            char reply[max_length];
            socket.receive_from(boost::asio::buffer(reply, max_length), sender_endpoint);
            std::cout << reply << std::endl;
        }
    }
    
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    
    return 0;
}