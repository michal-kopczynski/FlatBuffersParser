import os
import asyncio
import websockets
import json
import base64
import signal
import subprocess
import time
import pprint
import json
import time

import logging

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

class BinToJSONRequest:
    def __init__(self, id, binary_data):
        self.type = "bin_to_json"
        self.id = id
        self.data = base64.b64encode(binary_data).decode('ascii')

    def get(self):
        return json.dumps(self.__dict__) + "\0"

class BinToJSONResponse:
    def __init__(self, raw):
        response = json.loads(raw)
        self.type = response["type"]
        self.id = response["id"]
        self.data = json.loads(response["data"])

async def websocket_send_receive_verify(port, req, expected_response):
    uri = "ws://localhost:" + str(port)
    async with websockets.connect(uri) as websocket:
        for _ in range(2000):
            await websocket.send(req)

            response = await websocket.recv()
            resp = BinToJSONResponse(response)
            if not compare_json(resp.data, expected_response):
                return False
        return True


if __name__ == '__main__':
    test_successful = False
    parser_port = 12345
    print("Parser client test started")

    # logging.basicConfig(level=logging.DEBUG)

    parser_runner = ParserRunner()
    parser_runner.start_parser(parser_port)
    time.sleep(0.5)

    # Open raw file and send it's content to parser
    with open("raw.bin", "rb") as raw_binary_file, open("reference.json", "r") as reference_json_file:
        binary_data = raw_binary_file.read()
        reference_json = reference_json_file.read()

        request = BinToJSONRequest(1, binary_data)

        start_perf_counter = time.perf_counter()
        start_process_time = time.process_time()
        test_successful = asyncio.get_event_loop().run_until_complete(websocket_send_receive_verify(parser_port, request.get(), json.loads(reference_json)))

        end_perf_counter = time.perf_counter()
        end_process_time = time.process_time()
        print("Total time: {}".format(end_perf_counter - start_perf_counter))
        print("Process time: {}".format(end_process_time - start_process_time))

    if test_successful:
        print("Parser client test PASSED")
    else:
        print("Parser client test FAILED")

    parser_runner.terminate_parser()

    print("Parser client test finished")
