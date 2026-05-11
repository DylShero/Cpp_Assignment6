#Compiler and Flags
CXX      = g++
MPICXX   = mpicxx
CXXFLAGS = -Wall -Wextra -O2 -std=c++23
LDFLAGS  := -lstdc++exp #For print in windows

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
	$(CXX) $(CXXFLAGS) -o $(TARGETA) $(TARGETA).cc $(LDFLAGS)

#Assignment 6b 
$(TARGETB): $(TARGETB).cc
	$(CXX) $(CXXFLAGS) -o $(TARGETB) $(TARGETB).cc $(LDFLAGS) 

#Assignment 6c (MPI + Boost)
$(TARGETC): $(TARGETC).cpp
	$(MPICXX) $(CXXFLAGS) -o $(TARGETC) $(TARGETC).cc $(BOOST_LIBS) $(LDFLAGS)

#Clean
clean:
	rm -f $(TARGETA) $(TARGETB) $(TARGETC)


.PHONY: all clean