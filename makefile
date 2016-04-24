CC=gcc
CFLAGS=-I./include -std=c99 -g -O0
INCLUDE=./include
SOURCE=./src
OBJ = ./obj

all:
	@echo "Usage: make CRC or make md5 or make sha1"

CRC: CRC32.o CRC16.o mainCRC.o moveobj
	$(CC) $(CFLAGS) -o crc $(OBJ)/mainCRC.o $(OBJ)/CRC32.o $(OBJ)/CRC16.o

md5: mainMd5.o md5.o moveobj
	$(CC) $(CFLAGS) -o mainMd5 $(OBJ)/md5.o $(OBJ)/mainMd5.o
    
sha1: mainSha1.o sha1.o moveobj
	$(CC) $(CFLAGS) -o mainSha1 $(OBJ)/sha1.o $(OBJ)/mainSha1.o

md5.o: $(SOURCE)/md5.c $(INCLUDE)/md5.h
	$(CC) $(CFLAGS) $(SOURCE)/md5.c -c

mainMd5.o: $(SOURCE)/mainMd5.c $(INCLUDE)/md5.h
	$(CC) $(CFLAGS) $(SOURCE)/mainMd5.c -c

mainCRC.o: $(SOURCE)/mainCRC.c $(INCLUDE)/CRC32.h
	$(CC) $(CFLAGS) $(SOURCE)/mainCRC.c -c

CRC32.o: $(SOURCE)/CRC32.c $(INCLUDE)/CRC32.h
	$(CC) $(CFLAGS) $(SOURCE)/CRC32.c -c

CRC16.o: $(SOURCE)/CRC16.c $(INCLUDE)/CRC16.h
	$(CC) $(CFLAGS) $(SOURCE)/CRC16.c -c

sha1.o: $(SOURCE)/sha1.c $(INCLUDE)/sha1.h
	$(CC) $(CFLAGS) $(SOURCE)/sha1.c -c

mainSha1.o: $(SOURCE)/mainSha1.c $(INCLUDE)/sha1.h
	$(CC) $(CFLAGS) $(SOURCE)/mainSha1.c -c

moveobj:
	mkdir -p ./obj
	mv ./*.o ./obj
