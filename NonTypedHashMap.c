#ifndef MAXKEYSIZE
#include "NonTypedHashMap.h"
#endif
#include "HashConflictList.c"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int Hadd(char *_key, DATATYPE value, size_t inputSize, hashDefault *self){
  void* dataPtr = malloc(inputSize);
  memcpy(dataPtr, value, inputSize);
  hashItem* hL = &self->hash_map[self->hash(_key)];
	// find from list if cList already present
	if (strcmp(hL->key, "cList\0") == 0){
		hashItem nI;
		nI.data = dataPtr;
		strcpy(nI.key, _key);
		((linkedList*)hL->data)->push(nI, hL->data);
		return 1;
	}
	// create cList if there is a collission
  if (hL->data != NOTSET){
		hashItem nI; 
		nI.data = dataPtr;
		strcpy(nI.key, _key);
		linkedList* clist = generateLinkedList(*hL);
		clist->push(nI, clist);
		hL->data = clist;
		strcpy(hL->key, "cList\0");
		return 1;
	} else {
		hL->data = dataPtr;
		strcpy(hL->key, _key);
		return 1;
	}
};

DATATYPE Hfind(char *_key, hashDefault *self){
  hashItem val = self->hash_map[self->hash(_key)];
	if (val.data == NOTSET){
		return NOTFOUND;
	}
	if (strcmp(val.key, "cList\0") == 0){ // traverse LL to find element
		return ((linkedList*)val.data)->get(_key, val.data);
	}
  return val.data;
};

int Hremove(char *_key, hashDefault *self){
	int index = self->hash(_key);
	hashItem* hL = &self->hash_map[index];
	if (strcmp(hL->key, "cList") == 0) {
		int rS = ((linkedList*) hL->data)->remove(_key, hL->data);
		// status 2 means last item in list removed
		// in this case we want to allow the the clean up
		// at the end of this function to happen also worth noting here
		// that if there is only one item remaining in the cl we keep the
		// the cl instead of resolving it back to a node
		if (rS == 1) return 1;
	} 
	if (hL->data == NOTSET){ // no value to remove
		return NOTFOUND;
	}
	free(hL->data);
	hL->data = NOTSET;
	memset(hL->key, '\0', MAXKEYSIZE);
	return 1;
};

int Hhash(char * input){
  int hashNum = UINT_MAX;
  int hashBSize = sizeof(hashNum) * bitsInByte;
  for (int i = 0; input[i] != '\0'; i++){
    int shift = i % hashBSize; // mod by the number of bits in hashNum otherwise higher index could get greater than hashnum size leading to zero output from cyclic shift
    char cycledInput = input[i] << shift | input[i] >> (-shift & (hashBSize - 1)); // cyclic bit shift
    hashNum = hashNum ^ cycledInput;
  }
  return (unsigned int) hashNum % HASHSIZE;
};

