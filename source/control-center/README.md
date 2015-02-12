Control Center - CC module
==================================================================

DESCRIPTION
--------------------------------------
This module works as the control center of the project which will be installed on off-board computer.
Control Center serves as dashboard to visualize the interaction between the Robot, Depth Camera and Brain module.
It is a cross compatible tool that can work in any latest WebBrowser.


TECHNICAL DETAIL
--------------------------------------
Control center is developed in Javascript using NodeJS, ThreeJS and WebSockets.
It contains an UDP Client and a dashboard.

- UDP Client is an asynchronous app that connects to the UDP Server at localhost:5005 or nao5.local:5005.
UDP client uses the port number 5006 in order to avoid the conflicts between many clients connecting to the server.

- Dashboard is a webApp that receives streamed data from the UDP Client via WebSocket and uses ThreeJS (WebGL) to draw it on the canvas in real time.
It will also used to analyse the data that is being streamed by the UDP Server in the robot. Dashboard also contains controls to interact with the robot.


DEPENDENCIES
--------------------------------------
Install NodeJS on Mac OSX
```
brew update
brew install node
brew install git
```

Install NodeJS on Ubuntu
```
sudo apt-get update
curl -sL https://deb.nodesource.com/setup | sudo bash -
sudo apt-get install -y nodejs
sudo apt-get install git
```

INSTALLATION
--------------------------------------
First install
```
git clone git@github.com:AravinthPanch/gesture-recognition-for-human-robot-interaction.git ~/hri
cd ~/hri/source/control-center
sudo npm install
```

USAGE
--------------------------------------
This will start a control center web app at http://localhost:5007 in your default browser.
```
cd ~/hri/source/control-center
gulp
```

Click on Hand Tracking or Skeleton Tracking button to initiate.


SUPPORTED BROWSERS
--------------------------------------
- Google Chrome
- Mozilla Firefox
- Safari


TESTED ON
--------------------------------------
- Mac OSX 10.10 (Yosemite)
- Ubuntu Linux

