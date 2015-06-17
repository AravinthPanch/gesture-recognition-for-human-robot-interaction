__author__ = 'Aravinth Panchadcharam'
__email__ = "me@aravinth.info"
__date__ = '16/06/15'


from naoqi import ALProxy

robotIP = "nao2.local"
PORT = 9559

motionProxy = ALProxy("ALMotion", robotIP, PORT)

joints = ["HeadPitch", "HeadYaw"]
angles = [-0.3145120143890381, -0.013848066329956055]
fractionMaxSpeed = 0.1

motionProxy.setAngles(joints, angles, fractionMaxSpeed)


# [-0.317579984664917, -0.0123138427734375]
