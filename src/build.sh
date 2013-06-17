#!/bin/bash

cd "$(dirname "$0")"

for i in `ls -d */`
do
    cd $i
    make
    make install
    cd ..
done

