Human-Robot-Interaction - HRI module
==================================================================

DESCRIPTION
--------------------------------------
This module (Human-Robot-Interaction or HRI module) of the project is the main module that will be installed on the robot in order to get the skeletal information of the user in front of the robot via UDP stream.
HRI module works in two modes.

- User Tracking mode where 15 skeletal joints of users are tracked
- Hand Tracking mode where only the joint of hand (wrist or palm) of users are tracked


TECHNICAL DETAIL
--------------------------------------
HRI module is implemented in C++ using libraries such as Boost, OpenNI2 and NiTE2.
As described above HRI module must be installed on the robot with necessary libraries and drivers.
HRI module internally contains an UDP Server, UDP Client, Skeleton Tracker and Gesture Tracker.

- UDP Server is an asynchronous app that is implemented using Boost ASIO.
Once HRI module is started, UDP Server is initiated and waits for the UDP client to connect at port number 5005.

- UDP Client is an asynchronous app that connects to the UDP Server at localhost:5005 or nao5.local:5005.
UDP client uses the port number 5006 in order to avoid the conflicts between many clients connecting to the server.

- Skeleton Tracker uses OpenNI2 and NiTE2 libraries to track 15 skeletal joints of a user.

- Gesture Tracker is same as above but tracks only the hand joint and tracking must be initiated by using the 'WAVE' gesture.
Along with the position of hand joint (x,y,z), it also sends the information to the client whether WAVE or CLICK gesture is detected.

DEPENDENCIES
--------------------------------------
On Mac OSX
```
xcode-select --install
brew update
brew install boost
brew install cmake
brew install git
```

On Ubuntu
```
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install cmake
sudo apt-get install libboost-all-dev
sudo apt-get install git
```

BUILD
--------------------------------------

```
git clone git@github.com:AravinthPanch/gesture-recognition-for-human-robot-interaction.git ~/hri
cd ~/hri/source/human-robot-interaction
mkdir build; cd build
cmake ..
make
```

BUILDING ON OpenNAO-vm.2.1.2 for Nao with NaoQi 2.1.2
--------------------------------------
### Problem ###

- NAO runs on Gentoo Linux (2.6.33.9-rt31-aldebaran-rt) with Intel Atom Processor with i686 Architecture
- Aldeberan provides an image of NAO OS named as OpenNAO that can be run in a virtual machine
- C++ version available on OpenNAO/Nao is libstdc++.so.6.0.14
- GCC version available on OpenNAO is 4.5.3 (Gentoo 4.5.3-r1 p1.0, pie-0.4.5) with GLIBCXX_3.4.14.
Use the following command in OpenNAO to check it.
```
strings /usr/lib/libstdc++.so.6 | grep GLIBC
```
- Emerge is the package manager for Gentoo Linux and Portage is the package tree
- Portage tree used with OpenNAO/Nao was last updated on 11 Jan 2012. Use the following command in OpenNAO to check it.
```
emerge --info
```
- Aldeberan doesn't allow users to update emerge/portage tree because that will lead to conflicts with their software
- NiTE middleware library(libNiTE2.so) was built by PrimeSense using higher version of GCC (higher than GLIBCXX_3.4.14 or libstdc++.so.6.0.14)
- If you build the code with GCC 4.5.3, it will throw an error while linking libNiTE2.so, '/usr/lib/libstdc++.so.6: version GLIBCXX_3.4.15 not found'
- Hence small hack must be done in order to do that.
 - libstdc++6_4.6.1-1_i386.deb was downloaded from http://snapshot.debian.org/package/gcc-4.6/4.6.1-1
 - libstdc++6_4.6.1-1_i386.deb -> Right click -> Open With -> Archive Manager (Archive Manager available in Ubuntu)
 - Library was found under ﻿/usr/lib/i386-linux-gnu/libstdc++.so.6.0.16

### Solution ###

Please execute the following commands in OpenNAO to apply the patch
```
cd ~/hri/source/human-robot-interaction
sudo cp lib/libstdc++.so.6.0.16 /usr/lib
sudo rm libstdc++.so
sudo ln -s libstdc++.so.6.0.16 libstdc++.so
```

Use the following command in OpenNAO and now it should show versions upto GLIBCXX_3.4.16
```
strings /usr/lib/libstdc++.so.6 | grep GLIBC
```

Finally build it
```
cd ~/hri/source/human-robot-interaction
mkdir build; cd build
cmake ..
make
```

INSTALLATION
--------------------------------------
To run it on Robot, executable and libraries must be copied to NAO (Nao must be available in the same network).
```
cd ~/hri/source/human-robot-interaction
scp bin/human-robot-interaction nao@nao.local:~/hri/
scp lib/NiTE2/libNiTE2-32.so nao@nao.local:/usr/lib/libNiTE2.so
scp lib/NiTE2/NiTE.ini nao@nao.local:/usr/lib
scp -r lib/NiTE2/NiTE2 nao@nao.local:/usr/lib
scp lib/libstdc++.so.6.0.16 /usr/lib
```

Patch must be applied on NAO as well. Run these commands on NAO.
```
ssh nao@nao.local
cd /usr/lib
su #password is root
rm libstdc++.so
ln -s libstdc++.so.6.0.16 libstdc++.so
```

To run it on local machine Mac OSX, Ubuntu, OpenNAO
```
sudo cp lib/OpenNI2/libOpenNI2.{so,dylib} /usr/lib
sudo cp lib/NiTE2/libNiTE2.{so,dylib} /usr/lib
sudo cp lib/NiTE2/NiTE.ini /usr/lib
sudo cp -R lib/NiTE2/NiTE2 /usr/lib
```

USAGE
--------------------------------------
On local machine
```
~/hri/source/human-robot-interaction/bin/human-robot-interaction
```

On NAO
```
~/hri/human-robot-interaction
```

It will ask you "Do you want to start server or client? "
- option "server" will initiate UDP Server, Gesture Tracker (hand tracking and gesture tracking)
- option "server skel" will initiate UDP Server, Skeleton Tracker (full body skeleton tracking)
- option "client" will initiate UDP Client internally


TESTED ON
--------------------------------------
- Mac OSX 10.10 (Yosemite)
- Ubuntu Linux
- Gentoo Linux
