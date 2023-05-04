CC=gcc
CPP=g++
CFLAGS=-I.
OBJ = liste.o 

%.o: %.c $(DEPS)
	$(CPP) -c -o $@ $< $(CFLAGS)

liste: $(OBJ)
	$(CPP) -o $@ $^ $(CFLAGS)
