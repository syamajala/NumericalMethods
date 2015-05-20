CXX ?= g++
CXXFLAGS ?= -g -Wall -Wcpp -Wno-deprecated -std=c++11 -I../lib
LDFLAGS ?= 

all: radiation

radiation: radiation.o explicit_euler.o
	$(CXX) $(LDFLAGS) -o radiation radiation.o explicit_euler.o

radiation.o: radiation.cpp explicit_euler.h
	$(CXX) $(CXXFLAGS) -c radiation.cpp

explicit_euler.o: explicit_euler.cpp explicit_euler.h
	$(CXX) $(CXXFLAGS) -c explicit_euler.cpp

clean:
	rm -f *.o *~ radiation
