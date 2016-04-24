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
 *  Arquivo de cabeçalho "sha1.h"
 *
 *  Descrição: Esse arquivo de cabeçalho contém as definições
 *             estruturas e protótipos de funções utilizados
 *             pelo arquivo fonte "sha1.c". Aqui encontramos as
 *             definições da implementação do Secure Hashing
 *             Algorithm 1 (SHA-1)
 */


#ifndef _SHA1_H_
#define _SHA1_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef _SHA_enum_
#define _SHA_enum_
enum{
    sha_success = 0,    /* código de sucesso                */
    sha_failure = 1,    /* código de falha                  */
};
#endif

#define HASH_SIZE 20
#define MESSAGE_BLOCK 64

/*
 * Funções lógicas definidas pleo SHA-1.
 * Operam sobre três palavras de 32-bits e
 * produzem uma palavra de 32-bits para 0 <= t <= 79
 */
#define F0(b,c,d) ((b & c) | ((~b) & d))            /* 0 <= t <= 19                     */
#define FOR(b,c,d) ((b & c) | (b & d) | (c & d))    /* 40 <= t <= 59                    */
#define FXOR(b,c,d) (b ^ c ^ d)                     /* 20 <= t <= 39 ou 60 <= t <= 79   */

/* "palavras" constantes definidas pelo SHA-1 */
#define K0  0x5a827999  /* 0 <= t <= 19       */
#define K20 0x6ed9eba1  /* 20 <= t <= 39      */
#define K40 0x8f1bbcdc  /* 40 <= t <= 59      */
#define K60 0xca62c1d6  /* 60 <= t <= 79      */

/* buffer de cinco palavras de 32-bits definidas pelo SHA-1 */
#define H0  0x67452301;
#define H1  0xefcdab89;
#define H2  0x98badcfe;
#define H3  0x10325476;
#define H4  0xc3d2e1f0;

/* definição das máscaras para operações binárias */
#define MASK       0x80


/*
 *  Estrutura que armazena as informações de contexto
 *  definidas em SHA-1 para as operações de hash
 */
typedef struct sha1_info{
    uint32_t buffer[HASH_SIZE/4];           /* Message digest: 20-bytes representados em 5 palavras */

    uint32_t byteCount;

    int_least16_t msg_block_index;          /* Índice para o bloco de mensagem                      */
    uint8_t msg_block[MESSAGE_BLOCK];       /* Bloco de mensagem de 64-bytes                        */

}sha1_info;


 /*
  * Brief       : Inicializa o contexto
  *
  * Descrição   : Inicializa o contexto com as informações necessárias para
  *             o processamento
  * Parâmetros  :
  *             sha1_info *context: contexto que armazenará todas as informações
  *                                  relativas ao bloco de mensagem sendo processado
  * Retorno     : Nenhum
  */
void sha1_init(sha1_info *context);

 /*
  * Brief       : Gera um hash utilizando SHA-1
  *
  * Descrição   : Gera um hash utilizando SHA-1 para a mensagem original informada
  *
  * Parâmetros  :
  *             sha1_info *context: contexto que armazenará todas as informações
  *                                  relativas ao bloco de mensagem sendo processado
  *             char *fname: nome do arquivo de onde o hash será gerado
  *             uint8_t sha1_hash[HASH_SIZE]: array que suporta o resultado o hash sha-1
  * Retorno     : código de erro
  */
int generate_sha1(sha1_info *context, char *fname, uint8_t sha1_hash[HASH_SIZE]);

 /*
  * Brief       : Cria blocos de mensagem múltiplos de 512-bits
  *
  * Descrição   : Acrescenta bits a mensagem até que tenha um múltiplo de 512.
  *             O primeiro bit acrescentado deve ser '1' e os últimos 64-bits representam
  *             o tamanho da mensagem original, todos os bits no meio devem ser '0'
  * Parâmetros  :
  *             sha1_info *context: contexto que armazenará todas as informações
  *                                  relativas ao bloco de mensagem sendo processado
  * Retorno     : Nenhum
  */
void sha1_message_pad(sha1_info *context);

 /*
  * Brief       : Processa os blocos de mensagem múltiplos de 512-bits
  *
  * Descrição   : Processa os blocos de mensagem múltiplos de 512-bits utilizando
  *             o processo descrito no "method 1" do Memo US Secure Hash Algorithm 1 (SHA1)
  * Parâmetros  :
  *             sha1_info *context: contexto que armazenará todas as informações
  *                                  relativas ao bloco de mensagem sendo processado
  * Retorno     : Nenhum
  */
void sha1_hash_block(sha1_info *context);

 /*
  * Brief       : Reorganiza as entradas
  *
  * Descrição   : Rotaciona o conteúdo da variável word em n bits, dessa forma os n bits
  *               iniciais serão posicioados no final e o bit n+1 será o primeiro da nova
  *               word
  * Parâmetros  :
  *             uint32_t word: palavra a ser rotacionada
  *             uint8_t n: o número de bits que devem ser rotacionados
  * Retorno     : a palavra rotacionada
  */
uint32_t shar1_circular_shift(uint32_t word, uint8_t n);

 /*
  * Brief       : Escreve o hash em tela
  *
  * Descrição   : Escreve o hash em tela, mostrando cada um dos elementos do array
  *               separado por espaço
  * Parâmetros  :
  *             uint8_t* sha1_hash: hash a ser impresso
  * Retorno     : Nenhum
  */
void print_sha1_to_cmd(uint8_t* sha1_hash);

 /*
  * Brief       : Escreve o hash em arquivo
  *
  * Descrição   : Escreve o hash em arquivo, mostrando cada um dos elementos do array
  *               separado por espaço
  * Parâmetros  :
  *             uint8_t* sha1_hash: hash a ser impresso
  *             char *fname: arquivo onde o hash será impresso
  * Retorno     : Nenhum
  */
void print_sha1_to_file(uint8_t* sha1_hash, char *fname);

#endif
