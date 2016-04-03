#include <stdio.h>
#include <stdlib.h>

/** Máquina de estádo para automato onde so ocorra presenças pares da letra 'a' **/

int automacheck(char *str){
    S0:{
        if(*str == 'a'){
            str++;
            goto S1;
        }
        if(*str == 'b'){
            str++;
            goto S0;
        }
        return 1;
    }

    S1:{
        if(*str == 'a'){
            str++;
            goto S0;
        }

        if(*str == 'b'){
            str++;
            goto S1;
        }
        return 0;
    }
}


int main()
{
    char* str = "aaaaaaaaaaaabbbbbabababababbbababab";

    int result = automacheck(str);
    printf("%d",result);

    return 0;
}
