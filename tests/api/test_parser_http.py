import requests
import json
import pprint

def test_parser_http(port):
    with open("reference.json", "r") as reference_json_file:
        reference_json = reference_json_file.read()

        response_bin = requests.get(url='http://localhost:' + str(port) + '/json_to_bin',
                    data=reference_json,
                    headers={'Content-Type': 'application/json'})

        response_json = requests.get(url='http://localhost:' + str(port) + '/bin_to_json',
                    data=response_bin,
                    headers={'Content-Type': 'application/octet-stream'})

        assert response_json
        print("Response:")
        resp = json.loads(response_json.text)
        pprint.pprint(resp)

        assert resp == json.loads(reference_json)
