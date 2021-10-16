CC = gcc
CFLAGS = -g3 --std=gnu99


movies: movie.h file.h
	$(CC) $(CFLAGS) -o movies main.c

clean:
	rm -f movies
	rm -rf moncadae.movies.*

.PHONY:
	clean
