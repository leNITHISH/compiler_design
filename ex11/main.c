#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX 100

typedef struct {
	char res[10], op1[10], op2[10], op[5];
	int dead;
} Inst;


int is_val(char* s) {
	for(int i=0; s[i]; i++)if(!isdigit(s[i]))return 0;
	return 1;
}

int main(){
    Inst p[100];
    int n = 0, changed;
    char line[256];
    while(fgets(line, sizeof(line), stdin)){
        if(strncmp(line, "END", 3)==0)break;
        int args = sscanf(line, "%s = %s %s %s",p[n].res, p[n].op1, p[n].op, p[n].op2);
        if(args == 2){
            strcpy(p[n].op, "");
            strcpy(p[n].op2, "");
        }
        p[n].dead = 0;
        n++;
    }
    do{
        changed = 0;
        for(int i=0;i<n;i++){
            if(p[i].dead) continue;
            
            if(strlen(p[i].op)>0){
                if(is_val(p[i].op1) && is_val(p[i].op2)){
                    int v1 = atoi(p[i].op1), v2 = atoi(p[i].op2), val= 0;
                    if(p[i].op[0]=='+') val = v1+v2;
                    else if(p[i].op[0] == '-')val = v1-v2;
                    else if(p[i].op[0] == '*')val = v1*v2;
                    else if(p[i].op[0] == '/')val = v1/v2;
                    sprintf(p[i].op1, "%d", val);
                    strcpy(p[i].op, "");
                    strcpy(p[i].op2, "");
                    changed = 1;
                }
                else if(strcmp(p[i].op, "+")==0){
                    if(strcmp(p[i].op2, "0")==0){
                        strcpy(p[i].op, "");
                        changed = 1;
                    }else if(strcmp(p[i].op1, "0")==0){
                        strcpy(p[i].op1, p[i].op2);
                        strcpy(p[i].op, "");
                        changed = 1;
                    }
                }
                else if(strcmp(p[i].op, "*")==0){
                    if(strcmp(p[i].op2, "1")==0){
                        strcpy(p[i].op, "");
                        changed = 1;
                    }
                    else if(strcmp(p[i].op1, "1")==0){
                        strcpy(p[i].op1, p[i].op2);
                        strcpy(p[i].op, "");
                        changed = 1;
                    }
                    else if(strcmp(p[i].op2, "0")==0 || strcmp(p[i].op1, "0")==0){
                        strcpy(p[i].op1, "0");
                        strcpy(p[i].op, "");
                        changed = 1;
                    }
                }
            }
            if(strlen(p[i].op)==0){
                for(int j=i+1;j<n;j++){
                    if(strcmp(p[j].op1, p[i].res)==0){
                        strcpy(p[j].op1, p[i].op1);
                        changed = 1;
                    }
                    if(strcmp(p[j].op2, p[i].res) == 0){
                        strcpy(p[j].op2, p[i].op1);
                        changed = 1;
                    }
                }
            }
            
            if(strlen(p[i].op)>0){
                for(int j=i+1;j<n;j++){
                    if(!p[j].dead && strcmp(p[i].op1, p[j].op1)==0 && strcmp(p[i].op, p[j].op)==0 && strcmp(p[i].op2, p[j].op2)==0){
                        strcpy(p[j].op1, p[i].res);
                        strcpy(p[j].op, "");
                        strcpy(p[j].op2, "");
                        changed  = 1;
                    }
                }
            }
        }
        for(int i=0;i<n;i++){
            if(p[i].dead) continue;
            int used = 0;
            for(int j=i+1;j<n;j++){
                if(!p[j].dead && (strcmp(p[i].res, p[j].op1)==0 || strcmp(p[i].res, p[j].op2) == 0)){
                    used = 1;
                    break;
                }
            }
            if(strlen(p[i].op)==0 && strcmp(p[i].res, p[i].op1)==0){
                p[i].dead = 1;
                changed = 1;
            }
            else if(strlen(p[i].op)==0 && !is_val(p[i].op1)&& !used){
                p[i].dead = 1;
                changed = 1;
            }
        }
    } while(changed);
    
    for(int i=0;i<n;i++){
        if(!p[i].dead){
            if(strlen(p[i].op) > 0) printf("%s = %s %s %s\n", p[i].res, p[i].op1, p[i].op, p[i].op2);
            else printf("%s = %s\n", p[i].res, p[i].op1);
        }
    }
    return 0;
}