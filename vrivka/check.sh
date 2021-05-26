#!/bin/bash

make
./a.out -n QWER=5000 > file2
echo -n QWER=5000 > file1
diff file1 file2
make clean
rm -rf file1 file2

#1:04:16