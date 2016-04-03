#include <stdio.h>
#include <stdlib.h>

void next_line(FILE* _file){
    while(fgetc(_file)!='\n');
    return;
}
int main()
{
    FILE* input;
    FILE* output;
    input = fopen("D:\\in_code.c","r");
    output = fopen("D:\\out_code.c","w");

    char lexema;

    while(1){
        lexema = fgetc(input);

        if(lexema == '\n'){
            lexema = fgetc(input);

            while(lexema == '\n'){lexema = fgetc(input);}
                putc('\n',output);
        }

        if(lexema == EOF)
            break;

        if(lexema == '/'){
            lexema = fgetc(input);
            if(lexema == '/'){
                next_line(input);
                putc('\n',output);
            }
            else if(lexema == '*'){
                while(1){
                    if(fgetc(input) == '*'){
                        if(fgetc(input) == '/')
                            break;
                    }
                }
            }
            else{
                putc('/',output);
                putc(lexema,output);
            }
        }
        else{
            putc(lexema,output);
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}
