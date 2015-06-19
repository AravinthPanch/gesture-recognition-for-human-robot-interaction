# To move the robot at the given normalized velocity using Aldebaran Motion and Posture API

import time
from naoqi import ALProxy

robotIP = "nao.local"
PORT = 9559
motionProxy = ALProxy("ALMotion", robotIP, PORT)
postureProxy = ALProxy("ALRobotPosture", robotIP, PORT)

# Wake up robot
motionProxy.wakeUp()

# Send robot to Pose Init
postureProxy.goToPosture("StandInit", 0.5)

# x - normalized, unitless, velocity along X-axis. +1 and -1 correspond to the maximum velocity in the forward and backward directions, respectively.
# y - normalized, unitless, velocity along Y-axis. +1 and -1 correspond to the maximum velocity in the left and right directions, respectively.
# theta - normalized, unitless, velocity around Z-axis. +1 and -1 correspond to the maximum velocity in the counterclockwise and clockwise directions, respectively.

x = 1.0
y = 0.0
theta = 0.0
frequency = 1.0
motionProxy.moveToward(x, y, theta, [["Frequency", frequency]])

# Lets make him stop after 3 seconds
time.sleep(3)
motionProxy.stopMove()

# Go to rest position
motionProxy.rest()

