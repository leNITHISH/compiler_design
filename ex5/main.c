#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>


/*
    IF      -> if(EXPR)BLOCK
    FOR     -> for(EXPR;EXPR;EXPR)BLOCK
    BLOCK   -> {FOR} | {IF} | EXPR
    EXPR    -> TERM EXPR'
    EXPR'   -> +TERM EXPR' | -TERM EXPR' | e
    TERM    -> FACTOR TERM'
    TERM'   -> *FACTOR TERM' | FACTOR TERM' | e
    FACTOR  -> id | num | (EXPR)
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

void S();
void IF();
void FOR();
void BLOCK();
void EXPR();
void EXPR_prm();
void TERM();
void TERM_prm();
void FACTOR();

void S(){
   if(strncmp(src+idx, "if", 2)==0){
       IF();
       return;
   } 
   else if(strncmp(src+idx, "for", 3)==0){
       FOR();
       return;
   }
   else EXPR();
   
}
void IF(){
    if(strncmp(src+idx, "if", 2)==0){
        idx+=2;
        expect('(');
        EXPR();
        expect(')');
        BLOCK();
    }
    else
        err();
}

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
	}
	else err();
}

void BLOCK() {
	expect('{');
	if(src[idx]!='}'){
    
       if(src[idx]=='f' && src[idx+1]=='o' && src[idx+2]=='r'){
           FOR();
           goto block_breaker;
       }else if(src[idx]=='i' && src[idx+1]=='f' ){
           IF();
           goto block_breaker;
       }
       EXPR();
	}
	block_breaker: expect('}');
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
	S();
	printf("\e[32mParsing Succesful\e[");
	return 0;
}




