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

joints = ["HeadPitch", "HeadYaw"]
fractionMaxSpeed = 0.1
angles = [0.06438612937927246, -4.1961669921875e-05]
motionProxy.setAngles(joints, angles, fractionMaxSpeed)


# Wake up robot
# if motionProxy.robotIsWakeUp() is False:
#     motionProxy.wakeUp()
#     postureProxy.goToPosture("StandInit", 0.5)
#     motionProxy.setAngles(joints, angles, fractionMaxSpeed)

#
#
# time(3)
ttsProxy.say("Walk")

x = 0.5
y = 0.0
theta = 0.0
frequency = 1.0
motionProxy.moveToward(x, y, theta, [["Frequency", frequency]])
time.sleep(5)
motionProxy.stopMove()
# motionProxy.rest()

time.sleep(2)
angles = [-0.3145120143890381, -0.013848066329956055]
motionProxy.setAngles(joints, angles, fractionMaxSpeed)





