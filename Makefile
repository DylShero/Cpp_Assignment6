#Compiler and Flags
CXX      = g++
MPICXX   = mpicxx
CXXFLAGS = -Wall -Wextra -O2 -std=c++23
LDFLAGS  := #-lstdc++exp #For print in windows

#Libraries for Assignment 6c
BOOST_ROOT = /home/support/rl8/spack/1.1.1/opt/spack/linux-x86_64_v3/boost-1.89.0-66rwt5vi6urjsapzm2awqxbeuwnrexld
BOOST_INC  = -I$(BOOST_ROOT)/include
BOOST_LDIR = -L$(BOOST_ROOT)/lib
BOOST_LIBS = -lboost_mpi-mt-d-x64 -lboost_serialization-mt-d-x64

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
$(TARGETB): $(TARGETB).cc point.cc ConvexHull.cc
	$(CXX) $(CXXFLAGS) -o $(TARGETB) $(TARGETB).cc point.cc ConvexHull.cc $(LDFLAGS)

#Assignment 6c
$(TARGETC): $(TARGETC).cc
	$(MPICXX) $(CXXFLAGS) $(BOOST_INC) -o $(TARGETC) $(TARGETC).cc $(BOOST_LDIR) $(BOOST_LIBS) $(LDFLAGS)

#Clean
clean:
	rm -f $(TARGETA) $(TARGETB) $(TARGETC)


.PHONY: all clean