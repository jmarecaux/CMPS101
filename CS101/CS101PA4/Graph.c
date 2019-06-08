// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Jules Marecaux
// Graph.c
// jrmareca
// 1574177
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

typedef struct GraphObj {
	List *adj;
	char *color;
	int *parent;
	int *distance;
	int order;
	int size;
	int source;
} GraphObj;

// Constructers/Destructors ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Graph newGraph(int n) {
	Graph G = malloc(sizeof(struct GraphObj));
	G->adj = calloc(n+1, sizeof(List));
	G->color = calloc(n+1, sizeof(int));
	G->parent = calloc(n+1, sizeof(int));
	G->distance = calloc(n+1, sizeof(int));
	G->order = n;
	G->size = 0;
	G->source = NIL;

	for(int i = 0; i <= n; i++) {
		G->adj[i] = newList();
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
	
	return G;
	
}

void freeGraph(Graph* pG) {
	Graph G = *pG;
	for(int i = 0; i <= getOrder(G); i++ ) {
		freeList(&(G->adj[i]));
	}
	free(G->adj);
	free(G->parent);
	free(G->distance);
	free(G->color);
	free(*pG);
	*pG = NULL;
}

// Access Functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int getOrder(Graph G) {
	if( G == NULL ) {
		fprintf(stderr, "Error on getOrder(), Graph G not found.");
		exit(1);
	} 
	return G->order;
}

int getSize(Graph G) {
	if( G == NULL ) {
		fprintf(stderr, "Error on getSize(), Graph G not found.");
		exit(1);
	}
	return G->size;
}

int getSource(Graph G) {
	if( G == NULL ) {
		fprintf(stderr, "Error on getSource(), Graph G not found.");
		exit(1);
	}
	return G->source;
}

int getParent(Graph G, int u) {
	if( G == NULL ) {
		fprintf(stderr, "Error on getParent(), Graph G not found.");
		exit(1);
	}
	if( u < 1 || u > getOrder(G) ) {
		fprintf(stderr, "Error on getParent(), 1 <= u <= getOrder(G)");
		exit(1);
	}
	return G->parent[u];
}

int getDist(Graph G, int u) {
	if( G == NULL ) {
		fprintf(stderr, "Error on getDist(), Graph G not found.");
		exit(1);
	}
	if( u < 1 || u > getOrder(G) ) {
		fprintf(stderr, "Error on getDist(), 1 <= u <= getOrder(G)");
		exit(1);
	}
	return G->distance[u];
}

void getPath(List L, Graph G, int u) {
	if( G == NULL ) {
		fprintf(stderr, "Error on getPath(), Graph G not found.");
		exit(1);
	}
	if( u < 1 || u > getOrder(G) ) {
		fprintf(stderr, "Error on getPath(), 1 <= u <= getOrder(G)");
		exit(1);
	}
	if( getSource(G) == NIL ) {
		fprintf(stderr, "Error on getPath(), unkown source");
		exit(1);
	}
	if( u == getSource(G) ) {
		prepend(L, u);
	}
	else if (getParent(G, u) == NIL ){
		append(L, NIL);
	}
	else {
		getPath(L, G, G->parent[u]);
		prepend(L, u);
	}
}

// Manipulation Procedures ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void makeNull(Graph G) {
	if( G == NULL ) {	
		fprintf(stderr, "Error on makeNull(), Graph G not found.");
		exit(1);
	}
	for(int i = 0; i <= getOrder(G); i++) {
		clear(G->adj[i]);
	}
	G->source = NIL;
	G->size = 0;
}

void addEdge(Graph G, int u, int v) {
	if( G == NULL ) {
		fprintf(stderr, "Error on addEdge(), Graph G not found.");
		exit(1);
	}
	if( u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G) ) {
		fprintf(stderr, "Error on addEdge(), 1 <= u, v <= getOrder(G)");
		exit(1);
	}
	addArc(G, u, v);
	addArc(G, v, u);
	G->size--;
}
	

void addArc(Graph G, int u, int v) {
	if( G == NULL ) {
		fprintf(stderr, "Error on addArc(), Graph G not found.");
		exit(1);
	}
	if( u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G) ) {
		fprintf(stderr, "Error on addArc(), 1 <= u, v < = getOrder(G)");
		exit(1);
	}
	moveFront(G->adj[u]);
	while( index(G->adj[u]) > -1 && v > get(G->adj[u]) ) {
		moveNext(G->adj[u]);
	}
	if( index(G->adj[u]) == -1 ) {
		append(G->adj[u], v);
	}
	else {
		insertBefore(G->adj[u], v);
	}
	G->size++;
}

void BFS(Graph G, int s) {
	
	if(G == NULL) {
		fprintf(stderr, "Error on BFS(): Graph is null");
		exit(1);
	}
	if( s < 1 || s > getOrder(G) ) {
		fprintf(stderr, "Error on BFS(): 1 <= s <= getOrder(G)");
		exit(1);
	}
	G->source = s;	
	for(int i = 0; i < (getOrder(G)+1); i++) {
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
	List Q = newList();
	G->color[s] = 'g';
	G->distance[s] = 0;
	G->parent[s] = NIL;
	append(Q, s);
	int temp, t;
	while(length(Q) != 0) {
		temp = front(Q);
		deleteFront(Q);
		moveFront(G->adj[temp]);
		while(index(G->adj[temp]) != -1) {
			t = get(G->adj[temp]);	
			if(G->color[t] == 'w') {
				G->color[t] = 'g';
				G->distance[t] = G->distance[temp] + 1;
				G->parent[t] = temp;
				append(Q, t);
			}
			moveNext(G->adj[temp]);
		}
		G->color[temp] = 'b';
	}
	freeList(&Q);
}

// Other Operations ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void printGraph(FILE* out, Graph G) {
	if( out == NULL || G == NULL ) {
		printf("Error on printGraph(), out or Graph G not recognizd");
		exit(1);
	}
	for(int i = 1; i <= getOrder(G); i++) {
		fprintf(out, "%d: ", i);
		printList(out, G->adj[i]);
		fprintf(out, "\n");
	}
}






















