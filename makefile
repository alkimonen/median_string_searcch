all: build
build: medianSearch.cpp
	g++ -o medianSearch medianSearch.cpp
run:
	./medianSearch ${in} ${out}
clear:
	rm -f medianSearch