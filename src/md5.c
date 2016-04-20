#include "..\include\md5.h"


void encode_md5(char *in, char *out)
{
    FILE *fp_in = NULL, *fp_out = NULL;
    char c1, c2, c;
    int i = 0;
    long filelen;
    int buf=0, bit_loc=0, val=0, cline_counter=0;

    if ((fp_in = fopen(in, "rb")) == NULL){
        printf("\nErro ao abrir o arquivo de entrada.\n\n");
        return;
    }

    if ((fp_out = fopen(out, "wb")) == NULL){
        printf("\nErro ao abrir o arquivo de saida.\n\n");
        return;
    }
}
