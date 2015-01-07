__author__ = 'Aravinth Panchadcharam'
__email__ = "me@aravinth.info"
__project__ = 'Gesture Recognition for Human-Robot Interaction'
__date__ = '07/01/15'


from naoqi import ALProxy
ip = 55838
motionProxy = ALProxy("ALMotion", "localhost", ip)

motionProxy.wakeUp()
motionProxy.rest()
