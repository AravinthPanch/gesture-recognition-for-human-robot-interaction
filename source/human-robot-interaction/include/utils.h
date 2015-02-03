/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 23/01/15.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */


#ifndef __human_robot_interaction__utils__
#define __human_robot_interaction__utils__

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>

class utils{
public:
    static int wasKeyboardHit()
    {
        struct termios oldt, newt;
        int ch;
        int oldf;
        
        // don't echo and don't wait for ENTER
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        
        // make it non-blocking (so we can check without waiting)
        if (0 != fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK))
        {
            return 0;
        }
        
        ch = getchar();
        
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        if (0 != fcntl(STDIN_FILENO, F_SETFL, oldf))
        {
            return 0;
        }
        
        if(ch != EOF)
        {
            ungetc(ch, stdin);
            return 1;
        }
        
        return 0;
    }
    
    static void 
};

#endif


