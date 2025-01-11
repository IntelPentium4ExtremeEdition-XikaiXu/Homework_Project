CC=g++
CFLAGS=-I. -lm -g -std=c++11
DEPS = *.h
OBJTBC = objPos.o objPosDLinkedList.o objPosStack.o DLinkedList.o cmdQueue.o Test.o  

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Lab3: $(OBJTBC)
	$(CC) -o $@ ${OBJTBC} $(CFLAGS)

test:	testLab3
testLab3:
	./run.sh

.PHONY: clean

clean:
	del ${OBJTBC} *.exe *.xml Lab3
