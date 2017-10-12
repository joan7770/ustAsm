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
#include <stdint.h>

struct label{
	char *label;
	int location;
	bool filled;
};

int pass1(FILE *code, struct label labeltable[], int numOfLabels){
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
				labeltable[numOfLabels].label = temp;
				labeltable[numOfLabels].location = (int) strtol(token,NULL,10);
				labeltable[numOfLabels].filled = true;
				numOfLabels++;
			}else{
				labeltable[numOfLabels].location = lineNumber;
				op1 = (char*) malloc(sizeof(token));
				strcpy(op1,temp);
				labeltable[numOfLabels].label=op1;
				labeltable[numOfLabels].filled = false;
				numOfLabels++;
			}
		}
		lineNumber++;
	}
	return numOfLabels;
}

void pass2(FILE *code, struct label labeltable[], int numOfLabels, bool toFile, FILE *machineCode){
	char line[100];
	char *token = NULL;
	int lineNumber = 0;
	int opcode;
	int type; // 0 =R, 1= I, 2 = J, 3 = O
	int r1 = 0, r2 = 0, r3 = 0;
	uint32_t command = 0;
	
	while(fgets(line,sizeof line,code)!= NULL){
		token = strtok(line," \t\n");
		
	start:
		if (strcmp(token,"add") == 0){ //add
			opcode = 0;
			type = 0;
		} //add
		
		else if(strcmp(token,"nand") == 0) {
			opcode = 1;
			type = 0;
		}//nand
		
		else if(strcmp(token,"lw") == 0){//lw
			opcode = 2;
			type = 1;
		}//lw
			
		else if(strcmp(token,"sw") == 0){ // sw
			opcode = 3;
			type = 1;
		}//sw
			
		else if(strcmp(token,"beq") == 0){// beq
			opcode = 4;
			type = 1;
		}//beq
			
		else if(strcmp(token,"jalr") == 0){// jalr
			opcode = 5;
			type = 2;
			token=strtok(NULL," \t\n");
		}//jalr
		
		else if (strcmp(token,"halt") == 0){//halt
			opcode = 6;
			type = 3;
			token=strtok(NULL," \t\n");
		}//halt
			
		else if(strcmp(token,"noop") == 0){//noop
			opcode = 7;
			type = 3;
			token=strtok(NULL," \t\n");
		}//noop
		
		else if (strcmp(token,".fill") == 0){ //.fill
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				puts(token);
			} else{
				for (int i = 0; i < numOfLabels + 1 && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						printf("%d\n", labeltable[i].location);
					}
				}
			}

			continue;
		}
		
		else{ //label
			token = strtok(NULL," \t\n");
			goto start;
		}
		
		
		 //Reg stuff and binary stuff
		if (type == 0) { // R
            printf("%s ",token);
            //r1
            token=strtok(NULL," \t\n");
            if(isalpha(token[0]) == 0){
                r1 = (int) strtol(token,NULL,10);
            } else{
                for (int i = 0; i < numOfLabels + 1 && labeltable[i].label != NULL; i++) {
                    if (strcmp(token,labeltable[i].label) == 0) {
						if (labeltable[numOfLabels].filled) {
							r1 = labeltable[i].location;
						}else{
							r1 = labeltable[i].location - (lineNumber + 1);
						}
                    }
                }
            }
            
            //r2
            token=strtok(NULL," \t\n");
            if(isalpha(token[0]) == 0){
                r2 = (int) strtol(token,NULL,10);
            } else{
                for (int i = 0; i < numOfLabels + 1 && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						if (labeltable[numOfLabels].filled) {
							r2 = labeltable[i].location;
						}else{
							r2 = labeltable[i].location - (lineNumber + 1);
						}
					}
                }
            }
            
            //r3
            token=strtok(NULL," \t\n");
            if(isalpha(token[0]) == 0){
                r3 = (int) strtol(token,NULL,10);
            } else{
                for (int i = 0; i < numOfLabels + 1 && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						if (labeltable[numOfLabels].filled) {
							r3 = labeltable[i].location;
						}else{
							r3 = labeltable[i].location - (lineNumber + 1);
						}
					}
                }
            }
            printf("%d %d %d\n", r1, r2, r3);
		}
		
		else if (type == 1){ // I
			printf("%s ",token);
			//r1
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r1 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < numOfLabels + 1 && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						if (labeltable[numOfLabels].filled) {
							r1 = labeltable[i].location;
						}else{
							r1 = labeltable[i].location - (lineNumber + 1);
						}
					}
				}
			}
			
			//r2
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r2 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < numOfLabels + 1 && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						if (labeltable[numOfLabels].filled) {
							r2 = labeltable[i].location;
						}else{
							r2 = labeltable[i].location - (lineNumber + 1);
						}
					}
				}
			}
			
			//r3
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r3 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < numOfLabels + 1 && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						printf("Label: %s Location: %d Filled: %d\n", labeltable[i].label, labeltable[i].location, labeltable[i].filled);
						if (labeltable[numOfLabels].filled) {
							r3 = labeltable[i].location;
						}else{
							r3 = labeltable[i].location - (lineNumber + 1);
						}
					}
				}
			}
			printf("%d %d %d\n", r1, r2, r3);
			r2 = r2 + r3;
		}
		
		else if (type == 2){ // J
			
		}
		else if (type == 3){// O
			
		}
		lineNumber++;
	}
}

int main(int argc, const char * argv[]) {
	FILE *code; //File in
	FILE *machineCode; //File out
	bool toFile = false;
	struct label labeltable[50];
	int numOfLabels = 0;
	
	code = fopen(argv[1], "r");
	
	numOfLabels = pass1(code, labeltable, numOfLabels);
	fseek(code, 0, SEEK_SET);
	
	if (argv[2] != NULL) {
		toFile = true;
		machineCode = fopen(argv[2], "w+");
		pass2(code, labeltable, numOfLabels, toFile, machineCode);
		fclose(machineCode);
	}
	else{
		pass2(code, labeltable, numOfLabels, toFile, NULL);
	}
	
	fclose(code);
	return 0;
}
