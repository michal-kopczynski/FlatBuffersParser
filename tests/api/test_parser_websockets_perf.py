import asyncio
import websockets
import json
import time

import ws_payload

import logging

async def websocket_send_receive_verify(port, reference):
    url = "ws://localhost:" + str(port)
    request_jtb = ws_payload.composeJsonToBinRequest(1, reference)

    async with websockets.connect(url) as websocket:
        for _ in range(2000):
            await websocket.send(request_jtb)
            response_jtb = ws_payload.parseJsonToBinResponse(await websocket.recv())

            request_btj = ws_payload.composeBinToJsonRequest(1, response_jtb["data"])
            await websocket.send(request_btj)
            response_btj = ws_payload.parseBinToJsonResponse(await websocket.recv())

            if not response_btj["data"] == reference:
                raise Exception("Request and response doesn't match")

def test_parser_websockets_perf(port):
    with open("reference.json", "r") as reference_json_file:
        reference = json.loads(reference_json_file.read())

        start_perf_counter = time.perf_counter()
        start_process_time = time.process_time()
        asyncio.get_event_loop().run_until_complete(websocket_send_receive_verify(port, reference))

        end_perf_counter = time.perf_counter()
        end_process_time = time.process_time()
        print("Total time: {}".format(end_perf_counter - start_perf_counter))
        print("Process time: {}".format(end_process_time - start_process_time))
