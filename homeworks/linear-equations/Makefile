CXX = g++ -std=c++23
CXXFLAGS += -Wall -O
LDLIBS += -lstdc++ -lm -lpthread

run : Out.txt
	cat Out.txt
Out.txt: main
	./$< > $@

main : main.o

main.o : main.cpp matrix.hpp

.PHONY: clean
clean:
	rm main main.o Out.txt
test:
	@echo $(CXX)
	@echo $(CXXFLAGS)
	@echo $(RM)