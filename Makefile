CXX:= g++
CXXFLAGS:= -O3

all: knn

knn:
	$(CXX) $(CXXFLAGS) knn.cpp -o knn
