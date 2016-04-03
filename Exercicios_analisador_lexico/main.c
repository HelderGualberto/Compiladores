#include <stdio.h>
#include <stdlib.h>
#include "lexical_06.h"
#include "lexical_07.h"

/** FUNCTION TO VERIFY THE EXPRESSION: a(ab|ba)*c(a|b)c **/
//THAT FUNCTION RETURNS 0 IF THERE IS A WRONG WORD, AND 1 IF EVERYTHING IS OK
// IN ADDITION TO THE FUNCIOTN RETURN THE LINE AND THE WRONG WORD
int lexical_02(FILE* input, int* error_line,int* error_word){
    char l;

    l = fgetc(input);

    if(l == EOF)
        return 1;

    if(l == 'a'){
        l = fgetc(input);
        goto ABorBA;
    }
    return 0;

    ABorBA:
        if(l == 'b'){
            l = fgetc(input);
            goto BA;
        }
        if(l == 'a'){
            l = fgetc(input);
            goto AB;
        }
        if(l == 'c'){
            l = fgetc(input);
            goto AorB;
        }
        return 0;
    AB:
        if(l == 'b'){
            l = fgetc(input);
            goto ABorBA;
        }
        return 0;
    BA:
        if(l == 'a'){
            l = fgetc(input);
            goto ABorBA;
        }
        return 0;
    AorB:
        if(l == 'a' || l == 'b'){
            l = fgetc(input);
            goto C;
        }
        return 0;
    C:
        if(l == 'c'){
            l = fgetc(input);
            if(l == '\n'){
                *error_line += 1;
                *error_word = 1;
                return lexical_02(input,error_line,error_word);
            }
            else if(l == ' '){
                *error_word += 1;
                return lexical_02(input,error_line,error_word);
            }
            if(l == EOF)
                 return 1;
        }

        return 0;
}

/**FUNCTION THAT VERIFY IF ALL EXPRESSIONS HAS AT LEAST NUMBER PAIR OF 'a' OR 'b'**/
int lexical_03(FILE* input){
    char l = fgetc(input);

    if(l == EOF)
        return 1;

    PaPb:
        if(l == 'a'){
            l = fgetc(input);
            goto IaPb;
        }
        if(l == 'b'){
            l = fgetc(input);
            goto IbPa;
        }
        if(l == 'c'){
            l = fgetc(input);
            goto PaPb;
        }
        if(l == '\n' || l == ' ' || l == EOF)
            return 1;
        return 0;

    IaPb:
        if(l == 'a'){
            l = fgetc(input);
            goto PaPb;
        }
        if(l == 'b'){
            l = fgetc(input);
            goto IaIb;
        }
        if(l == 'c'){
            l = fgetc(input);
            goto IaPb;
        }
        if(l == '\n' || l == ' ' || l == EOF)
            return 1;
        return 0;
    IbPa:
        if(l == 'a'){
            l = fgetc(input);
            goto IaIb;
        }
        if(l == 'b'){
            l = fgetc(input);
            goto PaPb;
        }
         if(l == 'c'){
            l = fgetc(input);
            goto IbPa;
        }
        if(l == '\n' || l == ' ' || l == EOF)
            return 1;
        return 0;

    IaIb:
        if(l == 'a'){
            l = fgetc(input);
            goto IbPa;
        }
        if(l == 'b'){
            l = fgetc(input);
            goto IaPb;
        }
        if(l == 'c'){
            l = fgetc(input);
            goto IaIb;
        }
        return 0;
}

int lexical_4a(FILE* input){
    char l = fgetc(input);
    S0:
        if(l == 'a' || l == 'b'){
            l = fgetc(input);
            goto S0;
        }
        if(l == EOF)
            return 1;
        return 0;
}

int lexical_4b(FILE* input){
    char l = fgetc(input);

    Na1B:
        if(l == 'a'){
            l = fgetc(input);
            goto Na1B;
        }
        if(l == 'b'){
            l = fgetc(input);
            goto Na2B;
        }
        return 0;
    Na2B:
        if(l == 'a'){
            l = fgetc(input);
            goto Na2B;
        }
        if(l == 'b'){
            l = fgetc(input);
            goto Na3B;
        }
        return 0;
    Na3B:
        if(l == 'a'){
            l = fgetc(input);
            goto Na3B;
        }
        if(l == EOF)
            return 1;
        return 0;
}

int lexical_4c(FILE* input){
    char l = fgetc(input);

    Nb1A:
        if(l == 'a'){
            l = fgetc(input);
            goto Nb2A;
        }
        if(l == 'b'){
            l = fgetc(input);
            goto Nb1A;
        }
        return 0;
    Nb2A:
        if(l == 'a'){
            l = fgetc(input);
            goto Nb3A;
        }
        if(l == 'b'){
            l = fgetc(input);
            goto Nb1A;
        }
        return 0;
    Nb3A:
        if(l == 'a'){
            l = fgetc(input);
            goto AAA;
        }
        if(l == 'b'){
            l = fgetc(input);
            goto Nb1A;
        }
        return 0;
    AAA:
        if(l == 'b' || l == 'a'){
            l = fgetc(input);
            goto AAA;
        }
        if(l == EOF)
            return 1;
        return 0;
}

int lexical_4d(FILE* input){
    char l = fgetc(input);
    Nb1A:
        if(l == 'a'){
            l = fgetc(input);
            goto Nb2A;
        }
        if(l == 'b'){
            l = fgetc(input);
            goto Nb1A;
        }
        return 0;
    Nb2A:
        if(l == 'a'){
            l = fgetc(input);
            goto NbNa;
        }
        if(l == 'b'){
            l = fgetc(input);
            goto Nb1A;
        }
        return 0;
    NbNa:
        if(l == 'a'){
            l = fgetc(input);
            goto NbNa;
        }
        if(l == 'b'){
            l = fgetc(input);
            goto Nb1A;
        }
        if(l == EOF)
            return 1;
        return 0;
}

int lexical_05(FILE* input){
    char l = fgetc(input);

    S1:
        if(l == '1'){
            l = fgetc(input);
            goto S10;
        }
        if(l == '0'){
            l = fgetc(input);
            goto S1;
        }
        if(l == EOF)
            return 1;
        return 0;
    S10:
        if(l == '1'){
            l = fgetc(input);
            goto S10;
        }
        if(l == '0'){
            l = fgetc(input);
            goto S101;
        }
        if(l == EOF)
            return 1;
    S101:
        if(l == '1'){
            return 0;
        }
        if(l == '0'){
            l = fgetc(input);
            goto S1;
        }
        if(l == EOF){
            return 1;
        }
        return 0;
}

int main()
{
    FILE* input = fopen("d:\\automatos.txt","r");


    int result = lexical_07(input);
    printf("%d\n",result);

    /**TEST CASE FOR LEXICAL_02**/
    /*
        int el = 1,ew = 1;
        int result = lexical_02(input,&el,&ew);
        if(!result)
            printf("The error is in line: %d and the word: %d",el,ew);
        else
            printf("No errors founded");
    */
    return 0;
}
