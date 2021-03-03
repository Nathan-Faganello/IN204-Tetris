
CC=g++
CFLAGS=-Wall -IExternal/SFML/include -std=c++14
LDFLAGS=-LExternal/SFML/lib -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system -std=c++14
EXEC=sfml-app

all: $(EXEC)


sfml-app: main.o piece.o board.o
	$(CC) -o $@ $^ $(LDFLAGS)

board.o: board.cpp
	$(CC) -c $^ $(CFLAGS)

piece.o: piece.cpp
	$(CC) -c $^ $(CFLAGS)

main.o: main.cpp board.cpp board.h
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf sfml-app
