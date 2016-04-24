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
 *  Arquivo fonte "sha1.c"
 *
 *  Descrição: Esse arquivo fonte contém as implementações
 *             dos protótipos de funções descritos em "sha.h".
 *             Aqui encontramos as implementação do Secure
 *             Hashing Algorithm 1 (SHA-1). Para a descrição das
 *             funções, estruturas e macros, consulte o arquivo
 *             de cabeçalho "sha.h".
 */

#include "sha1.h"

void sha1_init(sha1_info *context){

        context->byteCount = 0;

        context->msg_block_index = 0;

        context->buffer[0] = H0;
        context->buffer[1] = H1;
        context->buffer[2] = H2;
        context->buffer[3] = H3;
        context->buffer[4] = H4;
}

int generate_sha1(sha1_info *context, char *fname, uint8_t sha1_hash[HASH_SIZE]){
        FILE *fp_in = NULL;
        int i; // Contador do loop que percorre o buffer
        char b = '\0';

        if ((fp_in = fopen(fname, "rb")) == NULL) {
                printf("\nErro ao abrir o arquivo de entrada.\n\n");
                exit(0);
        }

        // Se o tamanho da string é 0, o hash também
        if (b = getc(fp_in), feof(fp_in) != 0)
                return sha_success;
        else
                ungetc(b, fp_in);

        // Percorre a mensagem original, criando os blocos de 8-bits
        while(b = getc(fp_in), feof(fp_in) == 0 ) {
                context->msg_block[context->msg_block_index++] = b;

                // faz a contagem do número de bytes da mensagem original
                context->byteCount++;

                if (context->msg_block_index == MESSAGE_BLOCK) {
                        sha1_hash_block(context);
                }
        }

        fclose(fp_in);

        // Cria o message digest de 160-bit, completando o último bloco de mensagem
        // com o tamanho do arquivo original
        sha1_message_pad(context);

        // Preenche o sha1_hash com o buffer
        for(i = 0; i < HASH_SIZE; ++i) {
                sha1_hash[i] = context->buffer[i>>2] >> 8 * (3 - (i & 0x03));
        }

        return sha_success;
}

void sha1_message_pad(sha1_info *context){
        /*
         *  Verifica se o bloco de mensagem suporta os 64-bits finais
         *  com o tamanho do arquivo original
         */

        // Acrescenta 1 seguido de quinze 0 representado pelo hexadecimal 0x80
        context->msg_block[context->msg_block_index++] = MASK1;

        /*
         * Se a mensagem original for maior que 55bytes, cria-se outro bloco
         * para completar as informações
         */
        if(context->msg_block_index > 55) {
                // Completa o bloco de 64bytes com 0
                while(context->msg_block_index < MESSAGE_BLOCK) {
                        context->msg_block[context->msg_block_index++] = 0;
                }

                // Processa o bloco de mensagem completo e reseta o msg_block_index
                sha1_hash_block(context);
        }

        // Completa até o byte 55 com 0
        while(context->msg_block_index < 56) {
                context->msg_block[context->msg_block_index++] = 0;
        }

        // Concatena o tamanho da mensagem origina ao final do bloco
        context->msg_block[56] = 0;
        context->msg_block[57] = 0;
        context->msg_block[58] = 0;
        context->msg_block[59] = context->byteCount >> 29;
        context->msg_block[60] = context->byteCount >> 21;
        context->msg_block[61] = context->byteCount >> 13;
        context->msg_block[62] = context->byteCount >> 5;
        context->msg_block[63] = context->byteCount << 3;

        sha1_hash_block(context);
}

void sha1_hash_block(sha1_info *context){
        int t;                       /* Contador dos loops                  */
        uint32_t temp;               /* Valor temporário da palavra         */
        uint32_t w[80];              /* Sequência 80 palavras de 32-bits    */
        uint32_t a, b, c, d, e;      /* Buffers de palavras                 */

        // Divide o bloco de mensagem em 16 palavras
        for(t = 0; t < 16; t++) {
                w[t] = context->msg_block[t * 4] << 24;
                w[t] |= context->msg_block[t * 4 + 1] << 16;
                w[t] |= context->msg_block[t * 4 + 2] << 8;
                w[t] |= context->msg_block[t * 4 + 3];
        }

        // Aplica o shift circular para a esquerda
        for(t = 16; t < 80; t++) {
                w[t] = shar1_circular_shift(w[t-3] ^ w[t-8] ^ w[t-14] ^ w[t-16], 1);
        }

        // Aplica aos buffers de palavras as constantes definidas pelo SHA-1
        a = context->buffer[0];
        b = context->buffer[1];
        c = context->buffer[2];
        d = context->buffer[3];
        e = context->buffer[4];

        for(t = 0; t < 80; t++) {
                if(t < 20) {
                        temp = shar1_circular_shift(a,5) + F0(b,c,d) + e +w[t] + K0;
                }else if(t < 40) {
                        temp = shar1_circular_shift(a,5) + FXOR(b,c,d) + e + w[t] + K20;
                }else if(t < 60) {
                        temp = shar1_circular_shift(a,5) + FOR(b,c,d) + e + w[t] + K40;
                }else{
                        temp = shar1_circular_shift(a,5) + FXOR(b,c,d) + e + w[t] + K60;
                }

                e = d;
                d = c;
                c = shar1_circular_shift(b, 30);

                b = a;
                a = temp;
        }

        // Preenche o message digest
        context->buffer[0] += a;
        context->buffer[1] += b;
        context->buffer[2] += c;
        context->buffer[3] += d;
        context->buffer[4] += e;

        context->msg_block_index = 0;
}

void print_sha1_to_cmd(uint8_t* sha1_hash){
        int i;
        printf("\t");
        for (i=0; i<20; i++) {
                printf("%02x ", sha1_hash[i]);
        }
        printf("\n");
}

void print_sha1_to_file(uint8_t* sha1_hash, char *fname) {
        FILE *fp_out = NULL;
        int i;

        if ((fp_out = fopen(fname, "wb")) == NULL) {
            printf("\nErro ao abrir o arquivo de saída.\n\n");
            exit(0);
        }

        for (i=0; i<20; i++) {
                fprintf(fp_out, "%02x ", sha1_hash[i]);
        }

        fclose(fp_out);
}

uint32_t shar1_circular_shift(uint32_t word, uint8_t bits){
        return ((word << bits) | (word >> (32 - bits)));
}
