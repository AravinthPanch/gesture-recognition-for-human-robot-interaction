__author__ = 'Aravinth Panchadcharam'
__email__ = "me@aravinth.info"
__date__ = '08/01/15'

import asyncore
import socket


class AsyncoreServerUDP(asyncore.dispatcher):
    def __init__(self):
        asyncore.dispatcher.__init__(self)

        # Bind to port 5005 on all interfaces
        self.create_socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.bind(('localhost', 50005))

    # Even though UDP is connectionless this is called when it binds to a port
    def handle_connect(self):
        print "Server Started..."

    # This is called everytime there is something to read
    def handle_read(self):
        data, addr = self.recvfrom(2048)
        print str(addr) + " >> " + data

    # This is called all the time and causes errors if you leave it out.
    def handle_write(self):
        pass


AsyncoreServerUDP()
asyncore.loop()