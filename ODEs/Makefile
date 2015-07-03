CXX ?= g++
CXXFLAGS ?= -g -Wall -Wcpp -Wno-deprecated -std=c++11
LDFLAGS ?=

all: radiation

radiation: radiation.o
	$(CXX) $(LDFLAGS) -o radiation radiation.o

radiation.o: radiation.cpp explicit_euler.h
	$(CXX) $(CXXFLAGS) -c radiation.cpp

clean:
	rm -f *.o *~ radiation
