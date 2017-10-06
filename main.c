//
//  main.c
//  assembler
//
//  Created by Joan Marin on 10/6/17.
//  Copyright © 2017 Joan Marin-Romero. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
	FILE *code; //File in
	FILE *machineCode; //final out
	char a[] = "out.mc";
	
	
	code = fopen(argv[1], "r");
	machineCode = fopen(a, "w+");
	
	
	
	fclose(code);
	fclose(machineCode);
}
