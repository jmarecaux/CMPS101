// Jules Marecaux
// jrmareca
// Graph.h
// PA4
// ---------------------------------------------------------------------

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "List.h"

#define NIL 0
#define UNDEF -1

typedef struct GraphObj* Graph;

// Constructors/Destructors --------------------------------------------

Graph newGraph(int n); //good

void freeGraph(Graph* pG); //good

// Access Functions ----------------------------------------------------

int getOrder(Graph G); //good

int getSize(Graph G); //good

int getParent(Graph G, int u); //good

int getDiscover(Graph G, int u); //good

int getFinish(Graph G, int u); //good

// Manipulation Procedures ---------------------------------------------

void addArc(Graph G, int u, int v); //good

void addEdge(Graph G, int u, int v); // good

void DFS(Graph G, List S); 

// Other Functions -----------------------------------------------------

Graph transpose(Graph G); //good

Graph copyGraph(Graph G); //good

void printGraph(FILE* out, Graph G); //good

#endif
