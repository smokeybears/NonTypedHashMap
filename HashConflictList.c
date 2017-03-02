#ifndef MAXKEYSIZE
#include "NonTypedhashMap.h"
#endif
#include <stdlib.h>
#define LDT hashItem // "list datatype"

typedef struct _node {
	LDT data;
	struct _node* next;
} node;

typedef struct _linkedList {
	node* head;
	node* tail;
	node (*shift)(LDT, struct _linkedList*);
	node (*push)(LDT, struct _linkedList*);
	node (*find)(LDT, struct _linkedList*);	
	int (*remove)(char[MAXKEYSIZE], struct _linkedList*);
	LDT* (*get)(char[MAXKEYSIZE], struct _linkedList*);
	int length;
} linkedList;


node CLshift(LDT newVal, linkedList* parent){
	node* newNode = malloc(sizeof(node));
	newNode->data = newVal;
	newNode->next = parent->head;
	parent->head = newNode;
	if (parent->length == 0){ // head and tail should be same if only node in list
		parent->tail = newNode;
	}
	parent->length++;
	return *newNode;
}

node CLpush(LDT newVal, linkedList* parent){
	node* newNode = malloc(sizeof(node));
	newNode->data = newVal;
	parent->tail->next = newNode;
	parent->tail = newNode;
	if (parent->length == 0){ // head and tail should be same if only node in list
		parent->head = newNode;
	}
	parent->length++;
	return *newNode;
}

// remove FIRST instance of value in list returns 0 if not found 1 if value was removed
int CLremove(char _key[MAXKEYSIZE], linkedList* self){
	node *lnode = '\0', *cnode = self->head;
	if (self->length == 1 && strcmp(cnode->data.key, _key) == 0){ // if deleting last node in list
		free(cnode->data.data);
		free(cnode);
		self->length--;
		return 2;
	}
	while(1){
		if (strcmp(cnode->data.key, _key) == 0){
			if (cnode == self->head){ 
					self->head = cnode->next;
			}
			if (cnode == self->tail){
				lnode->next = '\0';
				self->tail = lnode;
			} 
			free(cnode->data.data);
			free(cnode);
			self->length--;
			return 1;	
		}
		if (cnode == self->tail){
			return 0;
		}
		lnode = cnode;
		cnode = cnode->next;	
	}
};

LDT* CLget(char _key[MAXKEYSIZE], linkedList* self){
	node *cnode = self->head;
	while(1){
		if (strcmp(cnode->data.key, _key) == 0){
			return cnode->data.data;
		}
		if(cnode == self->tail){
			return NOTFOUND;
		}
		cnode = cnode->next;
	}
}

linkedList* generateLinkedList(LDT initialValue){
	linkedList* newList = malloc(sizeof(linkedList));
	node* startNode = malloc(sizeof(node));
	startNode->data = initialValue;
	startNode->next = '\0';
	newList->head = startNode;
	newList->tail = startNode;
	newList->length = 1;
	newList->push = &CLpush;
	newList->shift = &CLshift;
	newList->remove = &CLremove;
	newList->get = &CLget;
	return newList;
}

