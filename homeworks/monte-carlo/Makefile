CXX = g++ -std=c++23
CXXFLAGS += -Wall -O
LDLIBS += -lstdc++ -lm -lpthread

all: Out.txt fig_circle.svg

fig_circle.svg : circle.dat Makefile
	echo 'set terminal svg; \
	set output "fig_circle.svg"; \
	set title "Integration error"; \
	set xlabel "N"; \
	set ylabel "error"; \
	a1=1; b1=0.1; \
	f(x) = a1 / sqrt(x) + b1; \
	fit f(x) "circle.dat" using 1:2 via a1,b1; \
	a2=1; b2=0.1; c2=1; \
	g(x) = a2 * log(x)**c2 / x + b2; \
	fit g(x) "quasi.dat" using 1:2 via a2,b2,c2; \
	plot \
		"circle.dat" using 1:2 with lines dt 1 title "Error plain MC", \
		"quasi.dat"  using 1:2 with lines dt 1 title "Error quasi-random MC", \
		f(x) title "Fit: a/sqrt(N) + b", \
		g(x) title "Fit: a*log(N)^c / N + b"' \
	| gnuplot

# build output
Out.txt: main
	./$< > $@

main : main.o

main.o : main.cpp matrix.hpp

.PHONY: clean
clean:
	rm Out.txt main main.o circle.dat fig_circle.svg
test:
	@echo $(CXX)
	@echo $(CXXFLAGS)
	@echo $(RM)