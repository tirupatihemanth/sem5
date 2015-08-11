#include <stdio.h>
#ifndef BSTREE_H
#define BSTREE_H    

typedef struct forTree_ forTree;
typedef struct forLevel_ forLevel;

struct forLevel_{
    char *str;
    long int pos;
};

struct forTree_{
    char *str;
    int level;
    forTree *left, *right;
};

int varLevel(forTree *, char *);
void updateTree(forTree *, char *, int);

#endif
