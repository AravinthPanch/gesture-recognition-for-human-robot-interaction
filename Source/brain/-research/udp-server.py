__author__ = 'Aravinth Panchadcharam'
__email__ = "me@aravinth.info"
__date__ = '07/01/15'

import SocketServer


class MyUDPHandler(SocketServer.BaseRequestHandler):
    """
    This class works similar to the TCP handler class, except that
    self.request consists of a pair of data and client socket, and since
    there is no connection the client address must be given explicitly
    when sending data back via sendto().
    """

    def handle(self):
        data = self.request[0].strip()
        socket = self.request[1]
        print "{} wrote:".format(self.client_address[0])
        js = '{"type":"0"}'
        socket.sendto(js, self.client_address)


if __name__ == "__main__":
    HOST, PORT = "localhost", 50005
    server = SocketServer.UDPServer((HOST, PORT), MyUDPHandler)
    server.serve_forever()
    print "hoola"