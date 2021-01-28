CC=g++
CFLAGS=-Wall -IExternal/SFML/include
LDFLAGS=-LExternal/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
EXEC=sfml-app

all: $(EXEC)


sfml-app: main.o
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: main.cpp
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf hello
