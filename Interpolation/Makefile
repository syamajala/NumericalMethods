CXX ?= g++
CXXFLAGS ?= -g -Wall -Wcpp -Wno-deprecated -I../include --std=c++11
LDFLAGS ?= -llapack -lANN

xinv: xinv.o
	$(CXX) $(LDFLAGS) -o xinv xinv.o

xinv.o: xinv.cpp direct_fit.h lagrange.h neville.h divided_difference.h newton.h
	$(CXX) $(CXXFLAGS) -c xinv.cpp

clean:
	rm -f *.o *~ xinv
