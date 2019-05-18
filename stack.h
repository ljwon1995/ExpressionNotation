//
//  stack.h
//  PrefixEvalAndTrans
//
//  Created by 이재원 on 14/05/2019.
//  Copyright © 2019 Jae Won. All rights reserved.
//

#ifndef stack_h
#define stack_h
#include <stdio.h>
#include <stdlib.h>
#define MAX_EXPR_LEN 100


typedef union{
    int key;
    char strKey[MAX_EXPR_LEN];
    char charKey;
}element;

typedef struct{
    int capacity;
    int top;
    element* stc;
}stack;

typedef enum{
    True = 1, False = 0
}Boolean;

void allocStack(stack** s);
Boolean isEmpty(stack s);
Boolean isFull(stack s);
void stackFull(stack* s);
void stackEmpty(void);
void push(stack* s, element e);
element pop(stack* s);
void stackFree(stack**s);



#endif /* stack_h */
