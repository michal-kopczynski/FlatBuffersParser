import os
import asyncio
import requests
import json
import time
import logging
from http import HTTPStatus

def rest_send_receive_verify(port, reference):
    url_json_to_bin = "http://localhost:" + str(port) + "/json_to_bin"
    url_bin_to_json = "http://localhost:" + str(port) + "/bin_to_json"
    reference_data=json.dumps(reference)
    for _ in range(2000):
        response_bin = requests.get(url=url_json_to_bin,
                    data=reference_data,
                    headers={'Content-Type': 'application/json'})

        if not response_bin.status_code == HTTPStatus.OK:
            raise Exception("Expected status code 200, but got {}".format(response_bin.status_code))

        response_json = requests.get(url=url_bin_to_json,
                    data=response_bin.content,
                    headers={'Content-Type': 'application/octet-stream'})

        if not response_json.status_code == HTTPStatus.OK:
            raise Exception("Expected status code 200, but got {}".format(response_json.status_code))

        if not json.loads(response_json.text) == reference:
            raise Exception("Request and response doesn't match")

def test_parser_http_perf(port):
    with open("reference.json", "r") as reference_json_file:
        reference = json.loads(reference_json_file.read())

        start_perf_counter = time.perf_counter()
        start_process_time = time.process_time()
        rest_send_receive_verify(port, reference)

        end_perf_counter = time.perf_counter()
        end_process_time = time.process_time()
        print("Total time: {}".format(end_perf_counter - start_perf_counter))
        print("Process time: {}".format(end_process_time - start_process_time))

