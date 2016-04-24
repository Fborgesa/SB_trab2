/*
 *  Universidade de Bras�lia
 *  Instituto de Ciencias Exatas
 *  Departamento de Ci�ncia da Computa��o
 *
 *  Software B�sico - Turma A - 1/2016
 *
 *  Hashs e CRCs
 *
 *  Grupo 3:
 *      - Carlos Joel Tavares da Silva  13/0007293
 *      - Felipe Barreto Fernandes      09/0112831
 *      - Felipe Borges Albuquerque     09/93972
 *      - G�ssica Neves Sodr� da Silva  11/0146115
 *      - Pedro da Costa Abreu J�nior   11/0018800
 *
 *  Arquivo fonte "/crc16.c"
 */

#include "../include/CRC16.h"

#ifndef CRC16_c
#define CRC16_c

int generateCRC16(char* in, char* out){
    FILE *fp_in, *fp_out;
    unsigned char c, d;
    int i, crc = 0;

    if ((fp_in = fopen(in, "rb")) == NULL) {
        printf("\nErro ao abrir o arquivo de entrada.\n\n");
        exit(0);
    }

    if ((fp_out = fopen(out, "wb")) == NULL) {
        printf("\nErro ao abrir o arquivo de entrada.\n\n");
        exit(0);
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

    fprintf(fp_out, "%x", crc);

    fclose(fp_in);
    fclose(fp_out);

    return crc;
}

int checkCRC16(char* in, char* crcFile){
    FILE *fp_in, *fp_out, *fp_crc;
    unsigned char c, d;
    int i, crc = 0, checkCRC, rValue = 0;

    if ((fp_in = fopen(in, "rb")) == NULL) {
        printf("\nErro ao abrir o arquivo de entrada.\n\n");
        //exit(0);
    }

    if ((fp_out = fopen("crc_check.txt", "wb")) == NULL) {
        printf("\nErro ao abrir o arquivo de entrada.\n\n");
        //exit(0);
    }

    if ((fp_crc = fopen(crcFile, "rb")) == NULL) {
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

    fscanf(fp_crc, "%x", &checkCRC);

    printf("\nCRC recebido: %x\n", checkCRC);
    printf("\nCRC gerado: %x\n", crc);

    if (crc == checkCRC) {
        printf("\nArquivo integro.\n\n");
        rValue = 1;
    }
    else{
        printf("\nArquivo corrompido.\n\n");
    }


    fprintf(fp_out, "%x", crc);

    fclose(fp_in);
    fclose(fp_out);
    fclose(fp_crc);

    return rValue;
}

#endif
