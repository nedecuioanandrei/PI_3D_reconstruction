#! /usr/bin/bash

test_case=$1

./a.out $(pwd)/test$1/left.bmp $(pwd)/test$1/right.bmp $(pwd)/test$1/params.json
xdg-open test_case_output.jpg

