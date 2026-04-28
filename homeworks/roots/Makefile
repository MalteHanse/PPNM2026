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

# acc 
fig_acc.svg : wave.dat wave_acc_0.dat wave_acc_1.dat wave_acc_2.dat wave_acc_3.dat Makefile
	echo 'set terminal svg; \
	set output "$@"; \
	set title "acc"; \
	set xlabel "r"; \
	set ylabel "f(r)"; \
	plot "wave.dat" using 1:3 with lines dt 2 title "Exact f(r)", \
		"wave_acc_0.dat" using 1:2 with lines title "acc=1e-5", \
	     "wave_acc_1.dat" using 1:2 with lines title "acc=1e-3", \
	     "wave_acc_2.dat" using 1:2 with lines title "acc=1e-2", \
	     "wave_acc_3.dat" using 1:2 with lines title "acc=0.1"' | gnuplot

# eps 
fig_eps.svg : wave.dat wave_eps_0.dat wave_eps_1.dat wave_eps_2.dat wave_eps_3.dat Makefile
	echo 'set terminal svg; \
	set output "$@"; \
	set title "eps"; \
	set xlabel "r"; \
	set ylabel "f(r)"; \
	plot "wave.dat" using 1:3 with lines dt 2 title "Exact f(r)", \
		 "wave_eps_0.dat" using 1:2 with lines title "eps=1e-5", \
	     "wave_eps_1.dat" using 1:2 with lines title "eps=1e-3", \
	     "wave_eps_2.dat" using 1:2 with lines title "eps=1e-2", \
	     "wave_eps_3.dat" using 1:2 with lines title "eps=0.1"' | gnuplot

# rmax 
fig_rmax.svg : wave.dat wave_rmax_0.dat wave_rmax_1.dat wave_rmax_2.dat wave_rmax_3.dat Makefile
	echo 'set terminal svg; \
	set output "$@"; \
	set title "rmax"; \
	set xlabel "r"; \
	set ylabel "f(r)"; \
	plot "wave.dat" using 1:3 with lines dt 2 title "Exact f(r)", \
		 "wave_rmax_0.dat" using 1:2 with lines title "rmax=1", \
	     "wave_rmax_1.dat" using 1:2 with lines title "rmax=3", \
	     "wave_rmax_2.dat" using 1:2 with lines title "rmax=5", \
	     "wave_rmax_3.dat" using 1:2 with lines title "rmax=10"' | gnuplot

# rmin 
fig_rmin.svg : wave.dat wave_rmin_0.dat wave_rmin_1.dat wave_rmin_2.dat wave_rmin_3.dat Makefile
	echo 'set terminal svg; \
	set output "$@"; \
	set title "rmin"; \
	set xlabel "r"; \
	set ylabel "f(r)"; \
	plot "wave.dat" using 1:3 with lines dt 2 title "Exact f(r)", \
		 "wave_rmin_0.dat" using 1:2 with lines title "rmin=1e-5", \
	     "wave_rmin_1.dat" using 1:2 with lines title "rmin=1e-3", \
	     "wave_rmin_2.dat" using 1:2 with lines title "rmin=1e-2", \
	     "wave_rmin_3.dat" using 1:2 with lines title "rmin=1e-1"' | gnuplot

# build output
Out.txt: main
	./$< > $@

main : main.o

main.o : main.cpp matrix.hpp

.PHONY: clean
clean:
	rm Out.txt main main.o wave.dat wave_acc_0.dat wave_acc_1.dat wave_acc_2.dat wave_acc_3.dat wave_acc_4.dat wave_eps_0.dat wave_eps_1.dat wave_eps_2.dat wave_eps_3.dat wave_eps_4.dat wave_rmax_0.dat wave_rmax_1.dat wave_rmax_2.dat wave_rmax_3.dat wave_rmax_4.dat wave_rmin_0.dat wave_rmin_1.dat wave_rmin_2.dat wave_rmin_3.dat wave_rmin_4.dat fig_wave.svg fig_acc.svg fig_eps.svg fig_rmax.svg fig_rmin.svg 
test:
	@echo $(CXX)
	@echo $(CXXFLAGS)
	@echo $(RM)