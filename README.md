# FlatBuffersParser
FlatBuffers Parser is a tool for parsing binary FlatBuffers data to JSON format. 

Usage
-----
* Initialize with the schema file by passing schema file name as a parameter. Specify listening port.

          FlatBuffersParser [OPTION...]

          -p, --port arg  Port to listen.
          -f, --file arg  Schema files.
          -v, --version   Print the version number and exit.
          -h, --help      Print help and exit.

    
* Connect to parser on selected port using WebSocket.

* Send binary data to parser in a WebSocket message. Receive response with parsed data.
    
Build
-----
#### Get the source

    $ git clone https://github.com/MichalKopczynski/FlatBuffersParser.git
    $ cd FlatBuffersParser

#### Build it

    FlatBuffersParser$ mkdir build
    FlatBuffersParser$ cd build
    build$ cmake ..
    build$ make
 
Test
-----
#### Run unit tests

    build$ make test

#### Run functional tests

    FlatBuffersParser$ cd functional_tests
    functional_tests$ python parser_test.py
    
