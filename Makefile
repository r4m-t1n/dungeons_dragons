build:
	cd src && gcc -std=c99 main.c game_utils.c load_game.c -o ../main

run:
	./main

clean:
	rm -rf main