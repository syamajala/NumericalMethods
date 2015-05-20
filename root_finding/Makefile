CXX ?= g++
CXXFLAGS ?= -g -Wall -Wcpp -Wno-deprecated -std=c++11 -I../lib/
LDFLAGS ?=

link: link.o iterative.o newton.o
	$(CXX) $(LDFLAGS) -o link iterative.o newton.o link.o

link.o: link.cpp iterative.h newton.h
	$(CXX) $(CXXFLAGS) -c link.cpp

newton.o: newton.cpp newton.h
	$(CXX) $(CXXFLAGS) -c newton.cpp

iterative.o: iterative.cpp iterative.h
	$(CXX) $(CXXFLAGS) -c iterative.cpp

clean:
	rm -f *.o *~ link
