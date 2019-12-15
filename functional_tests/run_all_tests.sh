#!/bin/bash

execute_test () {
    echo RUNNING TEST: $1
    python $1.py
    echo ""
}

execute_test parser_websockets_test
execute_test parser_websockets_perf_test
execute_test parser_rest_test
execute_test parser_rest_perf_test