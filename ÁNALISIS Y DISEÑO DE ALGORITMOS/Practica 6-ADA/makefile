#ANDREA GOMEZ BOBES
OPTS = -Wall -Wextra -std=c++0x

all: maze
	./maze
maze: maze.cc
	g++ ${OPTS} -o maze maze.cc	 

tar: maze.cc makefile
	tar cvfz 48679841L.tar.gz maze.cc makefile


clean: 
	rm -f maze
 
