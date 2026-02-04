CXX = g++ -std=c++23
CXXFLAGS += -Wall -Wextra -Werror
LDLIBS += -lstdc++ -lm 

Out.txt : main
# 	./main > Out.txt corresponds to:
	./$< > $@

main : main.o