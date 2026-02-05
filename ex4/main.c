#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>


/*
    FOR     -> for(EXPR;EXPR;EXPR)BLOCK
    BLOCK   -> {}
    EXPR    -> TERM EXPR'
    EXPR'   -> +TERM EXPR' | -TERM EXPR' | e
    TERM    -> FACTOR TERM'
    TERM'   -> *FACTOR TERM' | /FACTOR TERM' | e
    FACTOR  -> id / num / (EXPR)
*/


char src[1000] = {};
int idx = 0;

void err() {
	printf("\e[31mParsing failed\e[0m\n");
	exit(1);
}

void expect(char c) {
	if(src[idx]==c) idx++;
	else err();
}

void FOR();
void BLOCK();
void EXPR();
void EXPR_prm();
void TERM();
void TERM_prm();
void FACTOR();

void FOR() {
	if(strncmp(src+idx, "for", 3)==0) {
		idx+=3;
		expect('(');
		EXPR();
		expect(';');
		EXPR();
		expect(';');
		EXPR();
		expect(')');
		BLOCK();
		printf("\e[32mParsing Succesful\e[");
	}
	else err();
}

void BLOCK() {
	expect('{');
	expect('}');
}

void EXPR() {
	TERM();
	EXPR_prm();
}

void EXPR_prm() {
	if(src[idx]=='+'||src[idx]=='-') {
		idx++;
		TERM();
		EXPR_prm();
	}
}

void TERM() {
	FACTOR();
	TERM_prm();
}

void TERM_prm() {
	if(src[idx]=='*'|| src[idx]=='/') {
		idx++;
		FACTOR();
		TERM_prm();
	}
}


void FACTOR() {
	if(isalnum(src[idx])) idx++;
	else {
		expect('(');
		EXPR();
		expect(')');
	}
}
int main() {
	scanf("%s", src);
	idx = 0;
	FOR();
	return 0;
}




