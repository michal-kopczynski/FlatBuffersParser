import os
import asyncio
import websockets
import json
import time
import pprint

import test_helper as test_helper
import websockets_protocol as ws_protocol

import logging

async def websocket_send_receive(port, req):
    uri = "ws://localhost:" + str(port)
    async with websockets.connect(uri) as websocket:

        await websocket.send(req)
        print("Request sent")

        return await websocket.recv()

if __name__ == '__main__':
    test_successful = False
    parser_port = 12345
    print("Parser client test started")

    #logging.basicConfig(level=logging.DEBUG) # WebSockets debug

    parser_runner = test_helper.ParserRunner()
    parser_runner.start_parser(parser_port)
    time.sleep(0.5)

    # Open raw file and send it's content to parser
    with open("reference.json", "r") as reference_json_file:
        reference_json = reference_json_file.read()

        request_jtb = ws_protocol.JsonToBinRequest(1, reference_json)
        response = asyncio.get_event_loop().run_until_complete(websocket_send_receive(parser_port, request_jtb.get()))

        print("JsonToBinResponse received")
        if response:
            response_jtb = ws_protocol.JsonToBinResponse(response)
            request_btj = ws_protocol.BinToJsonRequest(1, response_jtb.data)

            response = asyncio.get_event_loop().run_until_complete(websocket_send_receive(parser_port, request_btj.get()))

            print("BinToJsonResponse received")
            if response:
                print("Response:")

                response_btj = ws_protocol.BinToJsonResponse(response)
                pprint.pprint(response_btj.data)
                if test_helper.compare_json(response_btj.data, json.loads(reference_json)):
                    test_successful = True
            else:
                print("Response empty!")
        else:
            print("Response empty!")

    if test_successful:
        print("Parser client test PASSED")
    else:
        print("Parser client test FAILED")

    parser_runner.terminate_parser()

    print("Parser client test finished")
