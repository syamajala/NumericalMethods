CXX ?= g++
CXXFLAGS ?= -g -Wall -Wcpp -Wno-deprecated -std=c++11 -I../lib/
LDFLAGS ?=

link: link.o
	$(CXX) $(LDFLAGS) -o link link.o

link.o: link.cpp iterative.h newton.h
	$(CXX) $(CXXFLAGS) -c link.cpp

clean:
	rm -f *.o *~ link
