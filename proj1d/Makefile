###############################################################################
# Makefile                                                                    #
# For Pacman Game (COMP 11 Project 1 | 2016 Spring)                           #
###############################################################################

all: pacman.o ghost.o game.o main.o termfuncs.o dot.o boulder.o
	clang++ -Wall -Wextra pacman.o ghost.o game.o main.o termfuncs.o \
			      dot.o boulder.o -o pacman

pacman.o: pacman.cpp pacman.h constants.h termfuncs.h
	clang++ -c -Wall -Wextra pacman.cpp

ghost.o: ghost.cpp ghost.h constants.h termfuncs.h
	clang++ -c -Wall -Wextra ghost.cpp

game.o: game.cpp *.h
	clang++ -c -Wall -Wextra game.cpp

main.o: main.cpp constants.h termfuncs.h
	clang++ -c -Wall -Wextra main.cpp

boulder.o: boulder.cpp boulder.h termfuncs.h constants.h
	clang++ -c -Wall -Wextra boulder.cpp

dot.o: dot.cpp dot.h constants.h termfuncs.h
	clang++ -c -Wall -Wextra dot.cpp

termfuncs.o: termfuncs.cpp termfuncs.h
	clang++ -c -Wall -Wextra termfuncs.cpp

clean:
	rm *.o pacman
