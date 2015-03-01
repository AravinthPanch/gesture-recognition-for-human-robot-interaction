/**
 * tcpIpCs.cpp
 *
 * http://thisthread.blogspot.com/2011/02/minimal-asio-tcp-server.html
 * http://thisthread.blogspot.com/2011/02/minimal-asio-tcp-client.html
 *
 * http://www.boost.org/doc/libs/1_54_0/doc/html/boost_asio/tutorial/tutdaytime1.html
 * http://www.boost.org/doc/libs/1_54_0/doc/html/boost_asio/tutorial/tutdaytime2.html
 */

#include <iostream>
#include <exception>
#include <array>
#include <boost/asio.hpp>

namespace
{
    const int HELLO_PORT = 50013;
    const char* HELLO_PORT_STR = "50013";
}

void asioTcpServer()
{
    try
    {
        boost::asio::io_service aios;
        boost::asio::ip::tcp::acceptor acceptor(aios,
                                                boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), HELLO_PORT));
        
        // just once
        {
            boost::asio::ip::tcp::socket socket(aios);
            std::cout << "Server ready" << std::endl;
            acceptor.accept(socket);
            
            std::string message("Hello from ASIO");
            boost::asio::write(socket, boost::asio::buffer(message));
        }
    }
    catch(std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void asioTcpClient(const char* host)
{
    try
    {
        boost::asio::io_service aios;
        
        boost::asio::ip::tcp::resolver resolver(aios);
        boost::asio::ip::tcp::resolver::iterator endpoint = resolver.resolve(
                                                                             boost::asio::ip::tcp::resolver::query(host, HELLO_PORT_STR));
       
        boost::asio::ip::tcp::socket socket(aios);
        // open the connection for the specified endpoint, or throws a system_error
        boost::asio::connect(socket, endpoint);
        
        for(;;)
        {
            std::array<char, 4> buf;
            boost::system::error_code error;
            size_t len = socket.read_some(boost::asio::buffer(buf), error);
            
            if(error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer
            else if(error)
                throw boost::system::system_error(error);
            
            std::cout.write(buf.data(), len);
            std::cout << '|';
        }
        std::cout << std::endl;
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

int main(int argc, char* argv[])
{
    if(argc > 1)
        asioTcpClient("localhost");
    else
        asioTcpServer();
}