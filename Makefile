CFLAGS = -c -Wall

all: Battle_Ship

Battle_Ship: Game.o Game_Structure.o Game_Boats.o Game_Play.o
	gcc Game.o Game_Structure.o Game_Boats.o Game_Play.o -o Battle_Ship

Game.o: Game.c
	gcc $(CFLAGS) Game.c

Game_Structure.o: Game_Structure.c
	gcc $(CFLAGS) Game_Structure.c

Game_Boats.o: Game_Boats.c
	gcc $(CFLAGS) Game_Boats.c

Game_Play.o: Game_Play.c
	gcc $(CFLAGS) Game_Play.c

exec:
	./Battle_Ship

clean:
	rm -rf *.o
	rm -rf Battle_Ship
