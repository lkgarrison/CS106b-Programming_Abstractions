TARGETS = problem1 problem2 problem4 problem5
CC = g++

all: $(TARGETS)

problem%: problem%.cpp
	$(CC) $< -o $@

clean:
	-rm $(TARGETS)
