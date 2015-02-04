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


INSTALLATION
--------------------------------------

```
git clone git@github.com:AravinthPanch/gesture-recognition-for-human-robot-interaction.git hri
cd hri/source/human-robot-interaction
sudo cp lib/OpenNI2/libOpenNI2.so /usr/lib
sudo cp lib/NiTE2/libNiTE2.so /usr/lib
sudo cp lib/NiTE2/NiTE.ini /usr/lib
sudo cp -R lib/NiTE2/NiTE2 /usr/lib
mkdir build; cd build
cmake .. -DSELECT_SUBPROJECT=human-robot-interaction
make
```



USAGE
--------------------------------------
-



TESTED ON
--------------------------------------
- Mac OSX 10.10 (Yosemite)
- Ubuntu Linux
- Gentoo Linux
