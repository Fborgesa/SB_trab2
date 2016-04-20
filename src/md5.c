#include "..\include\md5.h"


// Constants are the integer part of the sines of integers (in radians) * 2^32.
const uint32_t k[64] = {
0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee ,
0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501 ,
0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be ,
0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821 ,
0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa ,
0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8 ,
0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed ,
0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a ,
0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c ,
0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70 ,
0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05 ,
0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665 ,
0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039 ,
0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1 ,
0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1 ,
0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

// r specifies the per-round shift amounts
const uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                      5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                      4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                      6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

// leftrotate function definition
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

void to_bytes(uint32_t val, uint8_t *bytes)
{
    bytes[0] = (uint8_t) val;
    bytes[1] = (uint8_t) (val >> 8);
    bytes[2] = (uint8_t) (val >> 16);
    bytes[3] = (uint8_t) (val >> 24);
}

uint32_t to_int32(const uint8_t *bytes)
{
    return (uint32_t) bytes[0]
        | ((uint32_t) bytes[1] << 8)
        | ((uint32_t) bytes[2] << 16)
        | ((uint32_t) bytes[3] << 24);
}

#define F(X,Y,Z) (((X) & (Y)) | (~(X) & (Z)))
#define G(X,Y,Z) (((X) & (Z)) | ((Y) & ~(Z)))
#define H(X,Y,Z) ((X) ^ (Y) ^ (Z))
#define I(X,Y,Z) ((Y) ^ ((X) | ~(Z)))

// o vetor de saída deve ter tamanho 2
// In this document a "word" is a 32-bit quantity and a "byte" is an
// eight-bit quantity.
void toword_array(const size_t val, uint32_t *saida){
    saida[0] = (uint32_t) val;
    saida[1] = (uint32_t) (val >> 32);
}

void md5(const uint8_t *msg_inicial, uint8_t *md5_msg)
{
    //as variáveis que vão conter a mensagem
    uint32_t aa, bb, cc, dd;

    long long msglen;
    int i, offset;
    size_t inicial_len;
    uint32_t lenword[2], w[16];
    uint32_t a, b, c, d, f, g, temp;
    uint8_t *msg = NULL;

    inicial_len = strlen(msg_inicial);
    //msglen is len (in bits) at the beginning, and at the end will be congruent to 448 mod 512
    for(msglen = (inicial_len + 1) * 8; msglen % 512 < 448; msglen++);

    msglen = msglen / 8; //msglen in bytes plus the 64 bits of len to be appended
    msg = (uint8_t*)malloc(msglen + 8);
    memcpy(msg, msg_inicial, inicial_len);
    msg[inicial_len] = 0x80;
    for(i=inicial_len+1; i < msglen; i++)
        msg[i] = 0x00;

    toword_array(inicial_len, lenword);

    to_bytes(inicial_len<<3, msg + msglen);
    to_bytes(inicial_len>>29, msg + msglen + 4);

    printf("Len da msg: %d\n\n", msglen+8);

    //4 buffers de 32 bits são inicializados para computar o hash
    aa = 0x67452301;
    bb = 0xefcdab89;
    cc = 0x98badcfe;
    dd = 0x10325476;

    // processar a mensagem em chunks de 64 bytes (512 bits)
    for(offset=0; offset<msglen; offset += 64) {

        // break chunk into sixteen 32-bit words w[j], 0 ≤ j ≤ 15
        for (i = 0; i < 16; i++)
            w[i] = to_int32(msg + offset + i*4);

        // Initialize hash value for this chunk:
        a = aa;
        b = bb;
        c = cc;
        d = dd;

        // Main loop:
        for(i = 0; i<64; i++) {

            if (i < 16) {
                f = F(b,c,d);
                g = i;
            } else if (i < 32) {
                f = G(b,c,d);
                g = (5*i + 1) % 16;
            } else if (i < 48) {
                f = H(b,c,d);
                g = (3*i + 5) % 16;
            } else {
                f = I(b,c,d);
                g = (7*i) % 16;
            }

            temp = d;
            d = c;
            c = b;
            b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);
            a = temp;

        }

        // Add this chunk's hash to result so far:
        aa += a;
        bb += b;
        cc += c;
        dd += d;

    }
    free(msg);

    to_bytes(aa, md5_msg);
    to_bytes(bb, md5_msg + 4);
    to_bytes(cc, md5_msg + 8);
    to_bytes(dd, md5_msg + 12);


}
