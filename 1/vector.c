
#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

struct Vector{
    data_type *data;
    int size;
    int allocated;
};


Vector *vector_construct(){
    Vector *pvector;
    pvector = (Vector*)calloc(1, sizeof(Vector));    
    pvector->data = (data_type*)calloc(10, sizeof(data_type));
    pvector->allocated = 10;
    pvector->size = 0;
    return pvector;
}

void vector_destroy(Vector *v){
    free(v->data);
    free(v);
}

void vector_push_back(Vector *v, data_type val){
    if((v->size) >= (v->allocated)){
        v->allocated = v->allocated * 2;
        v->data = (data_type*)realloc(v->data, v->allocated * sizeof(data_type));
    }
    v->data[v->size] = val;
    v->size++;
}

data_type vector_get(Vector *v, int i){
    if ((i >= 0) && (i < (v->size))){
        return v->data[i];
    }
    printf("Valor invalido!\n");
    exit(0);
}

int vector_size(Vector *v){
    return v->size;
}

void vector_set(Vector *v, int i, data_type val){
    v->data[i] = val;
}

int vector_find(Vector *v, data_type val){
    int i = 0;
    for(i = 0; i < (v->size); i++){
        if (val == v->data[i]){
            return i;
        }
    }
    return -1;
}

data_type vector_remove(Vector *v, int i){
    int aux = v->data[i];
    v->size = v->size - 1;

    for(; i < v->size ; i++){
        v->data[i] = v->data[i+1];
    }

    v->data = realloc(v->data, v->size * sizeof(data_type));
    v->allocated = v->size;

    return aux;
}

data_type vector_pop_front(Vector *v){
    return vector_remove(v, 0);

}

data_type vector_pop_back(Vector *v){
    return vector_remove(v, v->size-1);
}

void vector_insert(Vector *v, int i, data_type val){
    data_type aux = 0, anterior = 0;
    v->size = v->size + 1;
    if(v->allocated < v->size){
        v->allocated = v->size;
        v->data = realloc(v->data, v->allocated * sizeof(data_type));
    }

    
    anterior = v->data[i];
    v->data[i] = val;
    i++;
    for(; i < v->size ; i++){
        aux = v->data[i];
        v->data[i] = anterior;
        anterior = aux;
    }
}

void vector_swap(Vector *v, int i, int j){
    data_type aux;
    aux = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = aux;
}


void vector_sort(Vector *v){
    int i = 0, ocorreu_troca = 0;

    do{
        ocorreu_troca = 0;
        for(i = 0; i < (v->size - 1); i++){
            if (v->data[i] > v->data[i+1]){
                vector_swap(v, i, i+1);
                ocorreu_troca = 1;
            }
        }
    }while(ocorreu_troca);
}

// Retorna o indice de val usando busca binaria. Retorna -1 se nao encontrado.
int vector_binary_search(Vector *v, data_type val){
    int idx_min = 0, idx_max = 0, idx_central = 0;
    idx_max = v->size-1;

    while(idx_min <= idx_max){
        idx_central = (idx_max + idx_min)/2;
        
        if (v->data[idx_central] == val){
            return idx_central;
        }

        else if(v->data[idx_central] < val){
            idx_min = idx_central+1;
        }
        else{
            idx_max = idx_central-1;
        }
    }

    return -1;
}

void vector_reverse(Vector *v){
    int i = 0;
    data_type aux; 

    for(i = 0; i < (v->size/2); i++){
        aux = v->data[i];
        v->data[i] = v->data[(v->size-1) -i];
        v->data[(v->size-1) -i] = aux;
    }

}
