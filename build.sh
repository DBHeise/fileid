#!/bin/bash
gcc -c -fPIC Externals/bzip2/bzlib.c -o bzip2.o
gcc -shared -o libbzip2.so bzip2.o
#
gcc -c -fPIC Externals/lzma/LzmaLib.c -o lzma.o
gcc -shared -o liblzma.so lzma.o
#
gcc -c -fPIC Externals/zlib/zutil.c -o zlib.o
gcc -shared -fPIC -o libzlib.so zlib.o
#
#gcc -static -lm -lstdc++ -std=c++0x -Wfatal-errors -Werror -L /usr/include -L /home/dxh87/fileid -lzlib -llzma -lbzip2 fileid/fileid.cpp fileid/oless/pole.cpp -o fid
g++ -lm -lstdc++ -std=c++11 -Wfatal-errors -Werror -I /home/dxh87/fileid/zip -L /usr/include -L /home/dxh87/fileid fileid/fileid.cpp fileid/oless/pole.cpp fileid/zip/ZipLib/detail/EndOfCentralDirectoryBlock.cpp fileid/zip/ZipLib/detail/ZipCentralDirectoryFileHeader.cpp fileid/zip/ZipLib/detail/ZipGenericExtraField.cpp fileid/zip/ZipLib/detail/ZipLocalFileHeader.cpp fileid/zip/ZipLib/ZipArchive.cpp fileid/zip/ZipLib/ZipArchiveEntry.cpp fileid/zip/ZipLib/ZipFile.cpp -o fid

