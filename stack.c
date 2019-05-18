//
//  stack.c
//  PrefixEvalAndTrans
//
//  Created by 이재원 on 14/05/2019.
//  Copyright © 2019 Jae Won. All rights reserved.
//

#include "stack.h"

#define INIT_STACK_CAPA 10

void allocStack(stack** s){
    *s = (stack*)calloc(1, sizeof(stack));
    (*s)->stc = (element*)calloc(INIT_STACK_CAPA, sizeof(element));
    (*s)->capacity = INIT_STACK_CAPA;
    (*s)->top = -1;
}

Boolean isEmpty(stack s){
    if(s.top == -1)
        return True;
    return False;
}

Boolean isFull(stack s){
    if(s.top == s.capacity - 1)
        return True;
    return False;
}

void stackFull(stack* s){
    s->capacity *= 2;
    s->stc = (element*)realloc(s->stc, s->capacity * sizeof(element));
}

void stackEmpty(){
    fprintf(stderr, "ERROR! Stack is empty");
    exit(EXIT_FAILURE);
}

void push(stack* s, element e){
    if(isFull(*s))
        stackFull(s);
    s->stc[++(s->top)] = e;
}

element pop(stack* s){
    if(isEmpty(*s))
        stackEmpty();
    return s->stc[(s->top)--];
}

void stackFree(stack** s){
    free((*s)->stc);
    free(*s);
}
