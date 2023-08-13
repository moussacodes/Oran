#!/bin/sh

cd build && cmake .. && make && ./Haifa ../test.txt && sleep 1 && cd ..