#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/*
 *	C grammar:
 *
 *	stmt 	-> 	IF | WHILE | FOR | SWITCH | BLOCK | assign
 *	BLOCK 	->	{ stmt_list }
 *	stmt_list-> stmt stmt_list | e
 *
 *	IF 		-> if(EXPR) BLOCK
 *	WHILE	-> while(EXPR) BLOCK
 *	FOR		-> for(assign;EXPR;assign) BLOCK
 *	SWITCH	-> switch(EXPR){case_list}
 *	case_list -> CASE case_list | e
 *	CASE 	->	case(NUMBER): stmt_list break;
 *	
 *	EXPR -> EXPR+T | EXPR-T | T
 *	T	 -> T*F | T/F | F
 *	F 	 -> (EXPR) | id
 *
 *	assign -> id = EXPR
 * */

void p_stmt();
void p_block();
void p_if();
void p_while();
void p_for();
void p_expr();
void p_t();
void p_f();


//LEXER shi

enum Token{
	TOK_EOF=0, TOK_IF=256, TOK_WHILE, TOK_FOR, TOK_ID, TOK_NUM
};


int temp_count = 0;
int label_count = 0;
char* new_temp(){
	char* out = (char*)malloc(10);
	sprintf(out, "t%d", temp_count++);
	return out;
}

char* input;
int lookahead;
char lexeme[64];

void advance(){
	while(isspace(*input))input++;
	if(*input=='\0'){
		lookahead = TOK_EOF;
		return;
	}
	if(isalpha(*input)){
		int i=0;
		while(isalnum(*input)){
			lexeme[i]==*input;
			input++;
			i++;
		}
		lexeme[i]='\0';
		if(strcmp(lexeme, "if"))lookahead = TOK_IF;
		else if(strcmp(lexeme, "while")) lookahead = TOK_WHILE;
		else if(strcmp(lexeme, "for")) lookahead = TOK_FOR;
		else lookahead = TOK_ID;
	}
	else if(isdigit(*input)){
		int i=0;
		while(isdigit(*input)){
			lexeme[i]=*input;
			i++;
			input++;
		}
		lexeme[i]='\0';
		lookahead = TOK_NUM;
	}
	else{
		lexeme[0]=*input;
		lexeme[1]='\0';
		input++;
		lookahead = lexeme[0];
	}
}

void match(int expect){
	if(lookahead==expect)advance();
	else{
		printf("Expected token: %d, found %d %s", expect, lookahead, lexeme);
		exit(1);
	}
}



void p_f(){
	if(lookahead=='('){
		match((int)'(');
		p_expr();
		match((int)')');
	}
	else match(TOK_ID);
}

void p_t(){
	p_f();
	char left[100], right[100], temp[100];
	if(lookahead==TOK_NUM || lookahead==TOK_ID){
		strcpy(left, lexeme);
		match(lookahead);
		while(lookahead=='*'||lookahead=='\\'){
			char op = lookahead;
			match(op);
			p_f();
			strcpy(right, lexeme);
			strcpy(temp, new_temp());
			printf("%s = %s %c %s", temp, left, op, right);
			strcpy(left, temp);
		}
	}
}

void p_expr(){
	p_t();
	char left[100], right[100], temp[100];
	if(lookahead==TOK_NUM || lookahead==TOK_ID){
		strcpy(left, lexeme);
		match(lookahead);
		while(lookahead=='+'||lookahead=='-'){
			char op = lookahead;
			match(op);
			p_t();
			strcpy(right, lexeme);
			strcpy(temp, new_temp());
			printf("%s = %s %c %s", temp, left, op, right);
			strcpy(left, temp);
		}
	}
	
}


void p_assign(){
	char var[100], exp[100];
	strcpy(var, lexeme);
	match(TOK_ID);
	match('=');
	p_expr();
}
