#include <stdio.h>

#define i 0

//this function takes the text in in.txt and generates a program that prints it
//to generate the q0 function for quine0.c, copy the specification of q() and useful_fn() from quine0() into in.txt
//copy the q0() function from out.txt and place it in quine0.c immediately before q()

char src_descriptor[] = "in.txt";
char dst_descriptor[] = "out.txt";

void q(){
    FILE* src = fopen(src_descriptor, "r");
    FILE* dst = fopen(dst_descriptor, "w");
    fputs(
        "void q0(){\n\tFILE* dst = fopen(src_desc, \"w\");\n\tfputs(\""
    , dst);
    char next;
    next = getc(src);
    while(next!=EOF){   //parses the file
        if(next == 34){ //double quote
            putc(92, dst);  //forward slash
            putc(34, dst);  //double quote
            next = getc(src);
            while(next!=EOF){   //parses strings in the file
                if(next == 34){ //double quote
                    putc(92, dst);  //forward slash
                    putc(34, dst);  //double quote
                    break;  //this is the end quote, so exit here
                }
                else if(next == 92){    //escape character
                    putc(92, dst);  //forward slash
                    putc(92, dst);  //forward slash
                    next = getc(src);
                    if(next==EOF)   break;
                    else if(next == 34){ //double quote
                        putc(92, dst);
                        putc(34, dst);
                    }
                    else if(next == 92){
                        putc(92, dst);  //forward slash
                        putc(92, dst);  //forward slash
                    }
                    else{
                        putc(next, dst);
                    }
                }
                else if(next != 13 && next!=10){    //no line feeds or carriage returns! we want our string to be on one line
                    putc(next, dst);
                }
                next = getc(src);
            }
        }
        else if(next == 10){    //line feed
            putc(92, dst);  //forward slash
            putc(110, dst); //n
        }
        else if(next == 9){ //tab
            putc(92, dst);  //forward slash
            putc(116, dst); //t
        }
        else if(next == 92){    //forward slash
            putc(92, dst);    //escape character
            putc(92, dst);    //forward slash
        }
        else if(next != 13){    //no carriage returns!!!
            putc(next, dst);
        }
        next = getc(src);
    }
    fputs(
        "\", dst);\n\tfclose(dst);\n\treturn;\n}"
    , dst);
    fclose(src);
    fclose(dst);
    return;
}

int main(){
    q();
}