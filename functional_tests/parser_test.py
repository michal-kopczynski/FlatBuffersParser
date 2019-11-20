import os
import asyncio
import websockets
import signal
import subprocess
import time
import pprint
import json

import binascii


class ParserRunner:
    def start_parser(self, port):
        print("Starting parser")
        self.parser_subprocess = subprocess.Popen([os.path.join('..','bin','FlatBuffersParser'),
                                                   '--file=monster.fbs', '--port=' + str(port)
                                                   ], stdout=subprocess.PIPE,
                               shell=False, preexec_fn=os.setsid)
        print("Parser started. Listening on port: {}".format(port))

    def terminate_parser(self):
        os.killpg(os.getpgid(self.parser_subprocess.pid), signal.SIGTERM)
        print("Parser terminated")

def compare_json(a , b):
    return a == b

async def send_receive(port, req):
    uri = "ws://localhost:" + str(port)
    async with websockets.connect(uri) as websocket:

        await websocket.send(req)
        print("Request sent")

        return await websocket.recv()

if __name__ == '__main__':
    test_successful = False
    parser_port = 12345
    print("Parser client test started")

    parser_runner = ParserRunner()
    parser_runner.start_parser(parser_port)
    time.sleep(0.5)

    # Open raw file and send it's content to parser
    with open("raw.bin", "rb") as raw_binary_file:
        binary_data = raw_binary_file.read()

        response = asyncio.get_event_loop().run_until_complete(send_receive(parser_port, binary_data))

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

    parser_runner.terminate_parser()

    print("Parser client test finished")
