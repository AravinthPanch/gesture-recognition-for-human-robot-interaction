__author__ = 'Aravinth Panchadcharam'
__email__ = "me@aravinth.info"
__date__ = '07/01/15'
__project__ = 'Gesture Recognition for Human-Robot Interaction'


import socket

HOST, PORT = "localhost", 50005
data = "01"

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("", 50006))

sock.sendto(data + "\n", (HOST, PORT))
print "Sent:     {}".format(data)

while True:
    data, addr = sock.recvfrom(1024)
    print "received message:", data