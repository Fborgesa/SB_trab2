#ifndef CRC16_h
#define CRC16_h

#define CRC16 0x18005
#define CRC16I 0x14003

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int generateCRC16(char* in, char* out);
int checkCRC16(char* in, char* checkCRC);

#endif /* CRC16_h */