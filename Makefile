CXXFLAG=-Wall -std=c++11

hw1: mystring.o main.o
	g++ -o $@  $(CXXFLAG) $^

main.o: main.cpp
	g++ $(CXXFLAG) -c $<

mystring.o: mystring.cpp mystring.h
	g++ $(CXXFLAG) -c $<

clean:
	rm -f *.o
	rm -f hw1
