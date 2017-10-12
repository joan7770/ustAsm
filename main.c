//	main.c
//  assembler
//	Joan Marin-Romero
//
//	CISC 340
//	Project 1
//	uint32_t output

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

struct label{
	int location;
	char *label;
};

int pass1(FILE *code, struct label labeltable[], int nooflabels){
	char line[100];
	char *token = NULL;
	char *op1;
	int lineNumber = 0;
	char* temp;
	while(fgets(line,sizeof line,code)!= NULL){
		token = strtok(line," \t\n");
		
		if (strcmp(token,"add") != 0 && strcmp(token,"nand") != 0 && strcmp(token,"lw") != 0 && strcmp(token,"sw") != 0 && strcmp(token,"beq") != 0 && strcmp(token,"jalr") != 0&& strcmp(token,"halt") != 0 && strcmp(token,"noop") != 0 && strcmp(token,".fill") != 0) {
			//  label encounter
			temp = (char*) malloc(sizeof(token));
			strcpy(temp,token);
			token = strtok(NULL," \t\n");
			
			if(strcmp(token,".fill") == 0){
				token = strtok(NULL," \t\n");
				labeltable[nooflabels].label = temp;
				labeltable[nooflabels].location = (int) strtol(token,NULL,10);
				nooflabels++;
			}else{
				labeltable[nooflabels].location = lineNumber;
				op1 = (char*) malloc(sizeof(token));
				strcpy(op1,temp);
				labeltable[nooflabels].label=op1;
				nooflabels++;
			}
		}
		lineNumber++;
	}
	return nooflabels;
}

void pass2(FILE *code, struct label labeltable[], int nooflabels){
	char line[100];
	char *token = NULL;
	int lineNumber = 0;
	char* opcode;
	int type; // 0 =R, 1= I, 2 = J, 3 = O
	int r1, r2, r3;
	uint32_t command = 0;
	
	while(fgets(line,sizeof line,code)!= NULL){
		token = strtok(line," \t\n");
	start:
		if (strcmp(token,"add") == 0){ //add
			opcode = "000";
			type = 0;
			
			
		} //add
		
		else if(strcmp(token,"nand") == 0) {
			opcode = "001";
			type = 0;
	

		}//nand
		
		else if(strcmp(token,"lw") == 0){//lw
			opcode = "010";
			type = 1;
			printf("%s ",token);
			//r1
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r1 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < nooflabels + 1 && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r1 = lineNumber - labeltable[i].location;
					}
				}
			}
			
			//r2
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r2 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < nooflabels + 1 && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r2 = lineNumber - labeltable[i].location;
					}
				}
			}
			
			//r3
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r3 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < nooflabels + 1 && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r3 = labeltable[i].location - (lineNumber + 1);
					}
				}
			}
			printf("%d %d %d\n", r1, r2, r3);
		}//lw
			
		else if(strcmp(token,"sw") == 0){ // sw
			opcode = "011";
			type = 1;
			

		}//sw
			
		else if(strcmp(token,"beq") == 0){// beq
			opcode = "100";
			type = 1;
			printf("%s ", token);
			//r1
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r1 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < nooflabels + 1 && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r1 = lineNumber - labeltable[i].location;
					}
				}
			}
			
			//r2
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r2 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < nooflabels + 1 && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r2 = lineNumber - labeltable[i].location;
					}
				}
			}
			
			//r3
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r3 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < nooflabels + 1 && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r3 = labeltable[i].location - (lineNumber + 1);
					}
				}
			}
			printf("%d %d %d\n", r1, r2, r3);
		}//beq
			
		else if(strcmp(token,"jalr") == 0){// jalr
			opcode = "101";
			type = 2;
			token=strtok(NULL," \t\n");
		}//jalr
		
		else if (strcmp(token,"halt") == 0){//halt
			opcode = "110";
			type = 3;
			token=strtok(NULL," \t\n");
		}//halt
			
		else if(strcmp(token,"noop") == 0){//noop
			opcode = "111";
			type = 3;
			token=strtok(NULL," \t\n");
		}//noop
		
		else if (strcmp(token,".fill") == 0){ //.fill
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				puts(token);
			} else{
				for (int i = 0; i < nooflabels + 1 && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						printf("%d\n", labeltable[i].location);
					}
				}
			}
			lineNumber++;
			continue;
		}
		
		else{ //label
			token = strtok(NULL," \t\n");
			goto start;
		}
		/*
		//Binary work
		if (type == 0) { // R
			
		}
		
		else if (type == 1){ // I
			r2 = r2 + r3;
		}
		
		else if (type == 2){ // J
			
		}
		else if (type == 3){// O
			
		}
		*/
		lineNumber++;
	}
}

int main(int argc, const char * argv[]) {
	FILE *code; //File in
	FILE *machineCode; //final out
	char a[] = "out.mc";
	struct label labeltable[50];
	int nooflabels = 0;
	
	code = fopen(argv[1], "r");
	machineCode = fopen(a, "w+");
	
	nooflabels = pass1(code, labeltable, nooflabels);
	fseek(code, 0, SEEK_SET);
	
	pass2(code, labeltable, nooflabels);
	
	fclose(code);
	fclose(machineCode);
}
