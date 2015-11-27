CXXFLAG = --std=c++11 -Wall -DCOLORFUL
#CC = /usr/local/Cellar/gcc/5.2.0/bin/g++-5
CC = g++
EXEC=hw2.run

$(EXEC): main.o client.o
	g++ $(CXXFLAG) -o $(EXEC) main.o client.o

main.o: main.cpp
	g++ -c $(CXXFLAG) main.cpp

client.o: client.h client.cpp
	g++ -c $(CXXFLAG) client.cpp

debug: clean
	$(CC) -c $(CXXFLAG) -g main.cpp
	$(CC) -c $(CXXFLAG) -g client.cpp
	$(CC) $(CXXFLAG) -g -o EXEC main.o client.o

test:
	cat test1.txt | ./$(EXEC) 

clean:
	rm -f *.o
	rm -f $(EXEC)
