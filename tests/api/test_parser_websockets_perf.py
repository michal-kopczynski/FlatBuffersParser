import asyncio
import websockets
import json
import time

import ws_payload

import logging

async def websocket_send_receive_verify(port, buffer_json):
    url = "ws://localhost:" + str(port)
    request_jtb = ws_payload.composeJsonToBinRequest(1, buffer_json)

    async with websockets.connect(url) as websocket:
        for _ in range(2000):
            await websocket.send(request_jtb)
            response = await websocket.recv()

            response_jtb = ws_payload.parseJsonToBinResponse(response)
            request_btj = ws_payload.composeBinToJsonRequest(1, response_jtb["data"])

            await websocket.send(request_btj)
            response = await websocket.recv()

            response_btj = ws_payload.parseBinToJsonResponse(response)
            if not response_btj["data"] == json.loads(buffer_json):
                raise Exception("Request and response doesn't match")

def test_parser_websockets_perf(port):
    with open("reference.json", "r") as reference_json_file:
        reference_json = reference_json_file.read()

        start_perf_counter = time.perf_counter()
        start_process_time = time.process_time()
        asyncio.get_event_loop().run_until_complete(websocket_send_receive_verify(port, reference_json))

        end_perf_counter = time.perf_counter()
        end_process_time = time.process_time()
        print("Total time: {}".format(end_perf_counter - start_perf_counter))
        print("Process time: {}".format(end_process_time - start_process_time))
