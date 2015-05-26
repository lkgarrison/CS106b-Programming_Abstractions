TARGETS = problem2 problem3 

all: $(TARGETS) 

problem2: problem2.cpp problem2.h
	g++ $< -o $@

%: %.cpp
	g++ $< -o $@

clean:
	-rm $(TARGETS)
