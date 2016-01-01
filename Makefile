hw4: main.cpp bst.h
	g++ -std=c++11 -o hw4 main.cpp 

debug: main.cpp bst.h
	g++ -g -std=c++11 -o hw4 main.cpp 

clean:
	rm -rf hw4
	rm -rf main.o
