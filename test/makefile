all: tests

# If you have googletest in non-standard paths, add them here
#GTESTPATH=
CXXFLAGS=-I${GTESTPATH}/include
LDFLAGS=-L${GTESTPATH}/lib

tests: ../*.cpp ../*.h test.cpp
	gcc -o tests test.cpp ../LUrlParser.cpp $(CXXFLAGS) -std=c++11 -lstdc++ $(LDFLAGS) -lgtest

clean:
	rm -f ./tests
