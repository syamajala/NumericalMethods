CXX ?= g++
CXXFLAGS ?= -g -Wall -Wcpp -Wno-deprecated -std=c++11 -I../include/
LDFLAGS ?= -larmadillo

all: link link_systems

link_systems: link_systems.o
	$(CXX) $(LDFLAGS) -o link_systems link_systems.o

link_systems.o: link_systems.cpp newton_systems.h
	$(CXX) $(CXXFLAGS) -c link_systems.cpp

link: link.o
	$(CXX) $(LDFLAGS) -o link link.o

link.o: link.cpp iterative.h newton.h
	$(CXX) $(CXXFLAGS) -c link.cpp

clean:
	rm -f *.o *~ link link_systems
