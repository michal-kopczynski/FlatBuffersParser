import os
import asyncio
import requests
import json
import base64
import time
import pprint
import json
import time

import logging

import test_helper as test_helper


def rest_send_receive_verify(port, reference_json, expected_response):
    uri_json_to_bin = "http://localhost:" + str(port) + "/json_to_bin"
    uri_bin_to_json = "http://localhost:" + str(port) + "/bin_to_json"
    for _ in range(2000):
        response_bin = requests.get(url=uri_json_to_bin,
                    data=reference_json,
                    headers={'Content-Type': 'application/json'})

        response_json = requests.get(url=uri_bin_to_json,
                    data=response_bin,
                    headers={'Content-Type': 'application/octet-stream'})

        resp = json.loads(response_json.text)

        if not test_helper.compare_json(resp, expected_response):
            return False
    return True

if __name__ == '__main__':
    test_successful = False
    parser_port = 12345
    print("Parser client test started")

    # logging.basicConfig(level=logging.DEBUG)

    parser_runner = test_helper.ParserRunner()
    parser_runner.start_parser(parser_port)
    time.sleep(0.5)

    # Open raw file and send it's content to parser
    with open("reference.json", "r") as reference_json_file:
        reference_json = reference_json_file.read()

        start_perf_counter = time.perf_counter()
        start_process_time = time.process_time()
        test_successful = rest_send_receive_verify(parser_port, reference_json, json.loads(reference_json))

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
