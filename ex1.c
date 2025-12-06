#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int isSpecial(char c) {
	char* s = "(){},;=><+-*/";
	for(int i=0; i<13; i++)if(s[i]==c)return 1;
	return 0;
}
char* keywords[] = {
	"void", "main", "int", "NULL",
	"float", "char", "double", "if",
	"else", "for", "while", "return"
};
int isKeyword(char* s) {
	for(int i=0; i<12; i++)if(!strcmp(s, keywords[i]))return 1;
	return 0;
}
int main() {
	int c;
	c = getchar();
	char* buffer = (char*) malloc(100*sizeof(char));
	for(int i=0; i<100; i++)buffer[i]='\0';
	int b_idx = 0;

	char spl[100];
	int s_idx=0;

	char kew[100][30];
	int k_idx=0;

	char ident[100][30];
	int i_idx=0;

	while(c!=EOF) {
		if(isalnum(c))buffer[b_idx++]=c;

		else if(isSpecial(c)||isspace(c)) {
			if(b_idx>0) {
				buffer[b_idx]='\0';
				if(isKeyword(buffer))strcpy(kew[k_idx++], buffer);
				else strcpy(ident[i_idx++], buffer);
				b_idx=0;
			}
			if(isSpecial(c))spl[s_idx++]=c;
		}
		c = getchar();
	}
	if(b_idx>0) {
		buffer[b_idx]='\0';
		if(isKeyword(buffer))strcpy(kew[k_idx++], buffer);
		else strcpy(ident[i_idx++], buffer);
		b_idx=0;
	}
	printf("+-----------------+-----------------+-----------------+\n");
	printf("|     Keywords    |   Identifiers   |  Special Chars  |\n");
	printf("|-----------------+-----------------+-----------------|\n");
	int max = (i_idx>s_idx)?i_idx:s_idx;
	max = (k_idx>max)?k_idx:max;
	for(int i=0; i<max; i++)
		printf("| %-15s | %-15s | %-15c |\n",
		       (i<k_idx)?kew[i]:"",
		       (i<i_idx)?ident[i]:"",
		       (i<s_idx)?spl[i]:' '
		      );
    printf("+-----------------+-----------------+-----------------+\n");
    
	return 0;
}
