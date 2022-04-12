build:
	gcc-11 -Wall -std=c99 ./src/*.c -o renderer.exec -I include -L lib -l SDL2-2.0.0

run:
	./renderer.exec

clean:
	rm renderer.exec