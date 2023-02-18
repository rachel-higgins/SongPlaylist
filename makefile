CC = g++
CPPFLAGS = -Wall -g -std=c++11

main:			main.o songlist.o song.o

main.o:			main.h songlist.h

songlist.o:			songlist.h

song.o:			song.h

.PHONY: clean	
clean:			# clean the directory
			$(info -- cleaning the directory --)
			rm -f *.o
			rm -f main
