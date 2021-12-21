import asyncio
import websockets
import json
import pprint

import ws_payload

import logging

async def websocket_send_receive(port, payload):
    url = "ws://localhost:" + str(port)
    async with websockets.connect(url) as websocket:

        await websocket.send(payload)
        return await websocket.recv()

def test_parser_websockets(port):
    with open("reference.json", "r") as reference_json_file:
        reference_json = reference_json_file.read()

        request_jtb = ws_payload.composeJsonToBinRequest(1, reference_json)
        response = asyncio.get_event_loop().run_until_complete(websocket_send_receive(port, request_jtb))
        assert response
        response_jtb = ws_payload.parseJsonToBinResponse(response)

        request_btj = ws_payload.composeBinToJsonRequest(1, response_jtb["data"])
        response = asyncio.get_event_loop().run_until_complete(websocket_send_receive(port, request_btj))
        assert response
        response_btj = ws_payload.parseBinToJsonResponse(response)
        pprint.pprint(response_btj["data"])

        assert response_btj["data"] == json.loads(reference_json)
