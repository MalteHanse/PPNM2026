CXX = g++ -std=c++23
CXXFLAGS += -Wall -O
LDLIBS += -lstdc++ -lm -lpthread

all: Out.txt fig_dr.svg fig_rmax.svg wavefunctions.dat fig_waves.svg

fig_waves.svg : wavefunctions.dat Makefile
	echo 'set terminal svg; \
	set output "$@"; \
	set tics in; \
	set xlabel "r"; \
	set ylabel "|Psi|"; \
	plot \
		"$<" index 0 using 1:2 with linespoints title "k=0",
		"$<" index 0 using 1:3 with linespoints title "k=0",
		"$<" index 0 using 1:4 with linespoints title "k=0";' |\
	gnuplot

fig_dr.svg : out.dr.data Makefile
	echo 'set terminal svg; \
	set output "$@"; \
	set tics in; \
	set xlabel "dr"; \
	set ylabel "E0"; \
	plot \
		"$<" index 0 using 2:3 with linespoints title "dr";' |\
	gnuplot

fig_rmax.svg : out.rmax.data Makefile
	echo 'set terminal svg; \
	set output "$@"; \
	set tics in; \
	set xlabel "rmax"; \
	set ylabel "E0"; \
	plot \
		"$<" index 0 using 1:3 with linespoints title "rmax";' |\
	gnuplot

wavefunctions.dat: main
	./main -rmax 10 -dr 0.01 -wf wavefunctions.dat

out.dr.data: main
	for r in $$(seq 0.1 0.1 1); do \
		./$< -rmax 10 -dr $$r 2>> $@; \
	done

out.rmax.data: main
	for r in $$(seq 1 10); do \
		./$< -rmax $$r -dr 0.3 2>> $@; \
	done

Out.txt: main
	./$< > $@
	./$< -rmax 10 -dr 0.3 > $@

main : main.o

main.o : main.cpp matrix.hpp

.PHONY: clean
clean:
	rm Out.txt main main.o out.rmax.data out.dr.data wavefunctions.dat fig_dr.svg fig_rmax.svg 
test:
	@echo $(CXX)
	@echo $(CXXFLAGS)
	@echo $(RM)