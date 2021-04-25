CC=g++
CXXFLAGS=-g -Wall -Wextra -Wshadow -O2
CXXSTANDARD=-std=c++11


all: virtual_func_tests

virtual_func_tests: virtual_func_tests.o
	$(CC) -o virtual_func_tests virtual_func_tests.o $(CXXFLAGS) $(CXXSTANDARD)

virtual_func_tests.o: virtual_func_tests.cpp
	$(CC) -c -o virtual_func_tests.o virtual_func_tests.cpp $(CXXFLAGS) $(CXXSTANDARD)

