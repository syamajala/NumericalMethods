CXX ?= g++
CXXFLAGS ?= -g -Wall -Wcpp -Wno-deprecated -I../include --std=c++11
LDFLAGS ?= -larmadillo -lANN

all: xinv enthalpy

xinv: xinv.o
	$(CXX) $(LDFLAGS) -o xinv xinv.o

xinv.o: xinv.cpp direct_fit.hpp lagrange.hpp neville.hpp divided_difference.hpp newton.hpp
	$(CXX) $(CXXFLAGS) -c xinv.cpp

enthalpy: enthalpy.o
	$(CXX) $(LDFLAGS) -o enthalpy enthalpy.o

enthalpy.o: enthalpy.cpp direct_fit.hpp
	$(CXX) $(CXXFLAGS) -c enthalpy.cpp

clean:
	rm -f *.o *~ xinv enthalpy
