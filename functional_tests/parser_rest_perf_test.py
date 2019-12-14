import os
import asyncio
import requests
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

def rest_send_receive_verify(port, data, expected_response):
    uri = "http://localhost:" + str(port) + "/bin_to_json"
    for _ in range(2000):

        response = requests.get(url=uri,
            data=binary_data,
            headers={'Content-Type': 'application/octet-stream'})

        resp = json.loads(response.text)

        if not compare_json(resp, expected_response):
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

        start_perf_counter = time.perf_counter()
        start_process_time = time.process_time()
        test_successful = rest_send_receive_verify(parser_port, binary_data, json.loads(reference_json))

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
