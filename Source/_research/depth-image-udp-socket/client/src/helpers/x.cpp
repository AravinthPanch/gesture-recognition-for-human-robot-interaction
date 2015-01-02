#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

const char* SERVER_PORT = "50005";
const char* HOST = "localhost";

using boost::asio::ip::tcp;

enum { max_length = 1024 };

int main(int argc, char* argv[])
{
    try
    {
        boost::asio::io_service io_service;
        
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(tcp::v4(), HOST, SERVER_PORT);
        tcp::resolver::iterator iterator = resolver.resolve(query);
        
        tcp::socket socket(io_service);
        boost::asio::connect(socket, iterator);

        std::cout << "Connected" << std::endl;
        
        char reply[max_length];
        boost::asio::read(socket, boost::asio::buffer(reply, max_length));
        
        std::cout << reply << std::endl;
    }
    
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    
    return 0;
}