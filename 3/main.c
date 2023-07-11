#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinaryTree.h"

//===== PESSOA ======//
typedef struct{
    char nome[20];
    int idade;
    float altura;
}Pessoa;

Pessoa *Pessoa_construct(char nome[], int idade, float altura);
void Pessoa_destruct(void *p);
void Pessoa_print(Pessoa *p);
void free_cpf(void *cpf);
int Pessoa_cmp_fn(void *a, void *b);

//===== CELULA ======//
typedef struct{
    int x;
    int y;
}Celula;

Celula *Celula_construct(int x, int y);
void Celula_destruct(void *c);
void Celula_print(Celula *c);
int Celula_cmp_fn(void *a, void *b);
void free_idx(void *idx);

//===== MAIN ======//
int main () {
    int n;
    char cmd[20];
    //if (pessoa)
        char nome[20];
        int idade;
        float altura;
        BinaryTree *bt = binary_tree_construct(Pessoa_cmp_fn, free_cpf, Pessoa_destruct);
    //if (celula)
    /*
        int x, y;
        BinaryTree *bt = binary_tree_construct(Celula_cmp_fn, free_idx, Celula_destruct);
    */
   
    scanf("%d%*c", &n);
    for(int i = 0; i < n; i++){
        scanf("%s%*c", cmd);
        
        if (!strcmp(cmd, "SET")){
            //if (celula)
            /*
                scanf("%d %d%*c", &x, &y);
                int *idx = malloc(sizeof(int));
                scanf("%d%*c", idx);
                Celula *c = Celula_construct(x, y);
                c = binary_tree_add(bt, c, idx);
                if (c)
                    Celula_destruct(c);
            */
           //if (pessoa)
                char *cpf;
                cpf = malloc(sizeof(char) * 12);

                scanf("%s%*c", cpf);
                scanf("%s %d %f%*c", nome, &idade, &altura);
                
                Pessoa *p = Pessoa_construct(nome, idade, altura);
                Pessoa *aux = binary_tree_add(bt, cpf, p);
                if (aux)
                    Pessoa_destruct(aux);
        }
        
        else if(!strcmp(cmd, "GET")){

            //if (celula)
            /*
                scanf("%d %d%*c", &x, &y);
                Celula *c = Celula_construct(x, y);
                int *idx = binary_tree_get(bt, c);
                if (idx == NULL)
                    printf("celula nao encontrada\n");
                else
                    printf("%d\n", *idx);
                Celula_destruct(c);
            */
           //if (pessoa)
                char *cpf;
                cpf = malloc(sizeof(char) * 12);
                scanf("%s%*c", cpf);

                Pessoa *p = binary_tree_get(bt, cpf);
                if(p != NULL)
                    Pessoa_print(p);
                else{
                    printf("CHAVE INEXISTENTE\n");}
                free(cpf);

        }

        else if(!strcmp(cmd, "POP")){
            //pessoa
                char *cpf;
                cpf = malloc(sizeof(char) * 12);
                scanf("%s%*c", cpf);
                void *aux = binary_tree_remove(bt, cpf);
                free_cpf(cpf);
                if(aux != NULL)
                    free(aux);
        }
        
        else printf("comando invalido\n");
    }
    
    /*Vector *v = binary_tree_levelorder_traversal(bt);
    for (int i = 0; i < vector_size(v); i++)
    {
        KeyValPair *pair = vector_get(v, i);
        Celula *c = pair->key;
        Celula_print(c);
        printf("%d | ", *(int*)pair->value);
        key_val_pair_destroy(pair);
    }
    vector_destroy(v);
    printf("\n");
    */
    
    binary_tree_destroy(bt);
    return 0;
}


//===== PESSOA ======//
Pessoa *Pessoa_construct(char nome[], int idade, float altura){
    Pessoa *p = (Pessoa*) malloc(sizeof(Pessoa));
    strcpy(p->nome, nome);
    p->idade = idade;
    p->altura = altura;
    return p;
}

void Pessoa_destruct(void *p){
    free(p);
}

void Pessoa_print(Pessoa *p){
    printf("%s %d %.2f\n", p->nome, p->idade, p->altura);
}

void free_cpf(void *cpf){
    free(cpf);
}

int Pessoa_cmp_fn(void *a, void *b){
    int a_cpf, b_cpf;
    a_cpf = atoi((char*)a);
    b_cpf = atoi((char*)b);
    if (a_cpf > b_cpf) return 1;
    else if (a_cpf < b_cpf) return -1;
    else return 0;
}

//===== CELULA ======//
Celula *Celula_construct(int x, int y){
    Celula *c = (Celula*) malloc(sizeof(Celula));
    c->x = x;
    c->y = y;
    return c;
}

void Celula_destruct(void *c){
    free(c);
}

void Celula_print(Celula *c){
    printf("(%d, %d) ", c->x, c->y);
}

int Celula_cmp_fn(void *a, void *b){
    Celula *c1 = (Celula*) a;
    Celula *c2 = (Celula*) b;
    if (c1->x > c2->x) return 1;
    else if (c1->x < c2->x) return -1;
    else{
        if (c1->y > c2->y) return 1;
        else if (c1->y < c2->y) return -1;
        else return 0;
    }
}

void free_idx(void *idx){
    free(idx);
}




