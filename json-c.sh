#!/bin/bash

git clone https://github.com/json-c/json-c.git
cd json-c
sh autogen.sh
./configure
make
make install
make check
