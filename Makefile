CC = gcc
CFLAGS = -g3 --std=gnu99


movies: movie.h file.h
	$(CC) $(CFLAGS) -o movies_by_year main.c

clean:
	rm -f movies_by_year
	rm -rf moncadae.movies.*

.PHONY:
	clean
