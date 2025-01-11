CC=g++
CFLAGS=-I. -lm -g -std=c++11
DEPS = *.h
OBJ = objPos.o objPosBST.o Test.o  

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Lab4: $(OBJ)
	$(CC) -o $@ ${OBJ} $(CFLAGS)

test:	testLab4
testLab4:
	./run.sh

.PHONY: clean

clean:
	del ${OBJ} *.exe *.xml Lab4
