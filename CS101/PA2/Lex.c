//--------------------------------------------------------------------
// Jules Marecuax
// jrmareca
// 1574177
// PA2 Lex.c
// -------------------------------------------------------------------

#include "List.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#define MAX_LEN 280


int main(int argc, char * argv[]) {
	int count = 0;
	FILE *in, *out;
	char line[MAX_LEN];
	char* token;
	
	if( argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	
	if(in == NULL) {
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if(out == NULL) {
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	
	while( fgets(line, MAX_LEN, in) != NULL) {
		count++;
	}

	fclose(in);
	fclose(out);
	
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	
	int size = count;
	char array[size][MAX_LEN];
	
	count = 0;
	
	while( fgets(line, MAX_LEN, in) != NULL) {
		token = strtok(line, "\0\n");
		strcpy(array[count], token);
		
		count++;
	}
	
	List L = newList();

	append(L, 0);
	
	for(int j = 1; j < size; j++) {
		moveFront(L);
		while(index(L) != -1) {
			if(strcmp(array[get(L)], array[j]) > 0){
				insertBefore(L, j);
				break;
			}
			moveNext(L);
			if(index(L) == -1) {
				append(L, j);
			}
		}
	}
	
	moveFront(L);
	while(index(L) != -1) {
		fprintf(out, "%s", array[get(L)]);
		moveNext(L);
	}
	
	fclose(in);
	fclose(out);
	
	freeList(&L);

	return(0);
	
}
