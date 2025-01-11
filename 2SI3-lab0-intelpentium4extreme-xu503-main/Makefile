CC=g++
CFLAGS=-I. -lm -g
DEPS = *.h
OBJ = Question1.o Test.o  

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Lab0: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test:	testLab0
testLab0:
	./run.sh

.PHONY: clean

clean:
	$(RM) *.o *.exe *.xml Lab0
