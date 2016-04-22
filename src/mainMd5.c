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
#if _WIN32
    #include "..\include\md5.h"
#else
    #include "../include/md5.h"
#endif

int main(int argc, char **argv){
    char *ar = argv[2], *msg;
    int i;
    int filelen;
    uint8_t result[16];

    if(argc < 3){
        printf("Modo de uso: \n-a para entrar com um arquivo;\n-s para entrar com um arquivo a ser codificado\n");
        return 1;
    }
    if(strcmp(argv[1], "-a")){
        filelen = strlen(ar);
        md5((uint8_t*) ar, filelen, result);
    }else if(strcmp(argv[1], "-s")){
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
        printf("%s\n", ar, filelen);
        md5((uint8_t*) msg, filelen, result);
    }
    // display result
    for (i = 0; i < 16; i++)
        printf("%2.2x", result[i]);

    printf("\n");
    return 0;


}
