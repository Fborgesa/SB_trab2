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

#include <string.h>
#include "../include/CRC32.h"

#define OPT1(ac, av) (ac > 1 ? av[1][0] == '-' ? av[1] : "\0" : "\0")

#define OPT2(ac, av) (ac > 2 ? av[2][0] == '-' ? av[2][1] : '\0' : '\0')


// Mensagens de erro.
char *error[] = { "\nSintaxe errada. \n\
Utilize a opcao -h para obter ajuda ou rode o programa sem passar parametros.\n\n",
"\nOpção não implementada. Utilize a opcao -h para obter ajuda.\n\n"};

char *help = "\nSintaxe:\n\
crc -h Exibe o menu de ajuda.\n\
\n\
crc { -16 | -32 } { -g | -c } {nome_arquivo1} {nome_arquivo2}\n\
\n\
-16 O CRC gerado será o CRC16.\n\
-32 O CRC gerado será o CRC32.\n\
\n\
-g Gera o CRC de um arquivo de entrada (nome_arquivo1) e salva o CRC gerado\n\
   em um arquivo de saída (nome_arquivo2), além de imprimir o CRC gerado em\n\
   tela.\n\
-c Checa se o arquivo de entrada (nome_arquivo1) está integro, utilizando o\n\
   CRC disponibilizado em outro arquivo (nome_arquivo2).\n\
   O programa imprime em tela se o arquivo está integro ou se foi corrompido\n\
   e gera um arquivo de saída \"crc_check.txt\" com o CRC gerado sobre o\n\
   arquivo de entrada (nome_arquivo1).\n\
\n";

void param_cmd_line(int argc, char **argv) {
    char *aux = NULL;
    int opt1 = 0, opt2 = 0, crc32 = 0;

    aux = OPT1(argc, argv);
    if (strcmp(aux, "-h") == 0)
        opt1 = 'h';
    else if (strcmp(aux, "-32") == 0)
        opt1 = '3';
    else if (strcmp(aux, "-16") == 0)
        opt1 = '1';

    opt2 = OPT2(argc, argv);

    switch (opt1) {
        // Ajuda.
        case 'h':
            printf("%s", help);
            break;

        // CRC32.
        case '3':
            switch (opt2) {
                // Gerar.
                case 'g':
                    crc32 = generate_crc32(argv[3], argv[4]);
                    printf("\n%x\n\n", crc32);
                    break;

                // Checar.
                case 'c':
                    check_crc32(argv[3], argv[4]);
                    break;
                default:
                    printf("%s", error[1]);
                    break;
            }
            break;

        // CRC16.
        case '1':
            switch (opt2) {
                // Gerar.
                case '3':
                    break;

                // Checar.
                case '1':
                    break;

                default:
                    printf("%s", error[1]);
                    break;
            }
            break;

        default:
            printf("%s", error[0]);
            break;
    }
}

void ask_param() {
    char op1 = '\0', op2 = '\0', name_arq1[100] = {0}, name_arq2[100] = {0};
    int crc32 = 0;

    do {
        printf("Digite o CRC a ser usado.\n");
        printf("0 - Sair.\n");
        printf("1 - CRC16.\n");
        printf("2 - CRC32.\n");
        op1 = getchar();
        if (op1 == '0')
            exit(0);
    } while (op1 != '1' && op1 != '2');

    do {
        printf("Digite se deseja gerar o CRC ou checar a integridade de um arquivo.\n");
        printf("0 - Sair.\n");
        printf("1 - Gerar CRC.\n");
        printf("2 - Checar a integridade de um arquivo.\n");
        op2 = getchar();
        if (op2 == '0')
            exit(0);
    } while (op2 != '1' && op2 != '2');

    if (op2 == '1')
        printf("Digite o nome do arquivo que terá seu CRC calculado:\n");
    else if (op2 == '2')
        printf("Digite o nome do arquivo que terá sua integridade checada:\n");
    scanf("%s", name_arq1);

    if (op2 == '1') {
        printf("Digite o nome do arquivo de saída, onde o valor do CRC gerado\n");
        printf("será salvo:\n");
    }
    if (op2 == '2') {
        printf("Digite o nome do arquivo que possui o valor do CRC correspondente\n");
        printf("ao arquivo de entrada.\n");
    }
    scanf("%s", name_arq2);

    // Gerar CRC16.
    if (op1 == '1' && op2 == '1') {}

    // Checar integridade de um arquivo com CRC16.
    else if (op1 == '1' && op2 == '2') {}

    // Gerar CRC32.
    else if (op1 == '2' && op2 == '1') {
        crc32 = generate_crc32(name_arq1, name_arq2);
        printf("\n%x\n\n", crc32);
    }

    // Checar integridade de um arquivo com CRC32.
    else if (op1 == '2' && op2 == '2')
        check_crc32(name_arq1, name_arq2);
}

int main(int argc, char **argv) {
    if (argc == 1)
        ask_param();
    else
        param_cmd_line(argc, argv);
}
