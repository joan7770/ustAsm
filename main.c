//
//  main.c
//  assembler
//
//  Created by Joan Marin on 10/6/17.
//  Copyright © 2017 Joan Marin-Romero. All rights reserved.
//uint32_t output 

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct command{
	char* label;
	int opcode;
	char* reg1;
	char* reg2;
	char* reg3;
	bool hasLabel;
	int address;
};

void pass1(FILE *code, struct command lines[]){
	char line[128];
	for (int readline = getc(code); readline != EOF; readline = getc(code)){
		fscanf(code,"%[^\n]", line);
		for (int i = 0; line[i] != '\0' && i < sizeof(lines); i = i + 1) {
			//int start = 0;
			
			if(line[0] !=  ' ' || line[0] !=  '\t'){
				char* str = &line[0];
				for (int c = 1; line[0] ==  ' ' || line[0] ==  '\t'; c = c +1) {
					str = str + line[c];
				}
				lines[i] = (struct command){.hasLabel = true, .label = str, .address = i};
				printf("str = %s\n", str);
			}
			
		}
	}
}

int main(int argc, const char * argv[]) {
	FILE *code; //File in
	FILE *machineCode; //final out
	char a[] = "out.mc";
	
	code = fopen(argv[1], "r");
	machineCode = fopen(a, "w+");
	
	printf("starting for loop\n");
	int count = 0;
	for (int c = getc(code); c != EOF; c = getc(code)){
		if (c == '\n'){
			count = count + 1;
		}
	}
	fseek(code, 0, SEEK_SET);
	
	struct command lines[count];
	printf("finished setting up struct\n");
	
	pass1(code, lines);
	
	fclose(code);
	fclose(machineCode);
}
