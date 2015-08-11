#include "bstree.h"
#include <stdlib.h>
#include <string.h>

int varLevel(forTree *var, char *str){
    if(var == NULL){
        return -1;
    }

    if(strcmp(var->str, str)<0){
        return varLevel(var->right, str);
    }
    else if(strcmp(var->str, str)>0){
        return varLevel(var->left, str);
    }
    else{
        return var->level;
    }
}

void updateTree(forTree *var, char *str, int level){

    if(strcmp(var->str, str)>0){
        if(var->left!=NULL){
            updateTree(var->left, str, level);
        }
        else{
            var->left = (forTree *)malloc(sizeof(forTree));
            var->level=level;
            char *temp = (char *) malloc(sizeof(char)*strlen(str));
            strcpy(temp,str);
            var->str = temp;
            return;
        }
    }
    else if(strcmp(var->str, str)<0){
        if(var->right!=NULL){
            updateTree(var->right, str, level);
        }
        else{
            var->right = (forTree *)malloc(sizeof(forTree));
            var->level = level;
            char *temp = (char *) malloc(sizeof(char)*strlen(str));
            strcpy(temp,str);
            var->str = temp;
            return;
        }
    }
    else{
        var->str = str;
        var->level = level;
        return;
    }

}
