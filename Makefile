EXE=SDLShit
OBJS=src/main.c\
	 src/window.c\
	 src/game.c

all: $(OBJS)
	gcc $(OBJS) -w -lSDL2 -I'./inc/' -o $(EXE)

clean:
	rm -f $(EXE)
