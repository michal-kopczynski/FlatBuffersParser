import os
import asyncio
import requests
import json
import time
import logging

def rest_send_receive_verify(port, reference_json, expected_response):
    url_json_to_bin = "http://localhost:" + str(port) + "/json_to_bin"
    url_bin_to_json = "http://localhost:" + str(port) + "/bin_to_json"
    for _ in range(2000):
        response_bin = requests.get(url=url_json_to_bin,
                    data=reference_json,
                    headers={'Content-Type': 'application/json'})

        response_json = requests.get(url=url_bin_to_json,
                    data=response_bin,
                    headers={'Content-Type': 'application/octet-stream'})

        resp = json.loads(response_json.text)

        if not resp == expected_response:
            raise Exception("Request and response doesn't match")

def test_parser_http_perf(port):
    with open("reference.json", "r") as reference_json_file:
        reference_json = reference_json_file.read()

        start_perf_counter = time.perf_counter()
        start_process_time = time.process_time()
        rest_send_receive_verify(port, reference_json, json.loads(reference_json))

        end_perf_counter = time.perf_counter()
        end_process_time = time.process_time()
        print("Total time: {}".format(end_perf_counter - start_perf_counter))
        print("Process time: {}".format(end_process_time - start_process_time))

