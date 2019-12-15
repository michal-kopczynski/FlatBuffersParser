import os
import requests
import json
import base64
import time
import pprint
import json

import test_helper as test_helper


if __name__ == '__main__':
    test_successful = False
    parser_port = 12345
    print("Parser client test started")

    parser_runner = test_helper.ParserRunner()
    parser_runner.start_parser(parser_port)
    time.sleep(0.5)

    # Open raw file and send it's content to parser
    with open("raw.bin", "rb") as raw_binary_file, open("reference.json", "r") as reference_json_file:
        binary_data = raw_binary_file.read()
        reference_json = reference_json_file.read()

        response = requests.get(url='http://localhost:'  + str(parser_port) + '/bin_to_json',
                    data=binary_data,
                    headers={'Content-Type': 'application/octet-stream'})

        print("Response received")
        if response:
            print("Response:")
            resp = json.loads(response.text)
            print(resp)

            pprint.pprint(resp)
            if test_helper.compare_json(resp, json.loads(reference_json)):
                test_successful = True
        else:
            print("Response empty!")

    if test_successful:
        print("Parser client test PASSED")
    else:
        print("Parser client test FAILED")

    parser_runner.terminate_parser()

    print("Parser client test finished")
