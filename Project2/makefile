IDIR = ../include
CC = gcc

ODIR=obj
LDIR =../lib

_DEPS = project2.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = project2.o student2A.o student2B.o student2Common.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

p2: $(OBJ)
	$(CC) -o $@ $^

PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~