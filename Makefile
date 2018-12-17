
CXX      = g++   
LIBGAB   = /home/gabriel/lib/libgab/

CXXFLAGS = -Wall -lm -O3 -lz -I${LIBGAB} -I${LIBGAB}/gzstream/ -c
LDFLAGS  = -lz


all: splitdgm 

splitdgm.o:	splitdgm.cpp
	${CXX} ${CXXFLAGS} splitdgm.cpp


splitdgm:	splitdgm.o ${LIBGAB}utils.o  
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS)

clean :
	rm -f splitdgm.o splitdgm

