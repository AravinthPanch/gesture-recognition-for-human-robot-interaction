# To say the specified string of characters in the specified language.

from naoqi import ALProxy

robotIP = "nao.local"
PORT = 9559
tts = ALProxy("ALTextToSpeech", robotIP, PORT)

# sets the language to english
tts.setLanguage("English")

# say words given
tts.say("Hello World")
