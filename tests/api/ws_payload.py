import json
import base64

def composeJsonToBinRequest(id, data):
    return json.dumps({
        "type": "json_to_bin",
        "id": id,
        "data": json.dumps(data)
    }) + "\0"

def parseJsonToBinResponse(r):
    response = json.loads(r)

    if (response["type"] != "json_to_bin"):
        raise Exception("Incorrect response type")

    return {
        "id": response["id"],
        "data": base64.b64decode(response["data"])
    }

def composeBinToJsonRequest(id, data):
    return json.dumps({
        "type": "bin_to_json",
        "id": id,
        "data": base64.b64encode(data).decode('ascii')
    }) + "\0"

def parseBinToJsonResponse(response):
    r = json.loads(response)

    if (r["type"] != "bin_to_json"):
        raise Exception("Incorrect response type")

    return {
        "id": r["id"],
        "data": json.loads(r["data"])
    }
