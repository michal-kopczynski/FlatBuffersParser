# FlatBuffersParser
FlatBuffers Parser is socket based tool for parsing binary FlatBuffers data to JSON format. 

Usage
-----
* Initialize with the schema file by passing schema file as parameter.

        FlatBuffersParser [SCHEMA FILE] 
    
* Connect to parser's socket on port 12345.

* Send binary data to parser using socket. Receive response with parsed data.
    
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

    FlatBuffersParser$ ./build/test/UnitTests

#### Run functional tests

    FlatBuffersParser$ cd functional_tests
    functional_tests$ python parser_test.py
    
