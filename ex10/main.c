#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/*
    grammar:
        E -> E+T
        E -> E-T
        E -> T 
        T -> T*F
        T -> T/F
        T -> F
        F -> id 
*/

char input[100];
int pos = 0;
int temp_count = 0;

char* newTemp(){
    char* out = (char*)malloc(10);
    sprintf(out, "t%d", temp_count++);
    return out;
}

char* E();
char* T();
char* F();
char* F(){
    char* out = (char*)malloc(10);
    if(isalnum(input[pos])){
        sprintf(out, "%c", input[pos]);
        pos++;
        return out;
    }
    printf("Syntax error, expect identifier\n");
    exit(1);
}

char* T(){
    char* p1 = F();
    while(input[pos]=='*' || input[pos]=='/'){
        char op = input[pos];
        pos++;
        char* p2 = F();
        char* t = newTemp();
        printf("%s = %s %c %s\n",t, p1, op, p2);
        strcpy(p1, t);
        free(p2);
    }
    return p1;
}

char* E(){
    char* p1 = T();
    while(input[pos]=='+' || input[pos]=='-'){
        char op = input[pos];
        pos++;
        char* p2 = T();
        char* t = newTemp();
        printf("%s = %s %c %s\n", t, p1, op, p2);
        strcpy(p1, t);
        free(p2);
    }
    return p1;
}

int main(){
    scanf("%s", input);
    char* res = E();
    free(res);
    return 0;
}
