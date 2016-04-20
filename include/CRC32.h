#ifndef CRC32_h
#define CRC32_h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#endif /* CRC32_h */

// Brief: Gera um valor CRC32.
//
// Descrição: Gera um valor CRC32, através de uma busca em uma tabela pré-calculada
// e XOR`s consecutivos.
//
// Parâmetros:
// char *fname: nome do arquivo que terá seu CRC calculado.
//
// Retorno: Valor CRC.
int32_t generate_crc32(char *fname);

int check_crc32(char *fname);

// Brief: Reflete um byte.
//
// Exemplo: 10110010 ------> 01001101
//
// Parâmetros:
// uint8_t x: Byte a ser refletido.
//
// Retorno: Byte refletido.
uint8_t reflect(uint8_t b);

// Brief: Reflete uma palavra de 32 bits.
//
// Exemplo: 0xFF0F0F00 ------> 0x00F0F0FF
//
// Parâmetros:
// uint32_t x: Palavra de 32 bits a ser refletida.
//
// Retorno: Palavra refletida.
uint32_t reflect32(uint32_t x);