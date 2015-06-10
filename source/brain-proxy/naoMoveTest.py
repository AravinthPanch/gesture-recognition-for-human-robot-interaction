__author__ = 'Aravinth Panchadcharam'
__email__ = "me@aravinth.info"
__date__ = '10/06/15'

import time
from naoqi import ALProxy

robotIP = "localhost"
PORT = 55291

motionProxy = ALProxy("ALMotion", robotIP, PORT)
postureProxy = ALProxy("ALRobotPosture", robotIP, PORT)

# Wake up robot
motionProxy.wakeUp()

# Send robot to Pose Init
postureProxy.goToPosture("StandInit", 0.5)

# Example showing the use of moveToward
# The parameters are fractions of the maximums
# Here we are asking for full speed forwards
x = 0.5
y = 0.0
theta = 0.6
frequency = 1.0
motionProxy.moveToward(x, y, theta, [["Frequency", frequency]])
time.sleep(5)
motionProxy.stopMove()
motionProxy.rest()


# If we don't send another command, he will move forever
# Lets make him slow down(step length) and turn after 3 seconds
# time.sleep(3)
# x = 0.5
# theta = 0.6
# motionProxy.moveToward(x, y, theta, [["Frequency", frequency]])
#
# # Lets make him slow down(frequency) after 3 seconds
# time.sleep(3)
# frequency = 0.5
# motionProxy.moveToward(x, y, theta, [["Frequency", frequency]])
#
# # Lets make him stop after 3 seconds
# time.sleep(3)
# motionProxy.stopMove()
# # Note that at any time, you can use a moveTo command
# # to run a precise distance. The last command received,
# # of velocity or position always wins
#
# # Go to rest position
# motionProxy.rest()