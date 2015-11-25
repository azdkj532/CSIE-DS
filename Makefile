CXXFLAG = --std=c++11 -Wall -DCOLORFUL
#CC = /usr/local/Cellar/gcc/5.2.0/bin/g++-5
CC = g++

hw2: main.o client.o
	g++ $(CXXFLAG) -o hw2.run main.o client.o

main.o: main.cpp
	g++ -c $(CXXFLAG) main.cpp

client.o: client.h client.cpp
	g++ -c $(CXXFLAG) client.cpp

debug: clean
	$(CC) -c $(CXXFLAG) -g main.cpp
	$(CC) -c $(CXXFLAG) -g client.cpp
	$(CC) $(CXXFLAG) -g -o hw2.run main.o client.o

clean:
	rm -f *.o
	rm -f hw2.run
