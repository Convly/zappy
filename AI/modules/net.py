import sys
import socket
import select
import log
class Net:
    def __init__(self, host, port):
        self._host = host
        self._port = port
        self._cmd = ''
        self._error = None
    
    def connect(self):
        # Creating the socket
        try:
            self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self._socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
        except:
            log.Fail('Failed to create to the socket.', underline=True)
            sys.exit(84)
        # Resolve real IP by domain name
        try:
            self._remoteIP = socket.gethostbyname(self._host)
            log.Log('Associating ' + self._host + ' to ' + self._remoteIP, color='Blue')
        except:
            log.Fail('Error while resolving host', underline=True)
            sys.exit(84)
        # Connect to the remoteIp with a specific port
        try:
            self._socket.connect((self._remoteIP, self._port))
            log.Log('Connected to ' + self._remoteIP + ':' + str(self._port) + ' [' + self._host+ ']', color='Blue')
        except:
            log.Fail('Cannot connect to ' + self._remoteIP + ':' + str(self._port) + ' [' + self._host+ ']', underline=True)            
            sys.exit(84)

    def send(self, buffer):
        r, w, x = select.select([], [self._socket], [])
        if self._socket in w:
            try:
                self._socket.sendall(buffer.encode('ascii'))
                return (1)
            except socket.error:
                self._error = 'Send failed. You have been disconnect from ' + self._host
                return (0)
    
    def receive(self):
        payload = ''
        while not '\n' in payload:
            payload += self._socket.recv(4096).decode('utf-8')
        self._cmd = payload
        return self._cmd