#include<stdio.h>

#define max 50
#define states 20
#define symbols 10

char* lhs[] = {"S'", "E", "E", "T", "F", "F"};
char* rhs[] = {"E", "E+T", "T", "T*F", "F", "(E)", "id"};

int prod_count = 7;

char* terminals[] = {"id", "+", "*", "(", ")", "$"};
char* nonterminals[] = {"E", "T", "F"};

int action[states][6];
int go_to[states][3];

void init_tables() {
	for(int i=0; i<states; i++) {
		for(int j=0; j<6; j++)
			action[i][j]=0;
		for(int j=0; j<3; j++)
			go_to[i][j]=-1;
	}
}

int follow_E[] = {1, 4, 5};
int follow_T[] = {1, 2, 4, 5};
int follow_F[] = {1, 2, 4, 5};

void build_table() {
	init_tables();

	action[0][0] = 5;
	action[0][3] = 4;
	go_to[0][0]  = 1;
	go_to[0][1]  = 2;
	go_to[0][2]  = 3;

	action[1][1] = 6;
	action[1][5] = -1;

	action[2][1] = -2;
	action[2][2] = 7;
	action[2][4] = -2;
	action[2][5] = -2;


	action[3][1] = -4;
	action[3][2] = -4;
	action[3][4] = -4;
	action[3][5] = -4;


	action[4][0] = 5;
	action[4][3] = 4;
	go_to[4][0] = 8;
	go_to[4][1] = 2;
	go_to[4][2] = 3;

	action[5][1] = -6;
	action[5][2] = -6;
	action[5][4] = -6;
	action[5][5] = -6;


	action[6][0] = 5;
	action[6][3] = 4;
	go_to[6][1] = 9;
	go_to[6][2] = 3;

	action[7][0] = 5;
	action[7][3] = 4;
	go_to[7][2] = 10;

	action[8][1] = 6;
	action[8][4] = 11;

	action[9][1] = -1;
	action[9][2] = 7;
	action[9][4] = -1;
	action[9][5] = -1;

	action[10][1] = -3;
	action[10][2] = -3;
	action[10][4] = -3;
	action[10][5] = -3;


	action[11][1] = -5;
	action[11][2] = -5;
	action[11][4] = -5;
	action[11][5] = -5;


}

void print_table() {
	printf("\n SLR Parse Table:\n");
	printf("State\tid\t+\t(\t)\t$\tE\tT\fF\n");

	for(int i=0; i<12; i++) {
		printf("%d\t", i);
		for(int  j =0; j<6; j++) {
			if(action[i][j]>0)
				printf("s%d\t", action[i][j]);
			else if(action[i][j]<0) {
				if(action[i][j]==-1)
					printf("acc\t");
				else
					printf("r%d\t", -action[i][j]);
			}
			else
				printf("-\t");
		}

		for(int j=0; j<3; j++)if(go_to[i][j]!=-1)
				printf("%d\t", go_to[i][j]);
			else
				printf("-\t");
		printf("\n");
	}
}

int main() {
	build_table();
	print_table();
	return 0;
}