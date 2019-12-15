import os
import asyncio
import websockets
import json
import base64
import time
import pprint
import json

import test_helper as test_helper


async def websocket_send_receive(port, req):
    uri = "ws://localhost:" + str(port)
    async with websockets.connect(uri) as websocket:

        await websocket.send(req)
        print("Request sent")

        return await websocket.recv()

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

        request = BinToJSONRequest(1, binary_data)

        response = asyncio.get_event_loop().run_until_complete(websocket_send_receive(parser_port, request.get()))

        print("Response received")
        if response:
            print("Response:")
            print(json.loads(response))

            resp = BinToJSONResponse(response)
            pprint.pprint(resp.data)
            if test_helper.compare_json(resp.data, json.loads(reference_json)):
                test_successful = True
        else:
            print("Response empty!")

    if test_successful:
        print("Parser client test PASSED")
    else:
        print("Parser client test FAILED")

    parser_runner.terminate_parser()

    print("Parser client test finished")
