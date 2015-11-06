CXX=g++
CXXFLAG=-Wall -std=c++11

.PHONY: hw1 test

hw1: MAKEFLAG=$(CXXFLAG)
test: MAKEFLAG= -DSELF_TEST $(CXXFLAG) 

hw1: clean editor
test: clean editor

# exectable
editor: mystring.o main.o
	$(CXX) -o $@  $(MAKEFLAG) $^

main.o: main.cpp
	$(CXX) $(MAKEFLAG) -c $<

mystring.o: mystring.cpp mystring.h
	$(CXX) $(MAKEFLAG) -c $<

clean: 
	rm -f *.o rm -f editor
