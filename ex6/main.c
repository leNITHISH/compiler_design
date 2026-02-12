#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

typedef struct{
	char str[512];
	size_t len;
} String;

String get_entry(){
	String s;
	scanf("%s", s.str);
	s.len = strlen(s.str);
	return s;
}

int is_non_empty_definition(String s){
	if(s.len==1&&s.str[0]=='-')return 0;
	return 1;
}

int main(){
	int ntc, tc;
	printf("Enter #(non-terminals): ");
	scanf("%d", &ntc);
	printf("Enter non-terminals: ");
	char non_terms[ntc];
	for(int i=0;i<ntc;i++)scanf("%c ", non_terms+i);
	printf("\nEnter #(terminals): ");
	scanf("%d", &tc);
	printf("Enter terminals: ");
	char terms[tc];
	for(int i=0;i<tc;i++)scanf("%c ", terms+i);
	printf("\n");
	
	String M[tc][ntc];

	for(int i=0;i<tc;i++){
		for(int j=0;j<ntc;j++){
			printf("M[%c, %c] = ", non_terms[j], terms[i]);
			M[i][j] = get_entry();
		}
		printf("\n");
	}
	
	String input = get_entry();
	ToDo("Stack Shi");

	return 0;
}

