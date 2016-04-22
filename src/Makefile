CC = g++
CFLAGS = -g -Wall
LDFLAGS = -L/usr/X11R6/lib -lm -lGL -lglut -lGLU -ltiff -lGLEW -lSDL2 -lSDL2_image -I/usr/include/SDL2
TARGETS=main

all: $(TARGETS)

$(TARGETS):
	$(CC) $(CFLAGS) *.c $(LDFLAGS) -o $@

clean:
	rm -f $(TARGETS)
