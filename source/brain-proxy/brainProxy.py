__author__ = 'Aravinth Panchadcharam'
__email__ = "me@aravinth.info"
__date__ = '09/06/15'

import logging
import sys
import json
import websocket
from naoqi import ALProxy
from naoMotion import NaoMotion


class BrainProxy():
    def __init__(self):
        self.init_logger()
        self.read_config()
        self.log.info("Brain Proxy started")

        self.naoMotion = NaoMotion(str(self.config['serverHostName']), int(self.config['naoQiPort']))
        self.ttsProxy = ALProxy("ALTextToSpeech", str(self.config['serverHostName']), int(self.config['naoQiPort']))

        websocket.enableTrace(False)
        self.ws_uri = "ws://localhost:" + str(self.config['websocketPort'])
        self.ws = websocket.WebSocketApp(self.ws_uri,
                                         on_message=self.on_message,
                                         on_error=self.on_error,
                                         on_close=self.on_close)
        self.ws.on_open = self.on_open
        self.ws.run_forever()

    def on_message(self, ws, message):
        self.log.info("Received : " + message)
        sign = str(json.loads(message)['GESTURE'])
        self.ttsProxy.say(sign)
        self.log.info("Message sent to Al-TTS")
        # self.naoMotion.handGesture(data)
        self.naoMotion.walk(sign)


    def on_error(self, ws, error):
        print error

    def on_close(self, ws):
        self.log.info("Connection closed")

    def on_open(self, ws):
        self.ws.send("AL")
        self.log.info("Connected to Brain")

    def read_config(self):
        with open('../config/hri.json') as config_file:
            self.config = json.load(config_file)
        self.log.info("Config file parsed")

    def init_logger(self):
        self.log = logging.getLogger('brain')
        self.log.setLevel(logging.INFO)
        format = logging.Formatter("%(asctime)s - %(name)s - %(levelname)s - %(message)s")
        ch = logging.StreamHandler(sys.stdout)
        ch.setFormatter(format)
        self.log.addHandler(ch)


if __name__ == "__main__":
    BrainProxy()

