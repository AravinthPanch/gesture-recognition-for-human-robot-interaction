#include <iostream>
#include <alerror/alerror.h>
#include <alproxies/altexttospeechproxy.h>

int main(int argc, char* argv[])
{
    AL::ALTextToSpeechProxy tts("localhost");
    tts.say("Hello");
    exit(0);
}
