# P2 Make File M Mangini
CC=gcc

# Dir Definitions
IDIR=include
ODIR=obj
SRCDIR=src

DEPS = $(SRCDIR)/project2.h

OBJ = $(ODIR)/project2.o
OBJ += $(ODIR)/student2A.o
OBJ += $(ODIR)/student2B.o
OBJ += $(ODIR)/student2Common.o

$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $<

$(info objs: $(OBJ))

p2: $(OBJ)
	$(CC) -o $@ $^

.PHONY: clean

clean:
	rm -f p2 $(ODIR)/*.o *~ core $(IDIR)/*~
