hw4: main.cpp bst.h
	@echo "The author of this spaghetti is azdkj532."
	@echo "The code stores on the Github at https://github.com/azdkj532/CSIE-DS/tree/hw4."
	g++ -std=c++11 -o hw4 main.cpp 

debug: main.cpp bst.h
	g++ -g -std=c++11 -o hw4 main.cpp 

clean:
	rm -rf hw4
	rm -rf main.o
