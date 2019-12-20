import os
import asyncio
import websockets
import json
import time
import pprint
import time

import test_helper as test_helper
import websockets_protocol as ws_protocol

import logging

async def websocket_send_receive_verify(port, buffer_json):
    uri = "ws://localhost:" + str(port)
    request_jtb = ws_protocol.JsonToBinRequest(1, buffer_json)

    async with websockets.connect(uri) as websocket:
        for _ in range(2000):
            await websocket.send(request_jtb.get())
            response = await websocket.recv()

            response_jtb = ws_protocol.JsonToBinResponse(response)
            request_btj = ws_protocol.BinToJsonRequest(1, response_jtb.data)

            await websocket.send(request_btj.get())
            response = await websocket.recv()

            response_btj = ws_protocol.BinToJsonResponse(response)
            if not test_helper.compare_json(response_btj.data, json.loads(buffer_json)):
                return False
        return True


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


        start_perf_counter = time.perf_counter()
        start_process_time = time.process_time()
        test_successful = asyncio.get_event_loop().run_until_complete(websocket_send_receive_verify(parser_port, reference_json))

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
