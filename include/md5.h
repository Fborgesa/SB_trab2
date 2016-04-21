#ifndef MD5_h
#define MD5_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void md5(const uint8_t *msg_inicial, long long inicial_len, uint8_t *md5_msg);
#endif /* CRC32_h */
