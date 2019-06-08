// Jules Marecaux
// jrmareca
// Graph.c
// PA4
// ---------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

typedef struct GraphObj {

	List *adj;
	char *color;
	int *parent;
	int *discover;
	int *finish;
	int order;
	int size;

} GraphObj;

// Constructors/Destructors --------------------------------------------

Graph newGraph(int n) {

	Graph G = malloc(sizeof(struct GraphObj));
	G->adj = calloc(n+1, sizeof(List));
	G->color = calloc(n+1, sizeof(char));
	G->parent = calloc(n+1, sizeof(int));
	G->discover = calloc(n+1, sizeof(int));
	G->finish = calloc (n+1, sizeof(int));
	G->order = n;
	G->size = 0;

	for(int i = 0; i <= n ; i++) {
		G->adj[i] = newList();
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}
	
	return G;

}

void freeGraph(Graph *pG) {
	Graph G = *pG;
	
	for(int i = 0; i <= getOrder(G); i++) {
		freeList(&(G->adj[i]));
	}
	
	free(G->adj);
	free(G->color);
	free(G->parent);
	free(G->discover);
	free(G->finish);
	
	free(*pG);
	*pG = NULL;

}

// Access Functions ----------------------------------------------------

int getOrder(Graph G) {

	if( G == NULL ) {
		fprintf(stderr, "Error on getOrder(): null argument for Graph G\n");
		exit(1);
	}

	return G->order;

}

int getSize(Graph G) {
	
	if( G == NULL ) {
		fprintf(stderr, "Error on getSize(): null argument for Graph G\n");
		exit(1);
	}

	return G->size;
	
}
	
int getParent(Graph G, int u) {
	
	if( G == NULL ) {
		fprintf(stderr, "Error on getParent(): null argument for Graph G\n");
		exit(1);
	}
	if( u < 1 || u > getOrder(G) ) {
		fprintf(stderr, "Error on getParent(): int u out of bounds\n");
		exit(1);
	}
	return G->parent[u];

}

int getDiscover(Graph G, int u) {
	
	if( G == NULL ) {
		fprintf(stderr, "Error on getDiscover(): null argument for Graph G\n");
		exit(1);
	}
	if( u < 1 || u > getOrder(G) ) {
		fprintf(stderr, "Error on getDiscover(): int u out of bounds\n");
		exit(1);
	}

	return G->discover[u];

}

int getFinish(Graph G, int u) {
	
	if( G == NULL ) {
		fprintf(stderr, "Error on getFinish(): null argument for Graph G\n");
		exit(1);
	}
	if( u < 1 || u > getOrder(G) ) {
		fprintf(stderr, "Error on getFinish(): int u out of bounds\n");
		exit(1);
	}

	return G->finish[u];

}

// Manipulation Procedures ---------------------------------------------

void addArc(Graph G, int u, int v) {

	if( G == NULL ) {
		fprintf(stderr, "Error on addArc(): null argument for Graph G\n");
		exit(1);
	}
	if( u < 1 || u > getOrder(G) ) {
		fprintf(stderr, "Error on addArc(): int u out of bounds\n");
		exit(1);
	}
	if( v < 1 || v > getOrder(G) ) {
		fprintf(stderr, "Error on addArc(): int v out of bounds\n");
		exit(1);
	}
	
	if( getSize(G) == 0 ) {
		append(G->adj[u], v);
		G->size++;
		return;
	}
	
	moveFront(G->adj[u]);
	while(index(G->adj[u]) != -1) {
		if(v == get(G->adj[u])) {
			return;
		}
		if( v < get(G->adj[u]) ) {
			insertBefore(G->adj[u], v);
			G->size = G->size + 1;
			return;
		}
		moveNext(G->adj[u]);
	}

	append(G->adj[u], v);
	G->size = G->size + 1;

}

void addEdge(Graph G, int u, int v) {

	if( G == NULL ) {
		fprintf(stderr, "Error on addEdge(): null argument for Graph G\n");
		exit(1);
	}
	if( u < 1 || u > getOrder(G) ) {
		fprintf(stderr, "Error on addEdge(): int u out of bounds\n");
		exit(1);
	}
	if( v < 1 || v > getOrder(G) ) {
		fprintf(stderr, "Error on addEdge(): int v out of bounds\n");
		exit(1);
	}
	
	addArc(G, u, v);
	addArc(G, v, u);
	G->size--;

}

void dfsvis(Graph G, List L, int x, int* ptime) {

	if( G == NULL ) {
		fprintf(stdout, "Error on dfsvis(): null argument for Graph G\n");
		exit(1);
	}
	
	G->color[x] = 'g';
	G->discover[x] = ++(*ptime);
	
	List A = G->adj[x];
	int y;

	for( moveFront(A); index(A) != -1; moveNext(A) ) {
		
		y = get(A);

		if( G->color[y] == 'w' ) {
			G->parent[y] = x;
			dfsvis(G, L, y, ptime);
		}
	}


	G->color[x] = 'b';
	G->finish[x] = ++(*ptime);
	prepend(L, x);
	
}

void DFS(Graph G, List S) {

	List A;
	int x, time = 0;

	if( G == NULL ) {
		fprintf(stderr, "Error on DFS(): null argument for Graph G\n");
		exit(1);
	}
	if( S == NULL ) {
		fprintf(stderr, "Error on DFS(): null argument for List S\n");
		exit(1);
	}
	if(length(S) != getOrder(G)) {
		fprintf(stderr, "Error on DFS(): length of S does not equal order of G\n");
		exit(1);
	}
	
	A = copyList(S);
	clear(S);

	for(int i = 1; i < getOrder(G) + 1; i++) {
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}

	for(moveFront(A); index(A) != -1; moveNext(A)) {
		
		x = get(A);
		if( G->color[x] == 'w' ) {	
			dfsvis(G, S, x, &time);
		}

	}
	
	freeList(&A);

}

// Other Functions -----------------------------------------------------

Graph transpose(Graph G) {

	if( G == NULL ) {
		fprintf(stderr, "Error on transpose(): null argument for Graph G\n");
		exit(1);
	}
	
	Graph A = newGraph(getOrder(G));	

	for(int i = 1; i <= getOrder(G); i++) {
		moveFront(G->adj[i]);
		while( index(G->adj[i]) != -1 ) {
			addArc(A, get(G->adj[i]), i);
			moveNext(G->adj[i]);
		}
	}
	
	return A;

}

Graph copyGraph(Graph G) {

	if( G == NULL ) {
		fprintf(stderr, "Error on copyGraph(): null argument for Graph G\n");
		exit(1);
	}
	
	Graph A = newGraph(getOrder(G));	

	for(int i = 1; i <= getOrder(G); i++) {
		moveFront(G->adj[i]);
		while( index(G->adj[i]) != -1 ) {
			addArc(A, i, get(G->adj[i]));
			moveNext(G->adj[i]);
		}
	}

	return A;

}

void printGraph(FILE* out, Graph G) {
	
	if( G == NULL ) {
		fprintf(stderr, "Error on printGraph(): null argument for Graph G\n");
		exit(1);
	}
	
	for( int i = 1; i <= getOrder(G); i++) {

		fprintf(out, "%d: ", i);
		printList(out, G->adj[i]);
		fprintf(out, "\n");

	}
}




















