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

#if _WIN32
    #include "..\include\md5.h"
    #include "..\include\sha1.h"
#else
    #include "../include/md5.h"
    #include "../include/sha1.h"
#endif

#define OPT1(ac, av) (ac > 1 ? av[1][0] == '-' ? av[1] : "\0" : "\0")

// Mensagens de erro.
char *error[] = { "\nSintaxe errada. \n\
Utilize a opcao -h para obter ajuda ou rode o programa sem passar parametros.\n\n",
"\nOpção não implementada. Utilize a opcao -h para obter ajuda.\n\n"};

char *help = "\nSintaxe:\n\
hash -h Exibe o menu de ajuda.\n\
\n\
hash { -sha1 | -md5 } {nome_arquivo1} {nome_arquivo2}\n\
\n\
-sha1 O hash gerado será o SHA1.\n\
-md5 O hash gerado será o MD5.\n\
\n\
O hash será gerado sobre o arquivo \"nome_arquivo1\" e será salvo no arquivo\n\
\"nome_arquivo2\".\n\
\n";

void param_cmd_line(int argc, char **argv) {
    sha1_info sha;
    uint8_t sha1_hash[HASH_SIZE], md5_hash[16];
    char *aux = NULL;
    int opt1 = 0, err = 0;

    aux = OPT1(argc, argv);
    if (strcmp(aux, "-h") == 0)
        opt1 = 'h';
    else if (strcmp(aux, "-sha1") == 0)
        opt1 = '1';
    else if (strcmp(aux, "-md5") == 0)
        opt1 = '2';

    switch (opt1) {
        // Ajuda.
        case 'h':
            printf("%s", help);
            break;

        // SHA-1
        case '1':
            sha1_init(&sha);
            err = generate_sha1(&sha, argv[2], sha1_hash);
            if (err){
                fprintf(stderr, "generate_sha1 Error %d.\n", err );
            }else{
                print_sha1_to_cmd(sha1_hash);
                print_sha1_to_file(sha1_hash, argv[3]);
            }
            break;

        // MD5
        case '2':
            err = call_md5(argv[2], md5_hash);
            if (err){
                fprintf(stderr, "call_md5 Error %d.\n", err );
            }else{
                print_md5_to_cmd(md5_hash);
                print_md5_to_file(md5_hash, argv[3]);
            }
            break;

        default:
            printf("%s", error[0]);
            break;
    }
}

// void ask_param() {
//     char op1 = '\0', op2 = '\0', name_arq1[100] = {0}, name_arq2[100] = {0};
//     int crc32 = 0;
//
//     do {
//         printf("Digite o CRC a ser usado.\n");
//         printf("0 - Sair.\n");
//         printf("1 - CRC16.\n");
//         printf("2 - CRC32.\n");
//         op1 = getchar();
//         if (op1 == '0')
//             exit(0);
//     } while (op1 != '1' && op1 != '2');
//
//     do {
//         printf("Digite se deseja gerar o CRC ou checar a integridade de um arquivo.\n");
//         printf("0 - Sair.\n");
//         printf("1 - Gerar CRC.\n");
//         printf("2 - Checar a integridade de um arquivo.\n");
//         op2 = getchar();
//         if (op2 == '0')
//             exit(0);
//     } while (op2 != '1' && op2 != '2');
//
//     if (op2 == '1')
//         printf("Digite o nome do arquivo que terá seu CRC calculado:\n");
//     else if (op2 == '2')
//         printf("Digite o nome do arquivo que terá sua integridade checada:\n");
//     scanf("%s", name_arq1);
//
//     if (op2 == '1') {
//         printf("Digite o nome do arquivo de saída, onde o valor do CRC gerado\n");
//         printf("será salvo:\n");
//     }
//     if (op2 == '2') {
//         printf("Digite o nome do arquivo que possui o valor do CRC correspondente\n");
//         printf("ao arquivo de entrada.\n");
//     }
//     scanf("%s", name_arq2);
//
//     // Gerar CRC16.
//     if (op1 == '1' && op2 == '1') {}
//
//     // Checar integridade de um arquivo com CRC16.
//     else if (op1 == '1' && op2 == '2') {}
//
//     // Gerar CRC32.
//     else if (op1 == '2' && op2 == '1') {
//         crc32 = generate_crc32(name_arq1, name_arq2);
//         printf("\n%x\n\n", crc32);
//     }
//
//     // Checar integridade de um arquivo com CRC32.
//     else if (op1 == '2' && op2 == '2')
//         check_crc32(name_arq1, name_arq2);
// }

int main(int argc, char **argv) {
    if (argc == 1) {}
        //ask_param();
    else
        param_cmd_line(argc, argv);
}
