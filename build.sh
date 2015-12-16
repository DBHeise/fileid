#!/bin/bash
gcc -o bzip2.o -c Externals/bzip2/bzlib.c
gcc -o lzma.o -c Externals/lzma/LzmaLib.c
gcc -o zlib.o -c Externals/zlib/zlib.h
gcc -lstdc++ -std=c++0x -Wfatal-errors -Werror zlib.o lzma.o bzip2.o fileid/fileid.cpp fileid/oless/pole.cpp -o fileid
