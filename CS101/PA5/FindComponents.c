// ---------------------------------------------------------------------
// Jules Marecaux
// jrmareca
// FindComponents.c
// 1574177
// ---------------------------------------------------------------------

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Graph.h"

#define MAX_LEN 380

int main(int argc, char* argv[]) {

	FILE* in;
	FILE* out;
	List S = newList();

	char line[MAX_LEN];
	
	if(argc != 3) {
		printf("Usage: FindComponents infile outfile\n");
		exit(1);
	}
	
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	if( in == NULL ) {
		printf("Cannot open input file for reading\n");
		exit(1);
	}
	if( out == NULL ) {
		printf("Cannot open output file for reading\n");
		exit(1);
	}
	
	fgets(line, MAX_LEN, in);
	int size = 0;
	sscanf( line, "%d", &size);

	Graph G = newGraph(size);

	for(int i = 1; i <= size; i++) {
		append(S, i);

	}

	while( fgets(line, MAX_LEN, in) != NULL ) {
		int x;
		int y;
		sscanf( line, "%d %d", &x, &y );
		if( x == 0 && y == 0 ) {
			break;
		}
		addArc(G, x, y);
	}

	fprintf(out, "Adjacency list representation of G: \n");
	printGraph(out, G);

	DFS(G, S);
	Graph T = transpose(G);
	DFS(T, S);
	moveFront(S);

	int scc = 0;
	while(index(S) != -1) {
		if(getParent(T, get(S)) == NIL) {
			scc++;
		}
		moveNext(S);
	}
	
	List SCC[scc];
	
	for(int i = 0; i < scc; i++) {
		SCC[i] = newList();
	}
	
	int count = scc;
	moveFront(S);
	while(index(S) != -1) {
		if(getParent(T, get(S)) == NIL) {
			count--;
		}
		if(count == scc) {
			break;
		}
		append(SCC[count], get(S));
		moveNext(S);
	}

	fprintf(out, "\nG contains %d strongly connected components: \n", scc);
	
	for(int i = 0; i < scc; i++) {
		fprintf(out, "Component %d: ", i+1);
		printList(out, SCC[i]);
		fprintf(out, "\n");
		freeList(&(SCC[i]));
	}

	freeGraph(&G);
	freeGraph(&T);
	freeList(&S);

	fclose(in);
	fclose(out);

	return(0);

}
