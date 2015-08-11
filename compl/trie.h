#include <stdio.h>
#include <stdlib.h>
#ifndef TRIE_H
#define TRIE_H

typedef struct trie_ trie;
typedef struct strlist_ strlist;

struct strlist_{
    char *str;
    strlist *next;
};

struct trie_{
    strlist *frnds; 
    trie *child[26];
};

strlist *search(trie *, char *, char *);
void addName(trie *,char *, char *);
strlist *getRelations(trie *, char *);
#endif
