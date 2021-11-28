#!/bin/bash
python3 csc_convert.py matrix1.txt
python3 csc_convert.py matrix2.txt
python3 csc_convert.py matrix3.txt
# make CSCSeq
# make CSRSeq
# make CSROpenMP
# make CSCOpenMP
make all
./CSRseq matrix1.txt 1
./CSRseq matrix2.txt 1
./CSRseq matrix3.txt 1

./CSROpenMP matrix1.txt 2
./CSROpenMP matrix2.txt 2
./CSROpenMP matrix3.txt 2
./CSROpenMP matrix1.txt 4
./CSROpenMP matrix2.txt 4
./CSROpenMP matrix3.txt 4
./CSROpenMP matrix1.txt 8
./CSROpenMP matrix2.txt 8
./CSROpenMP matrix3.txt 8

./CSROpenMP matrix1.txt 16
./CSROpenMP matrix2.txt 16
./CSROpenMP matrix3.txt 16
./CSROpenMP matrix1.txt 32
./CSROpenMP matrix2.txt 32
./CSROpenMP matrix3.txt 32
./CSCseq matrix1.txt 1
./CSCseq matrix2.txt 1
./CSCseq matrix3.txt 1
./CSCOpenMP matrix1.txt 2
./CSCOpenMP matrix2.txt 2
./CSCOpenMP matrix3.txt 2
./CSCOpenMP matrix1.txt 4
./CSCOpenMP matrix2.txt 4
./CSCOpenMP matrix3.txt 4
./CSCOpenMP matrix1.txt 8
./CSCOpenMP matrix2.txt 8
./CSCOpenMP matrix3.txt 8
./CSCOpenMP matrix1.txt 16
./CSCOpenMP matrix2.txt 16
./CSCOpenMP matrix3.txt 16
./CSCOpenMP matrix1.txt 32
./CSCOpenMP matrix2.txt 32
./CSCOpenMP matrix3.txt 32