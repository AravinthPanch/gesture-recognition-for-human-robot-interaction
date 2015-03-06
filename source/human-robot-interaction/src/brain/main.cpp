/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 04/03/15.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/log/trivial.hpp>
#include "udp_client.h"
#include "brain.h"


int main(int argc, char* argv[])
{
    try
    {
        boost::asio::io_service io_service;
        brain brain;
        
        std::cout << "Press \n 1 -> predict \n 2 -> train \n: ";
        std::string argument;
        std::getline(std::cin, argument);
        
        if(argument == "1")
        {
            BOOST_LOG_TRIVIAL(info) << "Starting Brain Module for Prediction";
            
            brain.setPredictionModeActive();
            
            udp_client client(io_service, &brain);
            boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service));
            
            while(brain.isPredictionModeActive()){}
            
        }
        else if(argument == "2")
        {
            BOOST_LOG_TRIVIAL(info) << "Starting Brain Module for Training";
            
            brain.setTrainingModeActive();
            
            udp_client client(io_service, &brain);
            boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service));
            
            while(true){
                if(!brain.isTrainingModeActive() && !brain.isPredictionModeActive()){
                    
                    BOOST_LOG_TRIVIAL(debug) << "Training Mode Off";
                    std::cout << "Press \n 1 -> Train next class \n 2 -> Stop training and go to prediction mode \n: ";
                    std::getline(std::cin, argument);
                    
                    if(argument == "1"){
                        brain.trainNext();
                        brain.setTrainingModeActive();
                    }
                    else if(argument == "2"){
                        brain.setPredictionModeActive();
                    }
                }
            }
        }
        
    }
    
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}

