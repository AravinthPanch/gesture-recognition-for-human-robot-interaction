/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 08/06/15.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#include <iostream>
#include <alproxies/altexttospeechproxy.h>
#include <alproxies/almotionproxy.h>

int main(int argc, char* argv[])
{
    const std::string phraseToSay = "Hello world";
    AL::ALTextToSpeechProxy tts("127.0.0.1", 9559);
    tts.say(phraseToSay);
}