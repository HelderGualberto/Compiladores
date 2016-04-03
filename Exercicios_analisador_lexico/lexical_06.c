#include <stdio.h>
#include <stdlib.h>

//GET REGULAR DEFINITION
// RETURN 0 TO NUMBERS, 1 TO CAPITAL LETTER AND 2 TO SMALL LETTER
int get_def(FILE* input){

    char l = fgetc(input);

    if(l >= 48 && l <= 57)
        return 0;

    if(l >= 65 && l <= 90)
        return 1;

    if(l >= 97 && l<= 122)
        return 2;
    if(l == '_')
        return -2;
    if(l == EOF)
        return -3;

    return -1;
}

int lexical_06(FILE* input){

    int def = get_def(input);


    if(def > 0){
        def = get_def(input);
        goto R2;
    }
    return 0;
    R2:
        if(def >= 0){
            def = get_def(input);
            goto R2;
        }
        if(def == -2){ //verify the _
            def = get_def(input);
            goto R3;
        }
        return 0;
    R3:
        if(def >= 0){ // Verify if is it letter, capital letter or number
            def = get_def(input);
            goto R3;
        }
        if(def == -3)//verify the EOF
            return 1;
        return 0;
}
