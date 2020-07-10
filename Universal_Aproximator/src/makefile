all: test

test: main.cpp universal_approximator.o
	g++ -o test main.cpp universal_approximator.o -Wall -O2 -larmadillo 

universal_approximator.o: universal_approximator.cpp universal_approximator.hpp
	g++ -c universal_approximator.cpp -Wall -O2 -larmadillo 

clean:
	rm *.o test