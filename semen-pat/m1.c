#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

/*
 * E->E+T | T
 * T->T*F | F
 * F->(E) | id
*/

int F();
int T();
int E();
void err();
char s[1000]={};
int i = 0;

int F(){
	int val=0;
	if(s[i]=='('){
		i++;
		val = E();
		if(s[i]!=')')err();
		else i++;
	}
	else if(isdigit(s[i]))while(isdigit(s[i])){
		val=val*10+(s[i]-'0');
		i++;
	}
	else err();
	return val;
}

int T(){
	int var = F();
	while(s[i]=='*' || s[i]=='/'){
		i++;
		if(s[i]=='*')
			var*=F();
		else
			var/=F();
	}
	return var;
}

int E(){
	int var = T();
	while(s[i]=='+' || s[i]=='-'){
		i++;
		if(s[i]=='+')
			var+=T();
		else
			var-=T();
	}
	return var;
}

void err(){
	printf("Nah bro!");
	exit(0);
}


int main(){
	printf("Enter string: ");
	scanf("%s", s);
	int var = E();
	printf("Evaluated value: %d\n", var);
	return 0;
}
