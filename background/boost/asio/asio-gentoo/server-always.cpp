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



int main()
{
    if(argc > 1)
        asioTcpClient("localhost");
    else
        asioTcpServer();
}