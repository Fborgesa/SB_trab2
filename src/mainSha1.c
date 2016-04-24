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
 */

/*#include <string.h>
#include "../include/sha1.h"

int main(int argc, char **argv){
    // Manipulação de arquivos
    FILE *fp_in, *fp_out;
    char fname_in[] = "bench/amostra_h1.bin";
    char fname_out[] = "teste.txt";
    char *msg;
    int length;

    // Manipulação do hash
    sha1_info sha;
    uint8_t sha1_hash[HASH_SIZE];
    int err;

    if ((fp_in = fopen(fname_in, "r")) == NULL) {
        printf("\nErro ao abrir o arquivo de entrada.\n\n");
        exit(0);
    }

    if ((fp_out = fopen(fname_out, "w")) == NULL) {
        printf("\nErro ao abrir o arquivo de saída.\n\n");
        exit(0);
    }


    fseek(fp_in, 0, SEEK_END);
    length = ftell(fp_in);

    rewind(fp_in);
    msg = (char*)(malloc(length));
    fread(msg, 1, length, fp_in);

    //err = generate_sha1(&sha, (uint8_t*) msg, length, sha1_hash);
    //err = generate_sha1(&sha, msg, length, sha1_hash);


    //if (err){
    //    fprintf(stderr, "generate_sha1 Error %d.\n", err );
    //}else{
    //    print_hash_to_cmd(sha1_hash);
    //}

    fclose(fp_in);
    fclose(fp_out);

    return 0;
}*/

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/sha1.h"

int main(){
    sha1_info sha;
    int i, j, err;
    uint8_t sha1_hash[HASH_SIZE];
    const unsigned char *resultarray[2] = {"a9 99 3e 36 47 06 81 6a ba 3e 25 71 78 50 c2 6c 9c d0 d8 9d","f5 75 98 eb bd 8c b5 a0 ee 8e ba 51 bd 65 6a 2f ff a6 31 9b"};

    sha1_init(&sha);

    //err = generate_sha1(&sha, (const unsigned char *) "abc", 3);

    err = generate_sha1(&sha, (uint8_t*) "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopqrabcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopqr", 114, sha1_hash);
    if (err){
        fprintf(stderr, "generate_sha1 Error %d.\n", err );
    }else{
        print_hash_to_cmd(sha1_hash);
        //printf("\t%s\n", resultarray[0]);
        printf("\t%s\n", resultarray[1]);
    }

    return 0;
}

/*
int main(int argc, char **argv){
    sha1_info sha;
    uint8_t sha1_hash[HASH_SIZE];
    char *ar = argv[2], *msg;
    int err;
    int filelen;

    printf("\nargv1: %s\n", argv[1]);
    printf("\nargv2: %s\n", argv[2]);
    if(argc < 3){
        printf("Modo de uso: \n-a para entrar com um arquivo;\n-s para entrar com um arquivo a ser codificado\n");
        return 1;
    }
    if(strcmp(argv[1], "-a") == 0){
        printf("\nif\n");
        filelen = strlen(ar);
        err = generate_sha1(&sha, (uint8_t*) ar, filelen, sha1_hash);
    }else if(strcmp(argv[1], "-s") == 0){
        printf("\nelse\n");
        FILE *arq = fopen(ar, "rb");
        if(arq == NULL){
            printf("Erro ao abrir o arquivo\n");
            return 1;
        }
        fseek(arq, 0, SEEK_END);
        filelen = ftell(arq);
        rewind(arq);
        msg = (char*)(malloc(filelen));
        fread(msg, 1, filelen, arq);
        err = generate_sha1(&sha, (uint8_t*) msg, filelen, sha1_hash);
    }

    if (err){
        fprintf(stderr, "generate_sha1 Error %d.\n", err );
    }else{
        print_hash_to_cmd(sha1_hash);
    }

    return 0;
}*/
