#include <string.h>
#define HASHSIZE 100
#define bitsInByte 8 
#define NOTSET '\0' 
#define NOTFOUND 0
#define DATATYPE void * // datatype this struct can hold                  
#define MAXKEYSIZE 20 // including '\0'
typedef struct _hashItem {
	DATATYPE data;
	char key[MAXKEYSIZE];
}	hashItem;

typedef struct _hashDefault {
  hashItem hash_map[HASHSIZE];
  int (*add)(char *, DATATYPE, size_t,  struct _hashDefault *);
  int (*remove)(char *, struct _hashDefault *);
  DATATYPE (*find)(char *, struct _hashDefault *);
  int (*hash)(char *);
} hashDefault;

int Hadd(char *_key, DATATYPE value, size_t inputSize, hashDefault *self);
int Hhash(char * input);
int Hremove(char *_key, hashDefault *self);
int Hhash(char * input);
DATATYPE Hfind(char *_key, hashDefault *parent);

hashDefault newHash(){
  hashDefault newHash;
	memset(newHash.hash_map, '\0', HASHSIZE * sizeof(hashItem));
  newHash.add = &Hadd;
  newHash.remove = &Hremove;
  newHash.find = &Hfind;
  newHash.hash = &Hhash;
  return newHash;
};
