#include<stdio.h>
#include<ctype.h>
#include<string.h>
char s[100];
int i=0;

int E();
int T();
int F();

int E(){
    int val = T();
    while(s[i]=='+' || s[i]=='-'){
        if(s[i]=='+'){
            i++;
            val+=T();
        }
        else if(s[i]=='-'){
            i++;
            val-=T();
        }
    }
    
    return val;
}

int T(){
    int val = F();
    while(s[i]=='*' || s[i]=='/'){
        if(s[i]=='*'){
            i++;
            val*=F();
        }
        else if(s[i]=='/'){
            i++;
            val/=F();
        }
    }
    return val;
}

int F(){
    int val = 0;
    if(s[i]=='('){
        i++;
        val = E();
        if(s[i]==')')i++;
    }
    else if(isdigit(s[i])){
        while(isdigit(s[i])){
            val = val*10 + (s[i]-'0');
            i++;
        }
    }
    else{
        printf("Syn err\n");
        return 0;
    }
    return val;
}

int main(){
    printf("Enter Input string: ");
    scanf("%s", s);
    //strcpy("4+5", s);
    int n = E();
    printf("%d", n);
    return 0;
}