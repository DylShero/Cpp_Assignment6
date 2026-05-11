#Compiler and Flags
CXX      = g++
MPICXX   = mpicxx
CXXFLAGS = -Wall -Wextra -O2 -std=c++17

#Libraries for Assignment 6c
BOOST_LIBS = -lboost_mpi -lboost_serialization

#Target Names
TARGETA = assignment6a
TARGETB = assignment6b
TARGETC = assignment6c

#Default 
all: $(TARGETA) $(TARGETB) $(TARGETC)

#Assignment 6a 
$(TARGETA): $(TARGETA).cc
	$(CXX) $(CXXFLAGS) -o $(TARGETA) $(TARGETA).cc

#Assignment 6b 
$(TARGETB): $(TARGETB).cc
	$(CXX) $(CXXFLAGS) -o $(TARGETB) $(TARGETB).cc

#Assignment 6c (MPI + Boost)
$(TARGETC): $(TARGETC).cpp
	$(MPICXX) $(CXXFLAGS) -o $(TARGETC) $(TARGETC).cc $(BOOST_LIBS)

#Clean
clean:
	rm -f $(TARGETA) $(TARGETB) $(TARGETC)


.PHONY: all clean