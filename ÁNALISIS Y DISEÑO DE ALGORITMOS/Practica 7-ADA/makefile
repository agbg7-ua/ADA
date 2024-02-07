#ANDREA GOMEZ BOBES
OPTS = -Wall -O3 -std=c++0x

maze: maze_greedy.cc
	g++ ${OPTS} -o maze_greedy maze_greedy.cc	 


all: maze
	./maze_greedy -f files/maze_n301r.def

tar: maze_greedy.cc makefile
	tar cvfz 48682738H.tar.gz maze_greedy.cc makefile

clean: 
	rm maze_greedy
 
