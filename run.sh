#!/bin/sh

cd build && cmake .. && make && ./oran ../test.txt && sleep 1 && cd ..