from naoqi import ALProxy

motionProxy = ALProxy("ALMotion", "nao2.local", 9559)
# names = ["LShoulderRoll", "LShoulderPitch", "LElbowRoll", "LElbowYaw","RShoulderRoll", "RShoulderPitch", "RElbowRoll", "RElbowYaw"]
# sensorAngles = motionProxy.getAngles(names, True)
# print "Angles:"
# print str(sensorAngles)
# print ""
#
# names = ["Body"]
# sensorAngles = motionProxy.getAngles(names, True)
# print "Body Angles:"
# print str(sensorAngles)
# print ""


names = ["HeadPitch", "HeadYaw"]
sensorAngles = motionProxy.getAngles(names, True)
print "Head Pitch and Yaw:"
print str(sensorAngles)
print ""


# Head Pitch and Yaw:
# [-0.3145120143890381, -0.013848066329956055]

#head reset
# [-0.018450021743774414, -0.009245872497558594]


