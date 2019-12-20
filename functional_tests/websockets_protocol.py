import json
import base64

class JsonToBinRequest:
    def __init__(self, id, json):
        self.type = "json_to_bin"
        self.id = id
        self.data = json

    def get(self):
        return json.dumps(self.__dict__) + "\0"

class JsonToBinResponse:
    def __init__(self, raw):
        response = json.loads(raw)
        self.type = response["type"]
        self.id = response["id"]
        self.data = base64.b64decode(response["data"])

class BinToJsonRequest:
    def __init__(self, id, binary_data):
        self.type = "bin_to_json"
        self.id = id
        self.data = base64.b64encode(binary_data).decode('ascii')

    def get(self):
        return json.dumps(self.__dict__) + "\0"

class BinToJsonResponse:
    def __init__(self, raw):
        response = json.loads(raw)
        self.type = response["type"]
        self.id = response["id"]
        self.data = json.loads(response["data"])