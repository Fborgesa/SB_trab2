/*
 *  Universidade de Brasília
 *  Instituto de Ciencias Exatas
 *  Departamento de Ciência da Computação
 *
 *  Software Básico - Turma A - 1/2016
 *
 *  Codificadores Binários
 *
 *  Grupo 3:
 *      - Carlos Joel Tavares da Silva  13/0007293
 *      - Felipe Barreto Fernandes      09/0112831
 *      - Felipe Borges Albuquerque     09/93972
 *      - Géssica Neves Sodré da Silva  11/0146115
 *      - Pedro da Costa Abreu Júnior   11/0018800
 *
 *  Arquivo fonte principal "main.c"
 *
 *  Copyright © 2016 UnB. All rights reserved.
 */
#include "..\include\md5.h"
#include <stdio.h>
#include <string.h>

#define OPT1(ac, av) (ac > 1 ? av[1][0] == '-' ? av[1][1] : '\0' : '\0')


// Mensagens de erro.
char *err[] = { "\nSintaxe errada. \n\
Utilize a opcao -h para obter ajuda ou rode o programa sem passar parametros.\n\n",
"\nFuncao nao implementada. Utilize a opcao -h para obter ajuda.\n\n"};

char *help = "\nSintaxe:\n \
main { -md5 | -sha1 | -crc32  } {arquivo de entrada} {arquivo de saida}\n\
\n\
-h Menu de ajuda.\n\
\n\
-md5 O Arquivo será codificado com md5.\n\
-sha1 O Arquivo será codificado com sha1.\n\
-crc O Arquivo será codificado com crc32\n\
\n";

void conversor(char *opt, char *a_entrada, char *a_saida){
    if(!strcmp(opt, "-h")){
        encode_md5(a_entrada, a_saida);
    }
    else if(!strcmp(opt, "-md5")){
        encode_md5(a_entrada, a_saida);
    }
    else if(!strcmp(opt, "-crc32")){
    }
}

int main(int argc, char **argv) {
    if(argc == 0){
        printf("%s", err[1]);

    }
    else{
        conversor(argv[1], argv[2], argv[3]);
    }
    return 0;
}

