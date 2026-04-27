CXX = g++ -std=c++23
CXXFLAGS += -Wall -O
LDLIBS += -lstdc++ -lm -lpthread

all: Out.txt fig_wave.svg fig_acc.svg fig_eps.svg fig_rmax.svg fig_rmin.svg

fig_wave.svg : wave.dat Makefile
	echo 'set terminal svg; \
	set output "fig_wave.svg"; \
	set title "Wavefunction"; \
	set xlabel "x"; \
	set ylabel "y"; \
	plot \
		"wave.dat" using 1:2 with lines dt 1 title "Numerical f(r)", \
		"wave.dat" using 1:3 with lines dt 2 title "Exact f(r)"' |\
	gnuplot

# acc experiments combined
fig_acc.svg : wave_acc_0.dat wave_acc_1.dat wave_acc_2.dat wave_acc_3.dat wave_acc_4.dat Makefile
	echo 'set terminal svg; set output "$@"; set title "acc"; set xlabel "r"; set ylabel "f(r)"; \
	plot "wave_acc_0.dat" using 1:2 with lines title "acc=0", \
	     "wave_acc_1.dat" using 1:2 with lines title "acc=1", \
	     "wave_acc_2.dat" using 1:2 with lines title "acc=2", \
	     "wave_acc_3.dat" using 1:2 with lines title "acc=3", \
	     "wave_acc_4.dat" using 1:2 with lines title "acc=4"' | gnuplot

# eps experiments combined
fig_eps.svg : wave_eps_0.dat wave_eps_1.dat wave_eps_2.dat wave_eps_3.dat wave_eps_4.dat Makefile
	echo 'set terminal svg; set output "$@"; set title "eps"; set xlabel "r"; set ylabel "f(r)"; \
	plot "wave_eps_0.dat" using 1:2 with lines title "eps=0", \
	     "wave_eps_1.dat" using 1:2 with lines title "eps=1", \
	     "wave_eps_2.dat" using 1:2 with lines title "eps=2", \
	     "wave_eps_3.dat" using 1:2 with lines title "eps=3", \
	     "wave_eps_4.dat" using 1:2 with lines title "eps=4"' | gnuplot

# rmax experiments combined
fig_rmax.svg : wave_rmax_0.dat wave_rmax_1.dat wave_rmax_2.dat wave_rmax_3.dat wave_rmax_4.dat Makefile
	echo 'set terminal svg; set output "$@"; set title "rmax"; set xlabel "r"; set ylabel "f(r)"; \
	plot "wave_rmax_0.dat" using 1:2 with lines title "rmax=0", \
	     "wave_rmax_1.dat" using 1:2 with lines title "rmax=1", \
	     "wave_rmax_2.dat" using 1:2 with lines title "rmax=2", \
	     "wave_rmax_3.dat" using 1:2 with lines title "rmax=3", \
	     "wave_rmax_4.dat" using 1:2 with lines title "rmax=4"' | gnuplot

# rmin experiments combined
fig_rmin.svg : wave_rmin_0.dat wave_rmin_1.dat wave_rmin_2.dat wave_rmin_3.dat wave_rmin_4.dat Makefile
	echo 'set terminal svg; set output "$@"; set title "rmin"; set xlabel "r"; set ylabel "f(r)"; \
	plot "wave_rmin_0.dat" using 1:2 with lines title "rmin=0", \
	     "wave_rmin_1.dat" using 1:2 with lines title "rmin=1", \
	     "wave_rmin_2.dat" using 1:2 with lines title "rmin=2", \
	     "wave_rmin_3.dat" using 1:2 with lines title "rmin=3", \
	     "wave_rmin_4.dat" using 1:2 with lines title "rmin=4"' | gnuplot

# build output
Out.txt: main
	./$< > $@

main : main.o

main.o : main.cpp matrix.hpp

.PHONY: clean
clean:
	rm Out.txt main main.o
test:
	@echo $(CXX)
	@echo $(CXXFLAGS)
	@echo $(RM)