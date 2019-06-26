CFLAGS = -O
CC = g++

Emulator: main.o MC68K.o
	$(CC) $(CFLAGS) -o Emulator main.o MC68K.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

MC68K.o: MC68K.cpp
	$(CC) $(CFLAGS) -c MC68K.cpp