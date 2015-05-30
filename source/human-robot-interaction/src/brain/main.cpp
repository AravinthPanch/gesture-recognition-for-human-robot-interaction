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
        std::cout << "================ Gesture Recognition For Human-Robot Interaction ================ \n";
        std::cout << "================ Author: Aravinth Panchadcharam <me@aravinth.info> ============== \n" <<std::endl;
        
        boost::asio::io_service io_service;
        brain brain;
        std::string argument1;
        std::string argument2;
        bool optionSelected1 = false;
        
        std::cout << "Press \n 1 -> Predict \n 2 -> Train \n 3 -> Exit \n: ";
        std::getline(std::cin, argument1);
        
        while (!optionSelected1) {
            
            if(argument1 == "1")
            {
                optionSelected1 = true;
                BOOST_LOG_TRIVIAL(info) << "Starting Brain Module for Prediction";
                brain.setPredictionModeActive();
                udp_client client(io_service, &brain);
                boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service));
                while(brain.isPredictionModeActive()){}
            }
            
            else if(argument1 == "2")
            {
                optionSelected1 = true;
                BOOST_LOG_TRIVIAL(info) << "Starting Brain Module for Training";
                brain.setTrainingModeActive();
                udp_client client(io_service, &brain);
                boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service));
                
                while(true){
                    if(!brain.isTrainingModeActive() && !brain.isPredictionModeActive()){
                        
                        BOOST_LOG_TRIVIAL(debug) << "Training Mode Off";
                        std::cout << "Press \n 1 -> Train the Class again \n 2 -> Train Next Class \n 3 -> Stop Training And Go To Prediction Mode \n 4 -> Exit \n: ";
                        std::getline(std::cin, argument2);
                        
                        if(argument2 == "1"){
                            brain.setTrainingModeActive();
                        }
                        else if(argument2 == "2"){
                            brain.trainNext();
                            brain.setTrainingModeActive();
                        }
                        else if(argument2 == "3"){
                            brain.setPredictionModeActive();
                        }
                        else if(argument2 == "4"){
                            BOOST_LOG_TRIVIAL(info) << "Exiting Gesture Recognition For Human-Robot Interaction";
                            return 0;
                        }
                        
                    }
                }
            }
            
            else if(argument1 == "3")
            {
                optionSelected1 = true;
                BOOST_LOG_TRIVIAL(info) << "Exiting Gesture Recognition For Human-Robot Interaction";
                return 0;
            }
            
            else {
                optionSelected1 = false;
                BOOST_LOG_TRIVIAL(info) << "Invalid selection." ;
                std::cout << "Press \n 1 -> Predict \n 2 -> Train \n 3 -> Exit \n: ";
                std::getline(std::cin, argument1);
            }
            
        }
    }
    
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}

