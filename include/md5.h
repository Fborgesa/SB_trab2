#ifndef MD5_h
#define MD5_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void md5(const uint8_t *msg_inicial, long long inicial_len, uint8_t *md5_msg);

int call_md5(char *ar, uint8_t result[16]);

void print_md5_to_cmd(uint8_t result[16]);

void print_md5_to_file(uint8_t result[16], char *fname);

#endif /* MD5_h */
