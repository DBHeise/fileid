#~/user/bin/make -f
EXECUTABLE = bin/linux/fid
EXECUTABLE_UNIT = bin/linux/unit_tests

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

SRC_UNIT = \
	test/main.cpp

# Object files			
OBJS_1 = \
		$(SRC_ZIPLIB:.cpp=.o) \
		$(SRC_ZLIB:.c=.o) \
		$(SRC_LZMA:.c=.o) \
		$(SRC_BZIP2:.c=.o)

OBJS_2 = \
		$(SRC_FILEID:.cpp=.o) \

OBJS_UNIT = \
		$(SRC_UNIT:.cpp=.o) \

# Rules
all: $(EXECUTABLE) $(EXECUTABLE_UNIT)

$(EXECUTABLE): $(OBJS_1)
	$(CXX) $(CXXFLAGS_1) $(LDFLAGS) $(CPP_FILES) -o $@ $^

$(EXECUTABLE): $(OBJS_2)
	$(CXX) $(CXXFLAGS_2) $(LDFLAGS) $(CPP_FILES) $^ -lstdc++fs -o $@

$(EXECUTABLE_UNIT): $(OBJS_UNIT)
	$(CXX) $(CXXFLAGS_2) $(LDFLAGS) $(CPP_FILES) $^ -lstdc++fs -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(EXECUTABLE) $(EXECUTABLE_UNIT) $(SO_LIBRARY) $(OBJS_1) $(OBJS_2) $(OBJS_UNIT)


BINDIR ?= ${PREFIX}/bin

install:
	@cp -p bin/fid ${PREFIX}/bin/fileid