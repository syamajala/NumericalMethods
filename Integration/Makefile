CXX ?= g++
CXXFLAGS ?= -g -Wall -Wcpp -Wno-deprecated -I../include -I../Interpolation --std=c++11
LDFLAGS ?= -llapack -lANN

xinv: xinv.o
	$(CXX) $(LDFLAGS) -o xinv xinv.o

xinv.o: xinv.cpp ../Interpolation/direct_fit.h
	$(CXX) $(CXXFLAGS) -c xinv.cpp

clean:
	rm -f *.o *~ xinv
