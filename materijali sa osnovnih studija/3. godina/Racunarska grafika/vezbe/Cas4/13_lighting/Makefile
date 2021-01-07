PROGRAM = 13_lighting
CC      = gcc
CFLAGS  = -g -ansi -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL

$(PROGRAM): main.o
	$(CC) $(LDFLAGS) -o $(PROGRAM) main.o $(LDLIBS)

.PHONY: clean dist run

run: $(PROGRAM)
	./$(PROGRAM)

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
