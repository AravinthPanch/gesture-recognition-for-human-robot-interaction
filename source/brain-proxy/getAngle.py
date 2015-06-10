from naoqi import ALProxy

motionProxy = ALProxy("ALMotion", "nao2.local", 9559)
names = ["LShoulderRoll", "LShoulderPitch", "LElbowRoll", "LElbowYaw","RShoulderRoll", "RShoulderPitch", "RElbowRoll", "RElbowYaw"]
sensorAngles = motionProxy.getAngles(names, True)
print "Angles:"
print str(sensorAngles)
print ""

names = ["Body"]
sensorAngles = motionProxy.getAngles(names, True)
print "Body Angles:"
print str(sensorAngles)
print ""
