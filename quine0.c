#include <stdio.h>
#define i 0

char src_desc[] = "temp.txt";

//this is the "A" part of the quine. it prints the specification of q() and useful_fn
void q0(){
	FILE* dst = fopen(src_desc, "w");
	fputs("void q(){\n    char dst_desc[i+9];\n    sprintf(dst_desc, \"quine%d.c\", i+1);\n    FILE* src = fopen(src_desc, \"r\");\n    FILE* dst = fopen(dst_desc, \"w\");\n    fputs(\n        \"#include <stdio.h>\\n#define i \"\n        , dst\n    );\n    char i_str[i+1];\n    sprintf(i_str, \"%d\", i+1);\n    fputs(i_str, dst);\n    fputs(\n        \"\\n\\nchar src_desc[] = \\\"temp.txt\\\";\\n\\nvoid q0(){\\n\\tFILE* dst = fopen(src_desc, \\\"w\\\");\\n\\tfputs(\\\"\"\n    , dst);\n    char next;\n    next = getc(src);\n    while(next!=EOF){\n        if(next == 34){ //double quote\n            putc(92, dst);  //forward slash\n            putc(34, dst);  //double quote\n            next = getc(src);\n            while(next!=EOF){\n                if(next == 34){ //double quote\n                    putc(92, dst);  //forward slash\n                    putc(34, dst);  //double quote\n                    break;  //this is the end quote, so exit here\n                }\n                else if(next == 92){    //escape character\n                    putc(92, dst);  //forward slash\n                    putc(92, dst);  //forward slash\n                    next = getc(src);\n                    if(next==EOF)   break;\n                    else if(next == 34){ //double quote\n                        putc(92, dst);\n                        putc(34, dst);\n                    }\n                    else if(next == 92){\n                        putc(92, dst);  //forward slash\n                        putc(92, dst);  //forward slash\n                    }\n                    else{\n                        putc(next, dst);\n                    }\n                }\n                else if(next != 13 && next!=10){    //no line feeds or carriage returns! we want our string to be on one line\n                    putc(next, dst);\n                }\n                next = getc(src);\n            }\n        }\n        else if(next == 10){    //line feed\n            putc(92, dst);  //forward slash\n            putc(110, dst); //n\n        }\n        else if(next == 9){ //tab\n            putc(92, dst);  //forward slash\n            putc(116, dst); //t\n        }\n        else if(next == 92){    //forward slash\n            putc(92, dst);    //escape character\n            putc(92, dst);    //forward slash\n        }\n        else if(next != 13){    //no carriage returns!!!\n            putc(next, dst);\n        }\n        next = getc(src);\n    }\n    fputs(\n        \"\\\", dst);\\n\\tfclose(dst);\\n\\treturn;\\n}\\n\\n\"\n    , dst);\n\n    rewind(src);\n    next = getc(src);   //print the output of q0() - that is the function q()- to the new file\n    while(next != EOF){\n        putc(next, dst);\n        next = getc(src);\n    }\n    \n    fputs(\n        \"\\n\\nint main(){\\n\\tq0();\\n\\tq();\\n\\tuseful_fn();\\n\\treturn 0;\\n}\"\n    , dst);\n\n    fclose(src);\n    fclose(dst);\n    remove(src_desc);\n    return;\n}\n\nvoid useful_fn(){\n    printf(\"i = %d\\n\", i);\n    return;\n}", dst);
	fclose(dst);
	return;
}

//this is the "B" part of the quine. it creates the function q0() from the output of q0 and then creates the file quine<i+1>.c
void q(){
    char dst_desc[i+9];
    sprintf(dst_desc, "quine%d.c", i+1);
    FILE* src = fopen(src_desc, "r");
    FILE* dst = fopen(dst_desc, "w");
    fputs(
        "#include <stdio.h>\n#define i "
        , dst
    );
    char i_str[i+1];
    sprintf(i_str, "%d", i+1);
    fputs(i_str, dst);
    fputs(
        "\n\nchar src_desc[] = \"temp.txt\";\n\nvoid q0(){\n\tFILE* dst = fopen(src_desc, \"w\");\n\tfputs(\""
    , dst);
    char next;
    next = getc(src);
    while(next!=EOF){
        if(next == 34){ //double quote
            putc(92, dst);  //forward slash
            putc(34, dst);  //double quote
            next = getc(src);
            while(next!=EOF){
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
        "\", dst);\n\tfclose(dst);\n\treturn;\n}\n\n"
    , dst);

    rewind(src);
    next = getc(src);   //print the output of q0() - that is the function q()- to the new file
    while(next != EOF){
        putc(next, dst);
        next = getc(src);
    }
    
    fputs(
        "\n\nint main(){\n\tq0();\n\tq();\n\tuseful_fn();\n\treturn 0;\n}"
    , dst);

    fclose(src);
    fclose(dst);
    remove(src_desc);
    return;
}

//this function can be modified to make the quine do useful work. when modifying this section, q0() must also be modified
void useful_fn(){   
    printf("i = %d\n", i);
    return;
}

int main(){
    q0();
    q();
    useful_fn();
    return 0;
}