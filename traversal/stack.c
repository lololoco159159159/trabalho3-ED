#include "stack.h"
#include "forward_list.h" 
#include <stdlib.h>

struct Stack{
    ForwardList *list;
};

Stack *stack_construct(){
    Stack *stack = (Stack*)malloc(sizeof(stack));
    stack->list = forward_list_construct();
    return stack;
}

void stack_destroy(Stack *s){
    forward_list_destroy(s->list);
    free(s);
}

void stack_push(Stack *stack, data_type data){
    forward_list_push_front(stack->list, data);
}

data_type stack_pop(Stack *stack){
    data_type data = forward_list_pop_front(stack->list);
    return data;
}
int stack_empty(Stack *s){
    return !forward_list_size(s->list);
}

data_type stack_top(Stack *s){
    return forward_list_front(s->list);
}