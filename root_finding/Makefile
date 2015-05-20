CXX ?= g++
CXXFLAGS ?= -g -Wall -Wcpp -Wno-deprecated -std=c++11
LDFLAGS ?=

link: link.o iterative.o
	$(CXX) $(LDFLAGS) -o link link.o iterative.o

link.o: link.cpp iterative.h
	$(CXX) $(CXXFLAGS) -c link.cpp

iterative.o: iterative.cpp iterative.h
	$(CXX) $(CXXFLAGS) -c iterative.cpp

clean:
	rm -f *.o *~ link
