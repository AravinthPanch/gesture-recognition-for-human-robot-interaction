__author__ = 'Aravinth Panchadcharam'
__email__ = "me@aravinth.info"
__date__ = '09/06/15'

import logging
import sys
import json
import websocket
from naoqi import ALProxy


class BrainProxy():
    def __init__(self):
        self.init_logger()
        self.read_config()
        self.log.info("Brain Proxy started")

        self.tts = ALProxy("ALTextToSpeech", str(self.config['serverHostName']), int(self.config['naoQiPort']))

        websocket.enableTrace(False)
        self.ws_uri = "ws://" + str(self.config['serverHostName']) + ":" + str(self.config['websocketPort'])
        self.ws = websocket.WebSocketApp(self.ws_uri,
                                         on_message=self.on_message,
                                         on_error=self.on_error,
                                         on_close=self.on_close)
        self.ws.on_open = self.on_open
        self.ws.run_forever()

    def on_message(self, ws, message):
        self.log.info("Received : " + message)
        data = str(json.loads(message)['GESTURE'])
        self.al_tts(data)

    def on_error(self, ws, error):
        print error

    def on_close(self, ws):
        self.log.info("Connection closed")

    def on_open(self, ws):
        self.ws.send("AL")
        self.log.info("Connected to Brain")

    def al_tts(self, message):
        self.tts.say(message)
        self.log.info("Message sent to Al-TTS")

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
