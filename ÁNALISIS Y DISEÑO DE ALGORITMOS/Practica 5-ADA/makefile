#ANDREA GOMEZ BOBES
OPTS = -Wall -Wextra -std=c++0x

all: pow2 graphs
pow: pow2.cc
	g++ ${OPTS} -o pow pow2.cc	 

pow2: pow
	./pow > pow2

graphs: pow2 pow.gpi
	gnuplot pow.gpi



tar: pow.cc pow.gpi makefile
	tar cvfz 48679841L.tar.gz pow2.cc pow.gpi makefile

clean: 
	rm -f pow pow2 fit.log pow2*.png *
 
