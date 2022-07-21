#~/user/bin/make -f
EXECUTABLE = bin/fid
SO_LIBRARY = bin/fid.so

CC         = gcc
CXX        = g++
CFLAGS     = -fPIC -Wno-enum-conversion -O3
CXXFLAGS_1 = -fPIC -std=c++14 -O3 -Wfatal-errors -Werror
CXXFLAGS_2 = -fPIC -std=c++17 -O3 -Wfatal-errors -Werror

LDFLAGS   = -pthread

SRC_ZLIB  = $(wildcard ziplib/Source/ZipLib/extlibs/zlib/*.c)
SRC_LZMA  = $(wildcard ziplib/Source/ZipLib/extlibs/lzma/unix/*.c)
SRC_BZIP2 = $(wildcard ziplib/Source/ZipLib/extlibs/bzip2/*.c)
SRC_ZIPLIB = \
		$(wildcard ziplib/Source/ZipLib/*.cpp) \
		$(wildcard ziplib/Source/ZipLib/detail/*.cpp)



SRC_FILEID = \
	fileid/fileid.cpp	


# Object files			
OBJS_1 = \
		$(SRC_ZIPLIB:.cpp=.o) \
		$(SRC_ZLIB:.c=.o) \
		$(SRC_LZMA:.c=.o) \
		$(SRC_BZIP2:.c=.o)

OBJS_2 = \
		$(SRC_FILEID:.cpp=.o) \


# Rules
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS_1)
	$(CXX) $(CXXFLAGS_1) $(LDFLAGS) $(CPP_FILES) -o $@ $^

$(EXECUTABLE): $(OBJS_2)
	$(CXX) $(CXXFLAGS_2) $(LDFLAGS) $(CPP_FILES) $^ -lstdc++fs -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(EXECUTABLE) $(SO_LIBRARY) $(OBJS)


BINDIR ?= ${PREFIX}/bin

install:
	@cp -p bin/fid ${PREFIX}/bin/fileid