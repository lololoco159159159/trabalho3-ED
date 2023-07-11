#include <stdio.h>
#include <stdlib.h>

#include "forward_list.h"

ForwardList_Node *ForwardList_node_construct(data_type value, ForwardList_Node *next)
{
    ForwardList_Node *n = (ForwardList_Node *)malloc(sizeof(ForwardList_Node));
    n->value = value;
    n->next = next;
    return n;
}

void ForwardList_node_destroy(ForwardList_Node *n)
{
    free(n);
}

ForwardList *forward_list_construct(){
    ForwardList *l = (ForwardList *)calloc(1, sizeof(ForwardList));
    l->head = NULL;
    l->last = NULL;
    l->size = 0;

    return l;
}

int forward_list_size(ForwardList *l)
{
    return l->size;
}

data_type forward_list_find(ForwardList *l, void *key, int (*cmp_fn)(data_type data, void *key))
{
    ForwardList_Node *n = l->head;

    while (n != NULL)
    {
        if (!cmp_fn(n->value, key))
            return n->value;

        n = n->next;
    }

    return NULL;
}

void forward_list_push_front(ForwardList *l, data_type data)
{
    l->head = ForwardList_node_construct(data, l->head);
    l->size++;

    if (l->size == 1)
        l->last = l->head;
}

void forward_list_push_back(ForwardList *l, data_type data)
{
    ForwardList_Node *new_node = ForwardList_node_construct(data, NULL);
    if (l->last == NULL)
        l->head = l->last = new_node;
    else{
        l->last->next = new_node;
        l->last = new_node;
    }
    l->size++;
}

void forward_list_print(ForwardList *l, void (*print_fn)(data_type data))
{
    ForwardList_Node *n = l->head;

    printf("[");

    while (n != NULL)
    {
        print_fn(n->value);
        n = n->next;

        if (n != NULL)
            printf(", ");
    }

    printf("]");
}

data_type forward_list_get(ForwardList *l, int i)
{
    if (i < 0 || i >= l->size)
        exit(printf("Error: forward_list_get(): index out of bounds."));

    ForwardList_Node *n = l->head;
    for (int j = 0; j < i; j++)
        n = n->next;

    return n->value;
}

data_type forward_list_pop_front(ForwardList *l)
{
    if (l->head == NULL)
        exit(printf("Error: forward_list_pop_front(): list is empty."));

    ForwardList_Node *n = l->head;
    l->head = l->head->next;
    data_type data = n->value;
    ForwardList_node_destroy(n);
    l->size--;

    if (l->size <= 1)
        l->last = l->head;

    return data;
}

ForwardList *forward_list_reverse(ForwardList *l)
{
    ForwardList *new_list = forward_list_construct();

    ForwardList_Node *n = l->head;
    while (n != NULL)
    {
        forward_list_push_front(new_list, n->value);
        n = n->next;
    }

    return new_list;
}

void forward_list_clear(ForwardList *l)
{
    // we cannot use l->size in the for loop
    // because the size will change as we remove items
    int n_itens = l->size;

    for (int i = 0; i < n_itens; i++)
        forward_list_pop_front(l);
}

int forward_list_remove(ForwardList *l, data_type val){
    ForwardList_Node *n = l->head;
    ForwardList_Node *prev = NULL;

    while (n != NULL){
        if (n->value == val){
            l->size--;
            if(l->last->value == val){
                l->last = prev;
                if(prev != NULL)
                    prev->next = NULL;
            }
            else if (prev == NULL){
                if(n->next == NULL){
                    l->head = NULL;
                    l->last = NULL;
                }
                else
                    l->head = n->next;
            }
            else{
                prev->next = n->next;
            }

            ForwardList_node_destroy(n);

            if(l->size == 1)
                l->last = l->head;
            if(l->size == 0){
                l->head = NULL;
                l->last = NULL;
                forward_list_destroy(l);
                return 1;
            }
            return 0;
        }
        else{
            prev = n;
            n = n->next;
        }
    }
    return 0;
}

void forward_list_unique(ForwardList *l)
{
    // TODO
}

void forward_list_cat(ForwardList *l, ForwardList *m)
{
    ForwardList_Node *n = m->head;

    while (n != NULL)
    {
        forward_list_push_front(l, n->value);
        n = n->next;
    }
}

void forward_list_sort(ForwardList *l)
{
    // TODO
}

void forward_list_destroy(ForwardList *l){
    ForwardList_Node *n = l->head;
    while (n != NULL)
    {
        ForwardList_Node *next = n->next;
        free(n->value);
        ForwardList_node_destroy(n);
        n = next;
    }

    free(l);
}

data_type forward_list_front(ForwardList *l){
    return l->head->value;
}

