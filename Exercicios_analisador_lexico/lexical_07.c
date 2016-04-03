#include <stdio.h>
#include <stdlib.h>

int lexical_07(FILE* input){

    char l = fgetc(input);


    if(l == '+' || l == '-'){
        l = fgetc(input);
        goto S;
    }
    if(l >= 48 && l <= 57){
        l = fgetc(input);
        goto SN;
    }
    return 0;

    S:
        if(l >= 48 && l <= 57){
            l = fgetc(input);
            goto SN;
        }
        return 0;
    SN:
        if(l >= 48 && l <= 57){
            l = fgetc(input);
            goto SN;
        }
        if(l == ','){
            l = fgetc(input);
            goto SNV;
        }
        if(l == 'E'){
            l = fgetc(input);
            goto SNE;
        }
        if(l == ' ')
            return lexical_07(input);
        if(l == EOF)
            return 1;

        return 0;
    SNV:
        if(l >= 48 && l <= 57){
            l = fgetc(input);
            goto SNVN;
        }
        return 0;
    SNE:
        if(l >= 48 && l <= 57){
            l = fgetc(input);
            goto SNEN;
        }
        if(l == '+' || l == '-'){
            l = fgetc(input);
            goto SNES;
        }
        return 0;
    SNVN:
        if(l >= 48 && l <= 57){
            l = fgetc(input);
            goto SNVN;
        }
        if(l == 'E'){
            l = fgetc(input);
            goto SNE;
        }
        if(l == ' ')
            return lexical_07(input);
        if(l == EOF)
            return 1;
        return 0;
    SNES:
        if(l >= 48 && l <= 57){
            l = fgetc(input);
            goto SNEN;
        }
        return 0;
    SNEN:
        if(l >= 48 && l <= 57){
            l = fgetc(input);
            goto SNEN;
        }
        if(l == ' ')
            return lexical_07(input);
        if(l == EOF)
            return 1;
        return 0;
}
