CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++0x

__start__: tictac
	./tictac

tictac: main.o gra.o minimax.o
	g++ -Wall -pedantic -std=c++0x -o tictac main.o gra.o minimax.o
	 


main.o:  main.cpp gra.hpp
	g++ -c ${CXXFLAGS} -o  main.o main.cpp

gra.o: gra.cpp gra.hpp
	g++ -c ${CXXFLAGS} -o gra.o gra.cpp

minimax.o: minimax.cpp minimax.hpp
	g++ -c ${CXXFLAGS} -o minimax.o minimax.cpp

clean:
	rm -f *.o tictac