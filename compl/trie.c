#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

strlist *getRelations(trie *var, char *str){
    int i;
    trie *temp = var;
    for(i=0;i<strlen(str);i++){
        if(temp==NULL){
            return NULL;
        }
        temp = temp->child[str[i]-'a'];
    }
    return temp->frnds;
}

strlist *search(trie *var, char *str, char *strfriend){
    int i;
    strlist *friends = getRelations(var, str);

    while(friends!=NULL){
        if(strcmp(strfriend, friends->str)==0){
            return friends;
        }
        friends = friends->next;
    }
    return friends;
}

void addName(trie *var, char *str, char *strfriend){
    
    int i;
    for(i=0;i<strlen(str);i++){
        if(var->child[str[i]-'a']==NULL){
            var->child[str[i]-'a'] = (trie *)malloc(sizeof(trie));
        }
        var = var->child[str[i]-'a'];
    }
    
    if(var->frnds == NULL){
        var->frnds = (strlist*) malloc(sizeof(strlist));
        var->frnds->str = strfriend;
    }
    else{
        strlist *temp = var->frnds;
        while(temp->next!=NULL){
            temp = temp->next;
        }
        temp->next = (strlist *)malloc(sizeof(strlist));
        temp->next->str = strfriend;
    }

}

