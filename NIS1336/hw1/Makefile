DEP = utils.o

all: prog1 prog2 prog1_cpp prog2_cpp

prog1: $(DEP) prog1.c
	$(CC) prog1.c $(DEP) -o prog1

prog2: $(DEP) prog2.c
	$(CC) prog2.c $(DEP) -o prog2

prog1_cpp: $(DEP) prog1.cc
	$(CXX) prog1.cc $(DEP) -o prog1_cpp

prog2_cpp: $(DEP) prog2.cc
	$(CXX) prog2.cc $(DEP) -o prog2_cpp
