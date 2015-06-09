/**
 * Copyright (c) 2011 Aldebaran Robotics. All Rights Reserved
 * \file sayhelloworld.cpp
 * \brief Make NAO say a short phrase.
 *
 * A simple example showing how to make NAO say a short phrase using the
 * specialized proxy ALTextToSpeechProxy.
 */


#include <iostream>
#include <alerror/alerror.h>
#include <alproxies/altexttospeechproxy.h>
 #include <alproxies/almotionproxy.h>

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    std::cerr << "Wrong number of arguments!" << std::endl;
    std::cerr << "Usage: say NAO_IP" << std::endl;
    exit(2);
  }

  /** The desired phrase to be said. */
  const std::string phraseToSay = "Hello world";
  try
  {
    /** Create an ALTextToSpeechProxy so that we can call the say method
    * Arguments for the constructor are:
    *  - IP of the robot
    *  - port on which NAOqi is listening. Default is 9559
    */
    AL::ALTextToSpeechProxy tts(argv[1], 9559);

    /** Call the say method */
    tts.say(phraseToSay);

    AL::ALMotionProxy motion(argv[1], 9559);
    motion.wakeUp();
    motion.rest();
  }
  catch (const AL::ALError& e)
  {
    std::cerr << "Caught exception: " << e.what() << std::endl;
    exit(1);
  }
  exit(0);
}
