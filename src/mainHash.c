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
#include "../include/md5.h"

int main(int argc, char **argv){
    char *msg = argv[1];
    int i;
    uint8_t result[16];

    if(argc < 2){
        printf("Utilize chamando um programa e provendo uma string como argumento");
        return 1;
    }
    md5((uint8_t*) msg, result);

    // display result
    for (i = 0; i < 16; i++)
        printf("%2.2x", result[i]);

    return 0;


}
