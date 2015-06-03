CXX ?= g++
CXXFLAGS ?= -g -Wall -Wcpp -Wno-deprecated --std=c++11
LDFLAGS ?= -llapack -lANN

xinv: xinv.o
	$(CXX) $(LDFLAGS) -o xinv xinv.o

xinv.o: xinv.cpp direct_fit.h lagrange.h
	$(CXX) $(CXXFLAGS) -c xinv.cpp

clean:
	rm -f *.o *~ xinv
