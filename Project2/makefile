CC = gcc
DEPS= project2.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

p2: project2.o student2A.o student2B.o student2Common.o
	$(CC) -o p2 project2.o student2A.o student2B.o student2Common.o

clean:
	rm ./*.o