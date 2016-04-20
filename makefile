CC=gcc
CFLAGS=-I./include -std=c99 -g -O0
INCLUDE=./include
SOURCE=./src
OBJ = ./obj

all: mainCRC

mainCRC: CRC32.o mainCRC.o moveobj
	$(CC) $(CFLAGS) -o crc $(OBJ)/mainCRC.o $(OBJ)/CRC32.o

mainHash:

mainCRC.o: $(SOURCE)/mainCRC.c $(INCLUDE)/CRC32.h
	$(CC) $(CFLAGS) $(SOURCE)/mainCRC.c -c

CRC32.o: $(SOURCE)/CRC32.c $(INCLUDE)/CRC32.h
	$(CC) $(CFLAGS) $(SOURCE)/CRC32.c -c

moveobj:
	mv ./*.o ./obj