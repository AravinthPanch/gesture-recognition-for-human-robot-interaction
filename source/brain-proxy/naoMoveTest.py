__author__ = 'Aravinth Panchadcharam'
__email__ = "me@aravinth.info"
__date__ = '10/06/15'

import time
from naoqi import ALProxy

robotIP = "nao2.local"
PORT = 9559

motionProxy = ALProxy("ALMotion", robotIP, PORT)
postureProxy = ALProxy("ALRobotPosture", robotIP, PORT)
ttsProxy = ALProxy("ALTextToSpeech", robotIP, PORT)

# Wake up robot
if motionProxy.robotIsWakeUp() is False:
    motionProxy.wakeUp()
    postureProxy.goToPosture("StandInit", 0.5)

ttsProxy.say("hello")
time.sleep(3)

x = 0.5
y = 0.0
theta = 0.0
frequency = 1.0
motionProxy.moveToward(x, y, theta, [["Frequency", frequency]])
time.sleep(5)
motionProxy.stopMove()
motionProxy.rest()


