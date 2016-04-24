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
 *  Arquivo de cabe�alho "CRC16.h"
 */

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
