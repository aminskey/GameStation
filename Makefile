all:
	rm -rf ~/bin/GameStation
	gcc libfuncs/*.c stgame.c -Ilibs -fdiagnostics-generate-patch -lncurses -lcurl -o ~/bin/GameStation
