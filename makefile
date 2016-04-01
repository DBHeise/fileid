#~/user/bin/make -f
EXECUTABLE = fid
SO_LIBRARY = fid.so

CC = gcc
CXX = g++
CFLAGS    = -fPIC -Wno-enum-conversion -O3
CXXFLAGS  = -fPIC -std=c++11 -O3

SRC_ZLIB = $(wildcard Externals/zlib/*.c)
SRC_LZMA = $(wildcard Externals/lzma/unix/*.c)
SRC_BZIP2 = $(wildcard Externals/bzip2/*.c)

CPP_FILES=fileid/fileid.cpp fileid/oless/pole.cpp


# Object files			
OBJS = \
		$(SRC:.cpp=.o)	   \
		$(SRC_ZLIB:.c=.o)  \
		$(SRC_LZMA:.c=.o)  \
		$(SRC_BZIP2:.c=.o)

# Rules
all: $(EXECUTABLE) $(SO_LIBRARY)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(CPP_FILES) -o $@ $^

$(SO_LIBRARY): $(OBJS)
	$(CXX) $(LDFLAGS) -shared -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf `find Source -name '*.o'` ziplib.tar.gz Bin/*.zip Bin/out* $(EXECUTABLE) $(SO_LIBRARY)

#fid:
#	g++ -Wfatal-errors -Werror -std=c++11 -lm -lstdc++ -llzma -lbz2 -lz $(CPP_FILES) -o $@


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 