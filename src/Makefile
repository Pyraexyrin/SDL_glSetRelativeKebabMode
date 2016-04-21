CC = g++
CFLAGS = -g -Wall
LDFLAGS = -L/usr/X11R6/lib -lm -lGL -lglut -lGLU -ltiff  -lGLEW -lSDL2
TARGETS=main

all: $(TARGETS)

$(TARGETS):
	$(CC) $(CFLAGS) main.c sceneOpenGL.c cube.c events.c  $(LDFLAGS)  -o $@

clean:
	rm -f $(TARGETS)
