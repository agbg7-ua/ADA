#ANDREA GÓMEZ BOBES 48679841L
OPTS = -Wall -Wextra -O3 -std=c++0x

quickSort: bubbleSort.cc
	g++ ${OPTS} -o quickSort quickSort.cc	 

quickSort.CPUtimes: quickSort
	./quickSort > quickSort.CPUtimes

graphs: quickSort.CPUtimes quickSort.gnuplot
	gnuplot quickSort.gnuplot

all: quickSort quickSort.CPUtimes graphs

tar: quickSort.cc quickSort.gpi makefile
	tar cvfz mi_DNI-NIE.tar.gz quickSort.cc quickSort.gpi makefile

clean: 
	rm -f quickSort quickSort.CPUtimes fit.log quickSort*.png *~