//
//  main.cpp
//  OpenNI2-hello-world
//
//  Created by Aravinth Panchadcharam on 13/11/14.
//  Copyright (c) 2014 Aravinth Panchadcharam. All rights reserved.
//

#include <iostream>
#include <OpenNI.h>
#include <stdio.h>

using namespace openni;
int main(){
    Status rc;
    
    int resp = OpenNI::initialize();
    printf("Success with resp %d", resp);
   
    OpenNI::shutdown();
    return 0;
}
