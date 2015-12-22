ifeq ($(shell uname -s), Darwin)
LDFLAGS=-framework OpenGL -framework GLUT
else
LDFLAGS=-lX11 -lGL -lGLU -lglut -lm
endif
CC = gcc
PROGRAMS = main
$(PROGRAMS).o :
	$(CC) $(PROGRAMS).c -o $(PROGRAMS).o $(LDFLAGS)
clean:
	@rm -f *.o *.out core
