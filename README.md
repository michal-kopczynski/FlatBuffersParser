# FlatBuffersParser
FlatBuffers Parser is a tool for converting FlatBuffers between binary and JSON format. Supports HTTP and WebSockets protocols.

## Usage

### Initialization
Initialize with the schema files by passing schema file names as a parameter. Specify listening port.

          FlatBuffersParser [OPTION...]

          -p, --port arg  Port to listen.
          -f, --file arg  Schema files.
          -v, --version   Print the version number and exit.
          -h, --help      Print help and exit.

### HTTP

Send HTTP GET request with binary/JSON data to specific URI:
* Binary to JSON: /bin_to_json (MIME type: application/octet-stream)
* JSON to binary: /json_to_bin (MIME type: application/json)

### WebSockets

Connect to parser on selected port using WebSockets.
Send JSON message contatining type of request, id and data to be parsed.
* Binary to JSON:
    {
    "type": "bin_to_json"
    "id": <ID>, 
    "data": <base64 encoded binary>
    }
* JSON to binary:
    {
    "type": "json_to_bin",
    "id": <ID>, 
    "data": <JSON FlatBuffer>
    }

## Docker deployment

### Configure
    Set arguments (port and file) in docker-compose.yaml

### Build image
    docker-compose build

### Run
    docker-compose up fb-parser

### Run tests
    docker-compose up 

## Manual build

### Get the source

    $ git clone https://github.com/michal-kopczynski/FlatBuffersParser.git
    $ cd FlatBuffersParser

### Dependencies

Most dependencies (FlatBuffers, cxxopts, RapidJSON) are fetched automatically by cmake. Currently only RESTinio requires manual installation (i.e. using vcpkg).

### Build

    FlatBuffersParser$ mkdir build
    FlatBuffersParser$ cd build
    build$ cmake ..
    build$ make
 
## Test

### Run unit tests

    build$ make test

### Run API tests

#### Install test dependencies
    tests/api$ pip install -r requirements.txt

#### Run tests
    tests/api$ pytest --port=<PORT_NUMBER>

