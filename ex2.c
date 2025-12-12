#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


enum toktype {
	IDENTIFIER,
	NUMBER,
	OPERATOR,
	RELATIONAL,
	KEYWORD,
	OTHERS,
	ENDOFFILE
};

struct Token {
	enum toktype type;
	char token[100];
};

char* tokmap[] = {"Identifier", "Number", "Arithmetic Operator", "Relational Operator", "Keyword", "Others", "EOF"};

void printtok(struct Token t) {
	printf("\t%s\t|\t%s\n", t.token, tokmap[t.type]);
}


int isnum(struct Token t) {
	char* c = t.token;
	if(strlen(c)==0 || !isdigit(c[0]))return 0;
	int n = strlen(c);
	for(int i=0; i<n; i++)if(!isdigit(c[i]))return 0;

	return 1;
}

int iskew(char* c) {
	const char* kewords[] = {
		"int", "float", "double", "main",
		"bool", "return", "char", "struct",
		"void", "if", "else"
	};
	int n = 11;
	for(int i=0; i<n; i++)if(!strcmp(c, kewords[i]))return 1;

	return 0;
}




struct Token gettok(FILE *fp) {
	struct Token t;
	strcpy(t.token, "");

	int c = fgetc(fp);
	while (c!=EOF && isspace(c)) c = fgetc(fp);

	if(c==EOF) {
		t.type = ENDOFFILE;
		return t;
	}

	if(isalpha(c)) {
		int i=0;
		while(isalnum(c)||c=='_') {
			t.token[i++]=c;
			c=fgetc(fp);
		}
		t.token[i]='\0';
		ungetc(c, fp);

		if(iskew(t.token))t.type=KEYWORD;
		else t.type = IDENTIFIER;
		return t;
	}

	if(isdigit(c)) {
		int i=0;

		while(isdigit(c)|| c=='.') {
			t.token[i++]=c;
			c = fgetc(fp);
		}
		t.token[i]='\0';
		ungetc(c, fp);
		t.type = NUMBER;
		return t;
	}

	if(c=='>'||c=='<'||c=='='||c=='!') {
		t.token[0] = c;
		int next = fgetc(fp);
		if(next =='=') {
			t.token[1]='=';
			t.token[2]='\0';
			t.type = RELATIONAL;
		}
		else {
			ungetc(next, fp);
			t.token[1]='\0';
			if(c=='=')t.type=OTHERS;
			else t.type = RELATIONAL;
		}
		return t;
	}
	if(strchr("+*/-", c)) {
		t.token[0]=c;
		t.token[1]='\0';
		t.type=OPERATOR;
		return t;
	}

	t.token[0]=c;
	t.token[1]='\0';
	t.type=OTHERS;
	return t;
}

int main() {
	FILE *fp = fopen("code.c", "r");
	if(fp==NULL) {
		printf("lmao");
		exit(1);
	}

	char unique[100][100];
	int count = 0;

	printf("\tToken\t|\tType\n----------------+--------------------------\n");
	while("truelol") {
		struct Token t = gettok(fp);

		if(t.type == ENDOFFILE)break;
		if(t.type == OPERATOR || t.type == RELATIONAL || t.type == NUMBER || t.type == IDENTIFIER)
			printtok(t);
		if(t.type==IDENTIFIER) {
			int found = 0;
			for(int i=0; i<count; i++)if(!strcmp(unique[i], t.token)) {
					found  = 1;
					break;
				}

			if(!found)strcpy(unique[count++], t.token);
		}

	}

	printf("----------------+--------------------------\nUnique Identifier: %d\nList: ", count);

	for(int i=0; i<count; i++)
		printf("%s%s", unique[i], (i<count-1)?", ":"\n");
	fclose(fp);
	return 0;
}
