#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <OpenNI.h>

#define SAMPLE_READ_WAIT_TIMEOUT 2000 //2000ms

const char* SERVER_PORT = "50005";

using boost::asio::ip::udp;
using namespace openni;

int readSensor(boost::asio::io_service& io_service, short port)
{
    
    //Socket
    udp::socket socket(io_service, udp::endpoint(udp::v4(), port));
    std::cout << "Server Started" << std::endl;
    
    char data[1024];
    udp::endpoint sender_endpoint;
    socket.receive_from(boost::asio::buffer(data, 1024), sender_endpoint);
    std::cout << "Client connected" <<std::endl;
    
    
    // OPEN NI
    Status rc = OpenNI::initialize();
    if (rc != STATUS_OK)
    {
        printf("Initialize failed\n%s\n", OpenNI::getExtendedError());
        return 1;
    }
    
    Device device;
    rc = device.open(ANY_DEVICE);
    if (rc != STATUS_OK)
    {
        printf("Couldn't open device\n%s\n", OpenNI::getExtendedError());
        return 2;
    }
    
    VideoStream depth;
    
    if (device.getSensorInfo(SENSOR_DEPTH) != NULL)
    {
        rc = depth.create(device, SENSOR_DEPTH);
        if (rc != STATUS_OK)
        {
            printf("Couldn't create depth stream\n%s\n", OpenNI::getExtendedError());
            return 3;
        }
    }
    
    rc = depth.start();
    if (rc != STATUS_OK)
    {
        printf("Couldn't start the depth stream\n%s\n", OpenNI::getExtendedError());
        return 4;
    }
    
    VideoFrameRef frame;
    
    for(;;)
    {
        int changedStreamDummy;
        VideoStream* pStream = &depth;
        rc = OpenNI::waitForAnyStream(&pStream, 1, &changedStreamDummy, SAMPLE_READ_WAIT_TIMEOUT);
        if (rc != STATUS_OK)
        {
            printf("Wait failed! (timeout is %d ms)\n%s\n", SAMPLE_READ_WAIT_TIMEOUT, OpenNI::getExtendedError());
            continue;
        }
        
        rc = depth.readFrame(&frame);
        if (rc != STATUS_OK)
        {
            printf("Read failed!\n%s\n", OpenNI::getExtendedError());
            continue;
        }
        
        if (frame.getVideoMode().getPixelFormat() != PIXEL_FORMAT_DEPTH_1_MM && frame.getVideoMode().getPixelFormat() != PIXEL_FORMAT_DEPTH_100_UM)
        {
            printf("Unexpected frame format\n");
            continue;
        }
        
        DepthPixel* pDepth = (DepthPixel*)frame.getData();
        
        int middleIndex = (frame.getHeight()+1)*frame.getWidth()/2;
        
        std::cout << *pDepth << std::endl;
        
        socket.send_to(boost::asio::buffer(pDepth, 1024), sender_endpoint);
    }
    
    depth.stop();
    depth.destroy();
    device.close();
    OpenNI::shutdown();
}


int main()
{
    
    try
    {
        boost::asio::io_service io_service;
        readSensor(io_service, std::atoi(SERVER_PORT));
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    
    return 0;
}
