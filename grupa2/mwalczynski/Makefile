CXX = g++
CC = g++
CXXFLAGS= -Wall -c -O3 --std=c++11 -lGL -lglut
LDFLAGS = -Wall -O3 --std=c++11 -lGL -lglut
ALL = main
HEADERS = vector.hpp point.hpp definitions.hpp

all: $(ALL)

$(ALL): %: %.o main.o vector.o point.o
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp %.c $(HEADERS) Makefile
	$(CXX) $(CXXFLAGS) $@ $<

clean:
	rm -f *.o $(ALL)
