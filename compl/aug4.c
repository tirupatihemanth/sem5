#include <stdio.h>
#include <string.h>
#include "trie.h"
#include "bstree.h"

void parse(int,int);
//int ifVal=0,forVal=0;

forLevel levels[256];
char *token, copy[256], str[256], name1[256], name2[256], name3[256];
FILE *in, *out;
char delim[10]=" \t\n";
trie *names;
forTree *fortree;

int main(){

    in = fopen("input.txt","r");
    out = fopen("output.txt","w");

    names = (trie *) malloc(sizeof(trie));
    //forloop *loops = (forloop *) malloc(sizeof(forloop));

    fprintf(out,"graph{\n");
    parse(0,0);   
    fprintf(out,"}\n");
    fclose(in);
    fclose(out);
    return 0;
}

void parse(int ifVal, int forVal){
    
    if(fgets(str,255, in)==NULL){
        return;
    }
    strcpy(copy, str);
    
    token = strtok(str,delim);
    
    if(token==NULL){
        return parse(ifVal, forVal);
    }
    
    if(ifVal<0){
        if(strcmp(token,"endif")==0){
            return;
        }
        return parse(-1, forVal);
    }
    else if(ifVal>0 && strcmp(token,"endif")==0){
        return;
    }

    if(forVal>0 && strcmp(token,"endforeach")==0){
        return;
    }

    if(strcmp(token,"if")==0){
        token = strtok(NULL,delim);
        char *temp = strtok(NULL, delim);
        temp = strtok(NULL, delim);
        strlist *friends = search(names, token, temp); 
        if(friends == NULL){
            parse(-1, forVal);
        }
        else{
            parse(1, forVal);
        }
        return parse(ifVal, forVal);
    }
    else if(strcmp(token,"foreach")==0){ 
        forVal++;
        token = strtok(NULL, delim);
        char *var = token;
        levels[forVal].pos = ftell(in);
        if(fortree!=NULL){
            updateTree(fortree,var,forVal);
        }
        else{
            fortree = (forTree *)malloc(sizeof(forTree));
            fortree->level=forVal;
            char *blah = (char *)malloc(sizeof(char)*strlen(var));
            strcpy(blah,var);
            fortree->str=blah;
        }
        token = strtok(NULL, delim);
        token = strtok(NULL, delim);
        strlist *list = getRelations(names, token);
        while(1){
            levels[forVal].str = list->str;
            parse(ifVal, forVal);
            list = list->next;
            if(list!=NULL){
                fseek(in,levels[forVal].pos, SEEK_SET);
            }
            else{
                break;
            }
        }
        forVal--;
        return parse(ifVal, forVal);
    }
    
    if(forVal>0){
        int temp = varLevel(fortree, token);
        if(temp!=-1){
            token = levels[temp].str;
        }
    }
    fprintf(out, "%s -- ", token);
    char *temp = strtok(NULL,delim);
    temp = strtok(NULL,delim);
    if(forVal>0){
        int tempLevel = varLevel(fortree, temp);
        if(tempLevel!=-1){
            temp = levels[tempLevel].str;
        }
    }

    char *var1 = (char *) malloc(sizeof(char)*strlen(token));
    char *var2 = (char *) malloc(sizeof(char)*strlen(temp));
    strcpy(var1, token);
    strcpy(var2, temp);
    addName(names, var1, var2);
    addName(names, var2, var1);
    fprintf(out,"%s;\n", temp);
    
    parse(ifVal, forVal);
    /*if(ifVal>0){
        parse(1);
    }
    else{
        parse(0);
    }*/
}
