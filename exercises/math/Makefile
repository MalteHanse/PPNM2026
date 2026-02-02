CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm

Out.txt : main
	./main > Out.txt

main : main.o sfuns.o
# 	$(CXX) $^ $(LDLIBS) -o main

main.o : main.cpp sfuns.h
# 	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

sfuns.o : sfuns.h sfuns.cpp
# 	$(CXX) $(CXXFLAGS) -c sfuns.cpp -o sfuns.o

.PHONEY:clean
clean:
	$(RM) --force main main.o sfuns.o Out.txt

test:
	@echo $(CXX)
	@echo $(CXX)
	@echo $(RM)