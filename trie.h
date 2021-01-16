#ifndef trie_h
#define trie_h

#define NUM_LETTERS ((int)26)

typedef enum {FALSE = 0,TRUE =1 }boolean;

typedef struct node{
    char letter;
    long unsigned int count;
    boolean isEndOfWord;
    struct node* children[NUM_LETTERS];
}node;

node* create_node(char ch);
void insert(node* r, char* str);
void print(node* head, short size);
void print_r(node* head, short size);
void print_recursive(node* node, char* str, int x);
void print_r_recursive(node* n, char* str, int x);

#endif