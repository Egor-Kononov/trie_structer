#include <stdio.h>
#include "trie.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

short s = 0;


 node* create_node(char ch){
     node* n = (node*)malloc(sizeof(node));
       if(n == NULL){
           exit(1);
       } 
       n->letter = ch;
       n->count = 0;
       n->isEndOfWord = FALSE;
       for(int i=0;i<NUM_LETTERS;i++){
           n->children[i]=NULL;
       }
     
     return n;
 }

 void insert(node* r, char* str){
     node* temp = r;
     while (*str){
         if(temp->children[*str - 'a'] == NULL){
             temp->children[*str - 'a'] = create_node(*str);
         }
         temp = temp->children[*str - 'a'];
         str++;
     }
     temp->count ++;
     temp->isEndOfWord = TRUE;
 }

 void triefree(node *current){
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        if (current->children[i] != NULL)
        {
            triefree(current->children[i]);
        }
    }
    free(current);
}


void print(node* head, short size){
    char *st = (char*)malloc(sizeof(char)*(size));
    if(st == NULL){
        triefree(head);
        exit(1);
    }
    print_recursive(head,st,0);
}

void print_recursive(node* n, char* str, int x){
    if(n == NULL){
        return;
    }
    if(n->isEndOfWord){
        str[x]='\0';
        printf("%s %ld\n",str, n->count);
    }
    for(int i=0; i<NUM_LETTERS;i++){
        if(n->children[i] != NULL){
            str[x]=i+'a';
            print_recursive(n->children[i],str,x+1);
        }
    }
    free(n);
}

void print_r(node* head, short size){
    char *st = (char*)malloc(sizeof(char)*(size));
    if(st == NULL){
        triefree(head);
        exit(1);
    }
    print_r_recursive(head,st,0);
}

void print_r_recursive(node* n, char* str, int x){
    if(n == NULL){
        return;
    }
    for(int i=NUM_LETTERS-1; i>=0;i--){
        if(n->children[i] != NULL){
            str[x] = i+'a';
            print_r_recursive(n->children[i],str,x+1);
        }
    }
    if(n->isEndOfWord == TRUE){
        str[x]='\0';
        printf("%s %ld\n",str, n->count);
    }
    free(n);
}

int main(int argc, char *argv[]){
    node* t = create_node(0);
    if(t == NULL){
        exit(1);
    }
    char ch ;
    char *str = (char*)malloc(sizeof(char));
    char result;
    int len = 0;
    int i = 0;
    while ((ch = getc(stdin)) != EOF){
        while((ch <= 122 && ch >=97) || (ch >= 65 && ch <= 90)){
            str = realloc(str,sizeof(char)*(i+2));
            if(str == NULL){
                triefree(t);
                exit(1);
            }
            result = tolower(ch);
            str[i] = result;
            str[i+1] = '\0';
            i++;
            ch = getc(stdin);
        }
        if(ch != '\n' && ch != '\t' && ch != ' ' && ch != EOF){
            continue;
        }
        len = strlen(str);
        if(len > s){
            s = len;
        }
        if(len == 0){
            continue;
        }
        
        insert(t,str);
        i=0;
        str[0] = '\0';      
        if(ch == EOF){
            break;
        } 
    }
    if(argc == 1){
        print(t,s);
        free(str);
    }else if(*argv[1] == 'r'){
        print_r(t,s);
        free(str);
    }
    return 0;
}
