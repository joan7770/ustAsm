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
};

int pass1(FILE *code, struct label labeltable[], int numOfLabels){
	char line[100];
	char *token = NULL;
	char *op1;
	int lineNumber = 0;
	
	while(fgets(line,sizeof line,code)!= NULL){
		token = strtok(line," \t\n");
		
		if (strcmp(token,"add") != 0 && strcmp(token,"nand") != 0 && strcmp(token,"lw") != 0 && strcmp(token,"sw") != 0 && strcmp(token,"beq") != 0 && strcmp(token,"jalr") != 0&& strcmp(token,"halt") != 0 && strcmp(token,"noop") != 0 && strcmp(token,".fill") != 0) {
			//  label encounter
			labeltable[numOfLabels].location = lineNumber;
			op1 = (char*) malloc(sizeof(token));
			strcpy(op1,token);
			labeltable[numOfLabels].label=op1;
			numOfLabels++;
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
			
			//r1
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r1 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < numOfLabels && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r1 = labeltable[i].location - lineNumber;
					}
				}
			}
			
			//r2
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r2 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < numOfLabels && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r2 = labeltable[i].location - lineNumber;
					}
				}
			}
			
			//r3
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r3 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < numOfLabels && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r3 = labeltable[i].location - lineNumber;
					}
				}
			}
		} //add
		
		else if(strcmp(token,"nand") == 0) {
			opcode = 1;
			type = 0;
			//r1
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r1 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < numOfLabels && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r1 = labeltable[i].location - lineNumber;
					}
				}
			}
			
			//r2
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r2 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < numOfLabels && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r2 = labeltable[i].location - lineNumber;
					}
				}
			}
			
			//r3
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r3 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < numOfLabels && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r3 = labeltable[i].location - lineNumber;
					}
				}
			}
		}//nand
		
		else if(strcmp(token,"lw") == 0){//lw
			opcode = 2;
			type = 1;
			
			//r1
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r1 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < numOfLabels && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r1 = labeltable[i].location - lineNumber;
					}
				}
			}
			
			//r2
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r2 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < numOfLabels && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r2 = labeltable[i].location - lineNumber;
					}
				}
			}
			
			//r3
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r3 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < numOfLabels && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r3 = labeltable[i].location - lineNumber;
					}
				}
			}
		}//lw
			
		else if(strcmp(token,"sw") == 0){ // sw
			opcode = 3;
			type = 1;
			
			//r1
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r1 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < numOfLabels && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r1 = labeltable[i].location - lineNumber;
					}
				}
			}
			
			//r2
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r2 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < numOfLabels && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r2 = labeltable[i].location - lineNumber;
					}
				}
			}
			
			//r3
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r3 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < numOfLabels && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r3 = labeltable[i].location - lineNumber;
					}
				}
			}
		}//sw
			
		else if(strcmp(token,"beq") == 0){// beq
			opcode = 4;
			type = 1;
			
			//r1
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r1 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < numOfLabels && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r1 = labeltable[i].location - lineNumber;
					}
				}
			}
			
			//r2
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r2 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < numOfLabels && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r2 = labeltable[i].location - lineNumber;
					}
				}
			}
			
			//r3
			token=strtok(NULL," \t\n");
			if(isalpha(token[0]) == 0){
				r3 = (int) strtol(token,NULL,10);
			} else{
				for (int i = 0; i < numOfLabels && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						r3 = labeltable[i].location - (lineNumber + 1);
					}
				}
			}
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
				if (toFile) {
					fprintf(machineCode,"%s\n", token);
				}else{
					puts(token);
				}
			} else{
				for (int i = 0; i < numOfLabels && labeltable[i].label != NULL; i++) {
					if (strcmp(token,labeltable[i].label) == 0) {
						if (toFile) {
							fprintf(machineCode,"%d\n", labeltable[i].location);
						}else{
							printf("%d\n", labeltable[i].location);
						}
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
			command = opcode << 22 | r2 << 19 | r3 << 16 | r1;
		}
		
		else if (type == 1){ // I
			command = opcode << 22 | r1 << 19 | r2 << 16 | (r3 & 0x0000FFFF);
		}
		
		else if (type == 2){ // J
			command = opcode << 22 | r1 << 19 | r2 << 16;
		}
		else if (type == 3){// O
			command = opcode << 22;
		}
		lineNumber++;
		
		if (toFile) {
			fprintf(machineCode,"%d\n", command);
		}else{
			printf("%d\n", command);
		}
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
