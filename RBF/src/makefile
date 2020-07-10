all: test

test: main.cpp rbf.o
	g++ -o test main.cpp rbf.o -Wall -O2 -larmadillo 

rbf.o: rbf.cpp rbf.hpp
	g++ -c rbf.cpp -Wall -O2 -larmadillo 

clean:
	rm *.o test