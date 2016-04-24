/*
 *  Universidade de Brasília
 *  Instituto de Ciencias Exatas
 *  Departamento de Ciência da Computação
 *
 *  Software Básico - Turma A - 1/2016
 *
 *  Hashs e CRCs
 *
 *  Grupo 3:
 *      - Carlos Joel Tavares da Silva  13/0007293
 *      - Felipe Barreto Fernandes      09/0112831
 *      - Felipe Borges Albuquerque     09/93972
 *      - Géssica Neves Sodré da Silva  11/0146115
 *      - Pedro da Costa Abreu Júnior   11/0018800
 *
 *  Arquivo de cabeçalho "md5.h"
 */
#ifndef MD5_h
#define MD5_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void to_bytes(uint32_t val, uint8_t *bytes);

uint32_t to_int32(const uint8_t *bytes);

void toword_array(const size_t val, uint32_t *saida);

void md5(const uint8_t *msg_inicial, long long inicial_len, uint8_t *md5_msg);

int call_md5(char *ar, uint8_t result[16]);

void print_md5_to_cmd(uint8_t result[16]);

void print_md5_to_file(uint8_t result[16], char *fname);

#endif /* MD5_h */
