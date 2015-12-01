CXX ?= g++
CXXFLAGS ?= -g -Wall -Wcpp -Wno-deprecated -I../include -I../Interpolation --std=c++11
LDFLAGS ?= -larmadillo -lANN

xinv: xinv.o
	$(CXX) $(LDFLAGS) -o xinv xinv.o

xinv.o: xinv.cpp ../Interpolation/direct_fit.hpp direct_fit.hpp ../Interpolation/newton.hpp newton.hpp
	$(CXX) $(CXXFLAGS) -c xinv.cpp

clean:
	rm -f *.o *~ xinv
