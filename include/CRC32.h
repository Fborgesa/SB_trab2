#ifndef CRC32_h
#define CRC32_h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Brief: Gera um valor CRC32.
//
// Descrição: Gera um valor CRC32, através de uma busca em uma tabela pré-calculada
// e XOR`s consecutivos.
//
// Parâmetros:
// char *fname: nome do arquivo que terá seu CRC calculado.
//
// Retorno: Valor CRC.
int32_t generate_crc32(char *fname_in, char* fname_out);

// Brief: Checa a integridade de um arquivo a partir do seu CRC.
//
// Descrição: Recebe um arquivo que será checado e outro arquivo com o seu CRC,
// gera um novo CRC e compara os dois.
//
// Parâmetros:
// char *fname_in_file: nome do arquivo a ser checado.
// char *fname_in_crc: nome do arquivo com o CRC pré-calculado.
//
// Retorno: Retorna 1 se o arquivo estiver integro e 0 se o arquivo estiver
// corrompido.
int32_t check_crc32(char *fname_in_file, char *fname_in_crc);

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

#endif /* CRC32_h */
