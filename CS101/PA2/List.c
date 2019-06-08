// -------------------------------------------------------------------
// Jules Marecaux
// jrmareca
// 1574177
// PA4 List.c
// -------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include"List.h"

typedef struct NodeObj {
	int data;
	struct NodeObj* prev;
	struct NodeObj* next;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

// -------------------------------------------------------------------

Node newNode(int value) {
	const size_t size = sizeof(struct NodeObj);
	Node N = (struct NodeObj*) malloc(size);
	N->data = value;
	N->prev = NULL;
	N->next = NULL;
	return N;
}

void freeNode(Node* pN) {
	if(pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

List newList() {
	const size_t size = sizeof(struct ListObj);
	List L = (struct ListObj *) malloc(size);
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->index = -1;
	L->length = 0;
	return L;
}

void freeList(List *pL) {
	if(pL != NULL && *pL != NULL) {
		Node N = (*pL)->front;
		while(N != NULL) {
			Node M = N;
			N = N->next;
			free(M);
		}
		free(*pL);
		*pL = NULL;
	}
}

// Access functions --------------------------------------------------

int length(List L) {
	if(L == NULL) {
		printf("List Error: calling index() on NULL List reference\n");
		exit(1);
	}
	return L->length;
}

int index(List L) {
	if(L == NULL) {
		printf("List Error: calling index() on NULL List reference\n");
		exit(1);
	}
	return L->index;
}

int front(List L) {
		Node N = L->front;
		return N->data;
}

int back(List L) {
	Node N = L->back;
	return N->data;
}

int get(List L) {
	if(L == NULL) {
		printf("List Error: calling get() on NULL list reference\n");
		exit(1);
	}
	if(L->index == -1) {
		printf("List Error: calling get() on NULL cursor reference\n");
		exit(1);
	}
	if(L->length <= 0) {
		printf("List Error: calling get() on too short of a List\n");
		exit(1);
	}
	Node N = L->cursor;
	return N->data;
}

int equals(List A, List B) {
	if(A->length != B->length) {
		return 0;
	}
	Node LA = A->front;
	Node LB = B->front;
	while(LA != NULL && LB != NULL) {
		if(LA->data != LB->data) {
			return 0;
		}
		LA = LA->next;
		LB = LB->next;
	}
	return 1;
	
}

// Manipulation procedures -------------------------------------------

void clear(List L) {
	if(L == NULL) {
		printf("List Error: calling clear() on NULL list reference\n");
		exit(1);
	}
	Node N = L->front;
	while(N != NULL) {
		Node M = N;
		N = N->next;
		free(M);
	}
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->index = -1;
}

void moveFront(List L) {
	if(L == NULL) {
		printf("List Error: calling moveFront on NULL list reference\n");
		exit(1);
	}
	if(L->length > 0) {
		L->cursor = L->front;
		L->index = 0;
	}
}

void moveBack(List L) {
	if(L == NULL) {
		printf("List Error: calling moveBack on NULL List reference\n");
		exit(1);
	}
	if(L->length > 0) {
		L->cursor = L->back;
		L->index = L->length - 1;
	}
}

void movePrev(List L) {
	if(L == NULL) {
		printf("List Error: calling movePrev on NULL list reference\n");
		exit(1);
	}
	if(L->index != 0 && L->cursor != NULL) {
		L->cursor = L->cursor->prev;
		L->index--;
	}
	else if(L->index == 0 && L->cursor != NULL) {
		L->cursor = NULL;
		L->index = -1;
	}
}

void moveNext(List L) {
	if( L==NULL ) {
		printf("List Error: calling moveNext on NULL list reference\n");
		exit(1);
	}
	if(L->index != L->length-1 && L->cursor != NULL) {
		L->cursor = L->cursor->next;
		L->index++;
	}
	else if(L->index == L->length-1 && L->cursor != NULL) {
		L->cursor = NULL;
		L->index = -1;
	}
}

void prepend(List L, int data) {
	if( L == NULL ) {
		printf("List Error: calling prepend on NULL list reference\n");
		exit(1);
	}
	Node N = newNode(data);
	if(L->back == NULL) L->back = N;
	else {
		L->front->prev = N;
	}
	N->next = L->front;
	if(index(L) != -1) L->index++;
	L->front = N;
	L->length++;
}

void append(List L, int data) {
	if( L == NULL ) {
		printf("List Error: calling prepend on NULL list reference\n");
		exit(1);
	}
	Node N = newNode(data);
	if(L->front == NULL) L->front = N;
	else {
		L->back->next = N;
		N->prev = L->back;
	}
	L->back = N;
	L->length++;
}

void insertBefore(List L, int data) {
	Node N = newNode(data);	
	if(L->cursor != L->front) {
		L->cursor->prev->next = N;
		N->prev = L->cursor->prev;
		L->cursor->prev = N;
		N->next = L->cursor;
	}
	else {
		L->cursor->prev = N;
		L->front = N;
		N->next = L->cursor;
	}
	L->index++;
	L->length++;
}

void insertAfter(List L, int data) {
	Node N = newNode(data);
	if(L->cursor != L->back) {
		L->cursor->next->prev = N;
		N->next = L->cursor->next;
		L->cursor->next = N;
		N->prev = L->cursor;
	}
	else {
		L->cursor->next = N;
		L->back = N;
		N->prev = L->cursor;
	}
	L->length++;
}

void deleteFront(List L) {
	if(L == NULL) { 
		printf("List Error: calling deleteFront() on NULL List reference.");
		exit(1);
	}
	if(length(L) == 0) {
		printf("List Error: calling deleteFront() on List of length 0");
		exit(1);
	}
	Node N = L->front;
	if(L->cursor == L->front)
		L->cursor = NULL;
	if(length(L) > 1) {
		L->front = N->next;
		L->front->prev = NULL;
	}
	else 
		L->front = L->back = NULL;
	L->length--;
	L->index--;
	freeNode(&N);
}

void deleteBack(List L) {
	if(L == NULL) { 
		printf("List Error: calling deleteBack) on NULL List reference.");
		exit(1);
	}
	if(length(L) == 0) {
		printf("List Error: calling deleteBack() on List of length 0");
		exit(1);
	}
	if(L->cursor == L->back) {
		L->cursor = NULL;
		L->index = -1;
	}
	Node N = L->back;
	if(length(L) > 1) {
		L->back = N->prev;
		L->back->next = NULL;
	}
	else
		L->front = L->back = NULL;
	L->length--;
	freeNode(&N);	
}

void delete(List L) {
	if(index(L) == 0) 
		deleteFront(L);
	else if(index(L) == length(L) - 1)
		deleteBack(L);
	else if (length(L) > 0 && index(L) != -1) {
		Node N = L->cursor;
		N->prev->next = N->next;
		N->next->prev = N->prev;
		L->cursor = NULL;
		L->index = -1;
		L->length--;
		freeNode(&N);
	}
}

// Other operations --------------------------------------------------

void printList(List L) {
	Node N = L->front;
	while(N != NULL) {
		printf("%d ", N->data);
		N = N->next;
	}
}

List copyList(List L) {
	List C = newList();
//	if(length(L) == 0 ) { 
//		return C;
//	}
	Node N = L->front;
	while(N != NULL) {
		append(C, N->data);
		N = N->next;
	}
	return C;
}



















