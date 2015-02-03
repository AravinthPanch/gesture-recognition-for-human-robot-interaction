__author__ = 'Aravinth Panchadcharam'
__email__ = "me@aravinth.info"
__date__ = '10/01/15'

from naoqi import ALProxy

tts = ALProxy("ALTextToSpeech", "localhost", 51626)
motionProxy = ALProxy("ALMotion", "localhost", 51626)


def send(data, logger):
    gesture = int(data['type'])

    if gesture == 0:
        logger.info('Received Gesture One')
        tts.say("one")
        motionProxy.rest()
    elif gesture == 1:
        logger.info('Received Gesture two')
        tts.say("two")
        motionProxy.wakeUp()

