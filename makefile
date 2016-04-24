CC=gcc
CFLAGS=-I./include -std=c99 -g -O0
INCLUDE=./include
SOURCE=./src
OBJ = ./obj

all: crc hash

crc: CRC32.o CRC16.o mainCRC.o moveobj
	$(CC) $(CFLAGS) -o crc $(OBJ)/mainCRC.o $(OBJ)/CRC32.o $(OBJ)/CRC16.o

hash: sha1.o md5.o mainHash.o moveobj
	$(CC) $(CFLAGS) -o hash $(OBJ)/sha1.o $(OBJ)/md5.o $(OBJ)/mainHash.o

# Compilando o crc.
mainCRC.o: $(SOURCE)/mainCRC.c $(INCLUDE)/CRC32.h
	$(CC) $(CFLAGS) $(SOURCE)/mainCRC.c -c

CRC32.o: $(SOURCE)/CRC32.c $(INCLUDE)/CRC32.h
	$(CC) $(CFLAGS) $(SOURCE)/CRC32.c -c

CRC16.o: $(SOURCE)/CRC16.c $(INCLUDE)/CRC16.h
	$(CC) $(CFLAGS) $(SOURCE)/CRC16.c -c

# compilando o hash.
mainHash.o: $(SOURCE)/mainHash.c $(INCLUDE)/sha1.h $(INCLUDE)/md5.h
	$(CC) $(CFLAGS) $(SOURCE)/mainHash.c -c

sha1.o: $(SOURCE)/sha1.c $(INCLUDE)/sha1.h
	$(CC) $(CFLAGS) $(SOURCE)/sha1.c -c

md5.o: $(SOURCE)/md5.c $(INCLUDE)/md5.h
	$(CC) $(CFLAGS) $(SOURCE)/md5.c -c

moveobj:
	mkdir -p ./obj
	mv ./*.o ./obj
