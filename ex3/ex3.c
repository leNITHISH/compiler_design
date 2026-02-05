#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
/*
    E-> TE'
    E'-> +TE' | -TE' | e
    T-> FT'
    T' -> *FT' | /FT' | E
    F-> (E) | id | num
*/

char input[1000];
int i_idx = 0;
int err=0;
int expect(char c){
    return input[i_idx]==c?1:0;
}

void T();
void E_prm();
void F();
void T_prm();

void E(){
    T();
    E_prm();
}

void E_prm(){
    if(expect('+') || expect('-')){
        i_idx++;
        T();
        E_prm();
    }    
}

void T(){
    F();
    T_prm();
}

void T_prm(){
    if(expect('*')||expect('/')){
        i_idx++;
        F();
        T_prm();
    }
}

void F(){
    if(expect('(')){
        i_idx++;
        E();
        if(expect(')')) i_idx++;
        else err=1;
    }
    else if(isalnum(input[i_idx]))
        while(isalnum(input[i_idx]))
            i_idx++;
    
    else err=1;
    
}


int main(){
    FILE *fp = fopen("input.txt", "r");
    if(fp==NULL)return 1;
    while(fgets(input, sizeof(input), fp)){
        input[strcspn(input, "\n")] = 0;
        if(!strlen(input))continue;
        i_idx=0;
        err = 0;
        printf("%-20s\t->\t", input);
        E();
        if(!err && input[i_idx]=='\0')
            printf("\e[48;5;154mParsing Successful\e[0m\n");
        else printf("\e[48;5;196mParsing Failed    \e[0m\n");
    }
    fclose(fp);
    return 0;
}
