//---------------------------------------------------------------
// Jules Marecaux
// GraphTest.c
// jrmareca
//---------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

int main(int argc, char const *argv[]) {
	Graph G = newGraph(7);
	
	addEdge(G, 1, 4);
	addEdge(G, 1, 5);
	addEdge(G, 4, 5);
	addEdge(G, 2, 3);
	addEdge(G, 2, 6);
	addEdge(G, 3, 7);
	addEdge(G, 6, 7);
	
	printGraph(stdout, G);
	printf("getOrder(): %i\n", getOrder(G));
    printf("getSize(): %i\n", getSize(G));
	BFS(G, 2);
	List L = newList();
	getPath(L, G, 7);
	printList(stdout, L);
	printf("\n");
    printf("getSource(): %i\n", getSource(G));
	makeNull(G);
	freeGraph(&G);
    return 0;
}
