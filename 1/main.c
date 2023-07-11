#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinaryTree.h"

typedef struct{
    char nome[20];
    int idade;
    float altura;
}Pessoa;

Pessoa *Pessoa_construct(char nome[], int idade, float altura);
void Pessoa_destruct(void *p);
void Pessoa_print(Pessoa *p);
void free_cpf(void *cpf);
int cmp_fn(void *a, void *b);

int main () {
    char nome[20], cmd[20];
    int idade;
    float altura;
    int n;

    BinaryTree *bt = binary_tree_construct(cmp_fn, free_cpf, Pessoa_destruct);

    scanf("%d%*c", &n);
    for(int i = 0; i < n; i++){
        scanf("%s%*c", cmd);
        
        if (!strcmp(cmd, "SET")){
            char *cpf;
            cpf = malloc(sizeof(char) * 12);

            scanf("%s%*c", cpf);
            scanf("%s %d %f%*c", nome, &idade, &altura);
            Pessoa *p = Pessoa_construct(nome, idade, altura);
            binary_tree_add(bt, cpf, p);
        }
        else if(!strcmp(cmd, "GET")){
            char *cpf;
            cpf = malloc(sizeof(char) * 12);
            scanf("%s%*c", cpf);

            Pessoa *p = binary_tree_get(bt, cpf);
            if (p == NULL)
                printf("cpf nao encontrado\n");
            else
                Pessoa_print(p);
            free(cpf);
        }
        else printf("comando invalido\n");
    }
    binary_tree_destroy(bt);
    return 0;
}

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

int cmp_fn(void *a, void *b){
    int a_cpf, b_cpf;
    a_cpf = atoi((char*)a);
    b_cpf = atoi((char*)b);
    if (a_cpf > b_cpf) return 1;
    else if (a_cpf < b_cpf) return -1;
    else return 0;
}


