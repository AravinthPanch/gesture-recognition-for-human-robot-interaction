#include <iostream>
#include <string>
#include <boost/asio.hpp>
 
namespace
{
    const int HELLO_PORT = 50013; // 1
}
 
void asioTcpServer(){
    try
    {
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), HELLO_PORT);
        boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);
        boost::asio::ip::tcp::socket socket(io_service);
 
        std::cout << "Server ready" << std::endl; // 2
        // just once
        {
            acceptor.accept(socket); // 3 
            std::string message("Hello from server\n");
            boost::asio::write(socket, boost::asio::buffer(message)); // 4
            
        }
    }
    catch(std::exception& e) // 6
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}


int main()
{

}