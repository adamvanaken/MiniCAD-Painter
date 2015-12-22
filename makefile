ifeq ($(shell uname -s), Darwin)
LDFLAGS=-framework OpenGL -framework GLUT -g
else
LDFLAGS=-lX11 -lGL -lGLU -lglut -lm -g
endif
CC = gcc
PROGRAMS = main
$(PROGRAMS).o :
	$(CC) $(PROGRAMS).c draw.c picker.c callbacks.c helper.c dlinked.c -o $(PROGRAMS).o $(LDFLAGS)
clean:
	@rm -f *.o *.out core
