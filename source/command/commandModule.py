__author__ = 'Aravinth Panchadcharam'
__email__ = "me@aravinth.info"
__project__ = 'Gesture Recognition For Human-Robot Interaction'
__date__ = '09/06/15'

import logging
import sys
import json
import websocket
from naoMotion import NaoMotion


class CommandModule():
    def __init__(self):
        self.init_logger()
        self.read_config()
        self.log.info("Command module started")
        self.host_name = str(self.config['serverHostName'])
        self.host_name = "nao5.local"
        self.naoqi_port = int(self.config['naoQiPort'])
        self.naoMotion = NaoMotion(self.host_name, self.naoqi_port)

        websocket.enableTrace(False)
        self.ws_uri = "ws://localhost:" + str(self.config['websocketPort'])
        self.ws = websocket.WebSocketApp(self.ws_uri,
                                         on_message=self.on_message,
                                         on_error=self.on_error,
                                         on_close=self.on_close)
        self.ws.on_open = self.on_open
        self.ws.run_forever()

    # When message received, command Nao Action
    def on_message(self, ws, message):
        self.log.info("Received : " + message)
        msg = json.loads(message)
        if "INFO" in msg:
            if "FOV" not in msg['INFO']:
                info = str(msg['INFO'])
                self.naoMotion.gesture_to_speech(info)
        elif "GESTURE" in msg:
            sign = str(msg['GESTURE'])
            self.naoMotion.gesture_to_speech(sign)
            # self.naoMotion.gesture_to_motion(sign)
            self.naoMotion.gesture_to_gesture(sign)

    def on_error(self, ws, error):
        print error

    def on_close(self, ws):
        self.log.info("Connection closed")

    def on_open(self, ws):
        self.ws.send("AL")
        self.log.info("Connected to Brain")

    # Read the common config file
    def read_config(self):
        with open('../config/hri.json') as config_file:
            self.config = json.load(config_file)
        self.log.info("Config file parsed")

    # Initiate the logger with basic config
    def init_logger(self):
        logging.basicConfig()
        self.log = logging.getLogger('command')
        self.log.setLevel(logging.INFO)
        format = logging.Formatter("%(asctime)s - %(name)s - %(levelname)s - %(message)s")
        ch = logging.StreamHandler(sys.stdout)
        ch.setFormatter(format)
        self.log.addHandler(ch)


if __name__ == "__main__":
    CommandModule()
