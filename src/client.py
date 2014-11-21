import socket
import sys
import StringIO
SERVER_PORT = 7777
PEER_PORT = 8888
CHUNK_SIZE = 1024
CLIENT_IP = socket.gethostname()

if len(sys.argv) != 2:
    print "Incorrect usage. Correct usage = python client.py <server_address>"
    exit(1)
server_address = sys.argv[1]

def command_line_interface():
    print "P2P CLI Started"
    user_command_input = None
    user_command = None
    tracker_file_name = None

    while 1:
        user_command_input = raw_input()
        user_command_StringIO = StringIO.StringIO(user_command_input)
        


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print "Connecting to server..."
sock.connect((server_address, SERVER_PORT))
print "Connected"
data = raw_input("Enter client command:\n")
sent = sock.send(data)
if sent == 0:
    print "Did not send"

count = 0
try:
    while True:
        received = sock.recv(CHUNK_SIZE)
        if not received:
            break
        print received
        count += 1
except KeyboardInterrupt:
    print
sock.close()
print count

while 1:
    #infinite while loop to let the threads do the work