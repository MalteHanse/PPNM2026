CXX = g++ -std=c++23
CXXFLAGS += -Wall -O
LDLIBS += -lstdc++ -lm -lpthread

Out.txt : main
	./main > Out.txt

main.o : matrix.hpp

.PHONY: clean
clean:
	rm main main.o Out.txt
test:
	@echo $(CXX)
	@echo $(CXXFLAGS)
	@echo $(RM)