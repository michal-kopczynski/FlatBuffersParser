import os
import socket
import signal
import subprocess
import time
import pprint
import json

class ParserRunner:
    def start_parser(self):
        print("Starting parser")
        self.parser_subprocess = subprocess.Popen([os.path.join('..','bin','FlatBuffersParser'),
                                                   'monster.fbs',
                                                   ], stdout=subprocess.PIPE,
                               shell=False, preexec_fn=os.setsid)
        print("Parser started")

    def terminate_parser(self):
        os.killpg(os.getpgid(self.parser_subprocess.pid), signal.SIGTERM)
        print("Parser terminated")

def compare_json(a , b):
    return a == b

if __name__ == '__main__':
    test_successful = False
    parser_port = 12345
    print("Parser client test started")

    parser_runner = ParserRunner()
    parser_runner.start_parser()

    #connect to parser
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        s.connect(('localhost', parser_port))
        print("Connected to parser")
    except:
        print("Connection error!")
    time.sleep(0.1)

    #open raw file and send it's content to parser
    with open("raw.bin", "rb") as raw_binary_file:
        binary_data = raw_binary_file.read()
        s.send(binary_data)
        print("Request sent")

    print("Waiting for response")
    response = s.recv(16000)

    print("Response received")
    if response:
        print("Response:")
        pprint.pprint(json.loads(response))

        with open("reference.json", "r") as reference_json_file:
            reference_json = reference_json_file.read()
            if compare_json(json.loads(response), json.loads(reference_json)):
                test_successful = True
    else:
        print("Response empty!")

    if test_successful:
        print("Parser client test PASSED")
    else:
        print("Parser client test FAILED")

    s.close()
    parser_runner.terminate_parser()

    print("Parser client test finished")


