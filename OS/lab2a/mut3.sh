#!/bin/sh
g++ -c mut3.c
g++ -o mut3 mut3.o -pthread
./mut3
