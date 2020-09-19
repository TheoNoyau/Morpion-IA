all: morpion morpion.o morpion_sdl.o

morpion_sdl.o: morpion_sdl.c morpion_sdl.h morpion.h
	gcc -O3 -c morpion_sdl.c -lSDL2 -lSDL2_ttf

morpion.o: morpion.c morpion.h
	gcc -O3 -c morpion.c 

morpion: main.c morpion.c morpion.h morpion_sdl.h
	gcc -O3 -o morpion main.c morpion.c morpion_sdl.c -lSDL2 -lSDL2_ttf

clean:
	rm *.o

