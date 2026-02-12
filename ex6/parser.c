#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

// Helper to find index of a symbol in the lists
int get_index(char c, char *list, int count) {
    for (int i = 0; i < count; i++) {
        if (list[i] == c) return i;
    }
    return -1;
}

// Formats the output to match the expected trace
void print_row(char *stack, int top, char *input, int ip, char *action) {
    for (int i = 0; i <= top; i++) printf("%c", stack[i]);
    printf("\t\t\t");
    printf("%s\t\t\t", input + ip);
    printf("%s\n", action);
}

int main() {
    int ntc, tc;
    char NT[MAX], T[MAX];
    char table[MAX][MAX][MAX];

    // Gather Grammar Metadata
    printf("Enter number of non-terminals: ");
    scanf("%d", &ntc);
    printf("Enter non-terminals: ");
    for (int i = 0; i < ntc; i++) scanf(" %c", &NT[i]);

    printf("Enter number of terminals: ");
    scanf("%d", &tc);
    printf("Enter terminals (include $): ");
    for (int i = 0; i < tc; i++) scanf(" %c", &T[i]);

    // Fill the runtime parsing table
    printf("\nEnter LL(1) Parsing Table:\n");
    for (int i = 0; i < ntc; i++) {
        for (int j = 0; j < tc; j++) {
            printf("M[%c, %c] = ", NT[i], T[j]);
            scanf("%s", table[i][j]);
        }
    }

    char input[MAX];
    printf("\nEnter input string: ");
    scanf("%s", input);

    // Setup Stack and Input Pointer
    char stack[MAX];
    int top = -1;
    int ip = 0;

    stack[++top] = '$';   // Bottom marker
    stack[++top] = NT[0]; // Start symbol

    printf("\n%-20s %-20s %-20s\n", "Stack", "Input", "Action");
    printf("------------------------------------------------------------\n");

    while (top != -1) {
        char X = stack[top];
        char a = input[ip];

        if (X == a) {
            char act[MAX];
            sprintf(act, "Match %c", a);
            print_row(stack, top, input, ip, act);
            top--; 
            ip++;
        } 
        else if (X >= 'A' && X <= 'Z') { // Non-Terminal logic
            int r = get_index(X, NT, ntc);
            int c = get_index(a, T, tc);

            if (r == -1 || c == -1 || strcmp(table[r][c], "-") == 0) {
                printf("\nError: No rule in table. String Rejected.\n");
                return 0;
            }

            char *rhs = table[r][c];
            char act[MAX];
            sprintf(act, "Apply %c -> %s", X, rhs);
            print_row(stack, top, input, ip, act);

            top--; // Pop the Non-Terminal

            // Handle 'e' for epsilon
            if (strcmp(rhs, "e") != 0) {
                // Reverse Push
                for (int k = strlen(rhs) - 1; k >= 0; k--) {
                    stack[++top] = rhs[k];
                }
            }
        } 
        else {
            printf("\nError: Terminal mismatch. String Rejected.\n");
            return 0;
        }
    }

    if (input[ip] == '\0' || input[ip] == '$') printf("\nString Accepted\n");
    else printf("\nString Rejected: Extra input.\n");

    return 0;
}
