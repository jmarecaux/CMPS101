// Jules Marecaux
// jrmareca
// PA4
// FindPath.c
// ---------------------------------------------------------------------

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Graph.h"

#define MAX_LEN 380

int main(int argc, char* argv[]) {
	FILE* in;
	FILE* out;
	
	char line[MAX_LEN];
	
	if(argc != 3) {
		printf("Usage: FindPath in out\n");
		exit(1);
	}
	
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	
	if(in == NULL) {
		printf("Cannot open input file for reading\n");
		exit(1);
	}
	if(out == NULL) {
		printf("Cannot open output file for writing\n");
		exit(1);
	}
	
	fgets(line, MAX_LEN, in);
	int len = 0;
	sscanf(line, "%d", &len);
	
	Graph G = newGraph(len);
	
	while( fgets(line, MAX_LEN, in) != NULL) {
		int x = 0;
		int y = 0;
		sscanf(line, "%d %d", &x, &y);
		if(x == 0 && y == 0)
			break;
		addEdge(G, x, y);
	}
	printGraph(out, G);
	int count = 0;
		
	while( fgets(line, MAX_LEN, in) != NULL) {
		int x = 0;
		int y = 0;
		sscanf(line, "%d %d", &x, &y);
		if(x == 0 && y == 0)
			break;
		if(count++ != 0)
			fprintf(out, "\n");
		fprintf(out, "\n");
		BFS(G, y);
		
		int dist = getDist(G, x);
		fprintf(out, "The distance from %d to %d is ", x, y);
		if(dist == INF)
			fprintf(out, "infinity\n");
		else
			fprintf(out, "%d\n", dist);
		List L = newList();
		getPath(L, G, x);
		if(front(L) == NIL)
			fprintf(out, "No %d-%d path exists", x, y);
		else {
			fprintf(out, "A shortest %d-%d path is: ", x, y);
			printList(out, L);
		}
		freeList(&L);
	}
	
	freeGraph(&G);
	
	fclose(in);
	fclose(out);
	
	return(0);
	
}












