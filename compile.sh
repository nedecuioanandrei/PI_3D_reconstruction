#! /usr/bin/bash
set -e 
source=$1
g++ -std=c++17 -Wshadow -Wall -o a.out $source -O2 -Wno-unused-result -DLOCAL -ljsoncpp `pkg-config --cflags --libs opencv4`
	
