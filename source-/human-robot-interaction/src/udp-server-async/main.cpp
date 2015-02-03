#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "ni.h"

using boost::asio::ip::udp;

class udp_server
{
    
private:
    const short SERVER_PORT = 50005;
    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 4> recv_buffer_;
    
    void start_receive()
    {
        socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_,
                                   boost::bind(&udp_server::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
    
    void handle_receive(const boost::system::error_code& error, std::size_t )
    {
        if (!error || error == boost::asio::error::message_size)
        {
            std::cout << "Received " << remote_endpoint_ << std::endl;
            ni::hola();
            start_receive();
        }
        else{
            std::cout << "Error " << remote_endpoint_ << std::endl;
        }
    }
    
    void handle_send(boost::shared_ptr<std::string> /*message*/,const boost::system::error_code& /*error*/,std::size_t /*bytes_transferred*/)
    {
        std::cout << "Sent " << remote_endpoint_ << std::endl;
    }
    
public:
    
    udp_server(boost::asio::io_service& io_service) : socket_(io_service, udp::endpoint(udp::v4(), SERVER_PORT))
    {
        start_receive();
        std::cout << "Started" << std::endl;
    }
    
    void send(){
        
        boost::shared_ptr<std::string> message(new std::string("Hola"));
        
        socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
                              boost::bind(&udp_server::handle_send, this, message, boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
    }
};



int main()
{
//    try
//    {
//        
//        boost::asio::io_service service;
//        udp_server server(service);
//        boost::thread thread(boost::bind(&boost::asio::io_service::run, &service));
//        //        boost::thread thread2(print, &server);
//        
//        std::cout << "Press enter to terminate whenever you want!" << std::endl;
//        std::string request;
//        std::getline(std::cin, request);
//        service.stop();
//        
//    }
//    catch (std::exception& e)
//    {
//        std::cerr << e.what() << std::endl;
//    }
    
    return 0;
}