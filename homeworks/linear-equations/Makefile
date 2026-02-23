CXX = g++ -std=c++23
CXXFLAGS += -Wall -O
LDLIBS += -lstdc++ -lm -lpthread

Out.txt : main

main.o : matrix.hpp

.PHONY: clean
clean:
	$(RM) $(EXECUTABLES) $(OBJECTS) $(DATA_FILES) $(PLOT_FILES) $(LOG_FILES) Out.txt
test:
	@echo $(CXX)
	@echo $(CXXFLAGS)
	@echo $(RM)