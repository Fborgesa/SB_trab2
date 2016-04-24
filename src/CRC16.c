#include "../include/CRC16.h"

#ifndef CRC16_c
#define CRC16_c

int generateCRC16(char* fname){
    FILE *fp_in;
    unsigned char c, d;
    int i, crc = 0;

    if ((fp_in = fopen(fname, "rb")) == NULL) {
        printf("\nErro ao abrir o arquivo de entrada.\n\n");
        //exit(0);
    }

    while (c = fgetc(fp_in), feof(fp_in) == 0) {
        crc = crc ^ c;
        for(i = 0; i < 8; i++){
            if(crc & 0x1 == 1){
                crc = crc ^ CRC16I;
                crc = crc >> 1;
            }
            else{
                crc = crc >> 1;
            }
        }
    }

    return crc;
}

int checkCRC16(int checkCRC, char* fname){
    FILE *fp_in;
    unsigned char c, d;
    int i, crc = 0;

    if ((fp_in = fopen(fname, "rb")) == NULL) {
        printf("\nErro ao abrir o arquivo de entrada.\n\n");
        //exit(0);
    }

    while (c = fgetc(fp_in), feof(fp_in) == 0) {
        crc = crc ^ c;
        for(i = 0; i < 8; i++){
            if(crc & 0x1 == 1){
                crc = crc ^ CRC16I;
                crc = crc >> 1;
            }
            else{
                crc = crc >> 1;
            }
        }
    }

    return crc == checkCRC;
}

#endif
