EXE=DLA
OBJS=src/main.c\
	 src/window.c\
	 src/game.c
FLAGS=-lSDL2 -I'./inc/' -g

CC=clang

all: $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $(EXE)

clean:
	rm -f $(EXE)
