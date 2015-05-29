NVCC ?= nvcc
CXX ?= g++
CXXFLAGS ?= -g -Wall -Wcpp -Wno-deprecated --std=c++11
LDFLAGS ?= -llapack -lANN

xinv: xinv.o direct_fit.o 
	$(CXX) $(LDFLAGS) -o xinv direct_fit.o xinv.o

xinv.o: xinv.cpp direct_fit.h
	$(CXX) $(CXXFLAGS) -c xinv.cpp

direct_fit.o: direct_fit.cpp direct_fit.h
	$(CXX) $(CXXFLAGS) -c direct_fit.cpp

clean:
	rm -f *.o *~ xinv
