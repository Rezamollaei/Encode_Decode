#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int encoding(FILE *fin, FILE *fout);
int decoding(FILE *fin, FILE *fout);

int main() {
    FILE *fp_in , *fp_out;
    int num_car;
    char choice , file_in[50],file_out[50];

    printf("encode ('C') or decode (D):  ");
    scanf("%c",&choice);

    switch (choice) {
        case 'C' :
            printf("input file name for encoding: ");
            scanf("%s",&file_in);

            printf("output file name for encoding:");
            scanf("%s" , &file_out);

            fp_in = fopen(file_in,"r");
            if (fp_in ==NULL){
                printf("error opening file\n");
                return 1;
            }
            fp_out = fopen(file_out,"w");
            if(fp_out==NULL){
                printf("error opening file\n");
                return 2;
            }
            num_car = encode(fp_in ,fp_out);
            fclose(fp_in);
            fclose(fp_out);

        case 'D':
            printf("input file name for decoding:");
            scanf("%s",&file_in);

            printf("output file name for decoding:");
            scanf("%s",&file_out);

            fp_in = fopen(file_in,"r");
            fp_out = fopen(file_out,"w");

            if(fp_in==NULL){
                printf("error opening file\n");
                return 3;
            }
            if(fp_out==NULL){
                printf("error opening file");
                return 4;
            }
            num_car = decode(fp_in,fp_out);
            fclose(fp_in);
            fclose(fp_out);

        default :
            printf("wrong answer");
            return 5;

    }
    if (num_car==0){
        printf("error");
    }else{
        printf("charecters printed: %d",num_car);
    }
    return 0;
}

int encode(FILE *fin ,FILE *fout){
    char ch , ch_prec;
    int num , flag , ch_cod;
    int counter=0 , num_car=0;

    ch_prec = '\n';
    while(!feof(fin)){
        ch = fgetc(fin);
        flag = 0;
        if(!feof(fin)){
            if(isdigit(ch)){
                num = (int)(ch) + counter;
                counter++;
                while(num >9){
                    num = num -10;
                }
                fputc(num,fout)
                num_car++;
                ch_prec =ch;
            }
            else if(isalpha(ch)){
                if(isalpha(ch_prec)){
                    if(islower((ch_prec))){
                        ch_cod = ch + ch_prec - 'a';
                    }
                    else{
                        ch_cod = ch + ch_prec -'A';
                    }
                    if(islower(ch) && ch_cod > 122){
                        flag = 1;
                    }
                    else if(isupper(ch) && ch_cod>90){
                        flag = 1;
                    }
                    if(flag){
                        ch_cod = ch_cod -26;
                    }
                    fprintf(fout,"%c",ch_cod);
                    num_car++;
                    ch_prec = ch_cod;
                }
                else{
                    fputc(ch,fout);
                    num_car++;
                    ch_prec = ch;
                }
            }
            else{
                fputc(ch,fout);
                num_car++;
                ch_prec =ch;
            }
        }
        else{
            fputc(ch,fout);
            num_car++;
            ch_prec = ch;
        }
    }
    return num_car;
}

int decode(FILE *fin , FILE *fout){
    char ch ,ch_prec;
    int num ,flag,ch_code;
    int counter=0 , num_car = 0;

    ch_prec = '\n';
    while(!feof(fin)) {
        ch = fgetc(fin);
        flag = 0;
        if (!feof(fin)) {
            if (isdigit(ch)) {
                num = (int) (ch) - counter;
                counter++;
                while (num < 0) {
                    num = num + 10;
                }
                fputc(num, fout);
                num_car++;
                ch_prec = ch;
            } else if (isalpha(ch)) {
                if (isalpha(ch_prec)) {
                    ch_code = ch - ch_prec + 'a';
                } else {
                    ch_code = ch - ch_prec + 'A';
                }
                if (islower(ch) && ch_code < 97) {
                    flag = 1;
                } else if (isupper(ch) && ch_code < 65) {
                    flag = 1;
                }
                if (flag) {
                    ch_code = ch_code + 26;
                }
                fprintf(fout, "%c", ch_code);
                num_car++;
                ch_prec = ch;
            } else {
                fputc(ch, fout);
                num_car++;
                ch_prec = ch;
            }
        } else {
            fputc(ch, fout);
            num_car++;
            ch_prec = ch;
        }
    }
    return num_car;
}