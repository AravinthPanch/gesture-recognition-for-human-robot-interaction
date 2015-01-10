__author__ = 'Aravinth Panchadcharam'
__email__ = "me@aravinth.info"
__date__ = '08/01/15'

import socket
import asyncore


class Start(asyncore.dispatcher):
    def __init__(self, logger):
        self.server_host = "localhost"
        self.server_port = 50005
        self.client_host = "localhost"
        self.client_port = 50006
        self.logger = logger

        asyncore.dispatcher.__init__(self)
        self.create_socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.bind((self.client_host, self.client_port))
        self.logger.info('UDP Client started at port:' + str(self.client_port))
        self.sendto("01", (self.server_host, self.server_port))
        self.logger.info('Connected to UDP Server at port:' + str(self.server_port))

    def handle_read(self):
        data, remote_endpoint = self.recvfrom(1024)
        self.logger.info(data)





