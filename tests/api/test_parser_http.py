import requests
import json
import pprint
from http import HTTPStatus

def test_parser_http(port):
    with open("reference.json", "r") as reference_json_file:
        reference = json.loads(reference_json_file.read())

        response_bin = requests.get(url='http://localhost:' + str(port) + '/json_to_bin',
                    data=json.dumps(reference),
                    headers={'Content-Type': 'application/json'})

        assert response_bin.status_code == HTTPStatus.OK

        response_json = requests.get(url='http://localhost:' + str(port) + '/bin_to_json',
                    data=response_bin.content,
                    headers={'Content-Type': 'application/octet-stream'})

        assert response_json.status_code == HTTPStatus.OK

        print("Response:")
        resp = json.loads(response_json.text)
        pprint.pprint(resp)

        assert resp == reference
