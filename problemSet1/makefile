TARGETS = problem1 problem2 problem3
CC = g++

all: $(TARGETS)

problem%: problem%.cpp
	$(CC) $< -o $@

clean:
	-rm $(TARGETS)
