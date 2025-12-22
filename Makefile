build:
	cd src && gcc -I../include -std=c99 main.c game_menu.c game_utils.c cheats.c missions.c -o ../main

run:
	./main

clean:
	rm -rf main