CXX ?= g++
CXXFLAGS ?= -g -Wall -Wcpp -Wno-deprecated --std=c++11
LDFLAGS ?= -llapack -lANN

xinv: xinv.o direct_fit.o fit.o lagrange.o
	$(CXX) $(LDFLAGS) -o xinv fit.o direct_fit.o lagrange.o xinv.o

xinv.o: xinv.cpp direct_fit.h lagrange.h
	$(CXX) $(CXXFLAGS) -c xinv.cpp

direct_fit.o: direct_fit.cpp direct_fit.h fit.h
	$(CXX) $(CXXFLAGS) -c direct_fit.cpp

lagrange.o: lagrange.cpp lagrange.h fit.h
	$(CXX) $(CXXFLAGS) -c lagrange.cpp

fit.o: fit.cpp fit.h
	$(CXX) $(CXXFLAGS) -c fit.cpp

clean:
	rm -f *.o *~ xinv
