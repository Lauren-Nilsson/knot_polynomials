# This is a makefile.

PROG = simulate_topology

OBJ = main.o 

CC = g++ -g -Wall

CFLAG = -c

OFLAG = -o

$(PROG) : $(OBJ)
	$(CC) $(OFLAG) $(PROG) $(OBJ) $(LIBS)

main.o:	knot.h crossing.h loop.h segment.h pair.h

clean:
	rm -f *.o
