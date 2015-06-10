__author__ = 'Aravinth Panchadcharam'
__email__ = "me@aravinth.info"
__date__ = '09/06/15'

from naoqi import ALProxy

# tts = ALProxy("ALTextToSpeech", "nao2.local", 9559)
motion = ALProxy("ALMotion", "nao2.local", 9559)
# tts.say("hello")
motion.wakeUp()
