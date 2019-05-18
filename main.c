//
//  main.c
//  ExpressionNotation
//
//  Created by 이재원 on 17/05/2019.
//  Copyright © 2019 Jae Won. All rights reserved.
//

#include <stdio.h>
#include "stack.h"
#include <string.h>




typedef enum{
    lparen = 0, rparen, plus, minus, multi, division, mod, eos, operand, unplus, unminus, and, or,
    not, bigger, smaller, shl, shr, equal, diff, eorbig, eorsmall
}value;

int icp[22] = {20, 20, 12, 12, 13, 13, 13, 0, 0, 15, 15, 5, 4, 15, 10, 10, 11, 11, 9, 9, 10, 10};
int isp[22] = {0, 0, 12, 12, 13, 13, 13, 0, 0, 15, 15, 5, 4, 15, 10, 10, 11, 11, 9, 9, 10, 10};


int infixEval(char *expr);
int postfixEval(char *expr);
void postfixToInfix(char *expr, char *result);
void infixToPostfix(char *expr, char *result);
int prefixEval(char *expr);
char* prefixToInfix(char *expr);
char* infixToPrefix(char *expr);
char* prefixToPostfix(char *expr);
char* postfixToPrefix(char *expr);

char* printValue(value name);
void makeExp(value name, char *op1, char *op2, char *answer);

value checkName(char *token);
int calculate(value name, int op1, int op2);

int main(){
    char expr[MAX_EXPR_LEN];
    char answer[MAX_EXPR_LEN];

    printf("Expression? : ");
    fgets(expr, sizeof(expr), stdin);
    expr[strlen(expr)-1] = '\0';
    

    postfixToInfix(expr, answer);
    printf("%s", answer);
}

value checkName(char *token){
    if(!strcmp(token, "("))
        return lparen;
    
    else if(!strcmp(token, ")")){
        return rparen;
    }
    
    else if(!strcmp(token, "+")){
        return plus;
    }
    
    else if(!strcmp(token, "-")){
        return minus;
    }
    
    else if(!strcmp(token, "*")){
        return multi;
    }
    
    else if(!strcmp(token, "/")){
        return division;
    }
    
    else if(!strcmp(token, "%")){
        return mod;
    }
    
    else if(!strcmp(token, "\0")){
        return eos;
    }
    
    else if(!strcmp(token, "\\+")){
        return unplus;
    }
    
    else if(!strcmp(token, "\\-")){
        return unminus;
    }
    
    else if(!strcmp(token, "&&")){
        return and;
    }
    
    else if(!strcmp(token, "||")){
        return or;
    }
    
    else if(!strcmp(token, "!")){
        return not;
    }
    
    else if(!strcmp(token, ">")){
        return bigger;
    }
    
    else if(!strcmp(token, "<")){
        return smaller;
    }
    
    else if(!strcmp(token, "<<")){
        return shl;
    }

    else if(!strcmp(token, ">>")){
        return shr;
    }
    
    else if(!strcmp(token, "==")){
        return equal;
    }
    
    
    else if(!strcmp(token, "!=")){
        return diff;
    }
    
    
    else if(!strcmp(token, "<=")){
        return eorsmall;
    }
    
    else if(!strcmp(token, ">=")){
        return eorbig;
    }
    
    else
        return operand;
}

int infixEval(char *expr){
    char result[MAX_EXPR_LEN];
    
    infixToPostfix(expr, result);
    return postfixEval(result);
}

int calculate(value name, int op1, int op2){
    switch (name) {
        case plus:
            return op1 + op2;
            break;
            
        case minus:
            return op1 - op2;
            break;
            
        case multi:
            return op1 * op2;
            break;
            
        case division:
            return op1 / op2;
            break;
            
        case mod:
            return op1 % op2;
            break;
            
        case unplus:
            return +op1;
            break;
            
        case unminus:
            return -op1;
            break;
            
        case and:
            return op1 && op2;
            break;
            
        case or:
            return op1 || op2;
            break;
            
        case not:
            return !op1;
            break;
            
        case bigger:
            return op1 > op2;
            break;
            
        case smaller:
            return op1 < op2;
            break;
            
        case shl:
            return op1 << op2;
            break;
            
        case shr:
            return op1 >> op2;
            break;
            
        case equal:
            return op1 == op2;
            break;
            
        case diff:
            return op1 != op2;
            break;
            
        case eorbig:
            return op1 >= op2;
            break;
            
        case eorsmall:
            return op1 <= op2;
            break;
            
            
        default:
            printf("Error! Wrong Operator\n");
            exit(EXIT_FAILURE);
            break;
    }
}

int postfixEval(char *expr){
    char del[] = " ";
    char *token;
    value name;
    stack *operandStc;
    element item;
    int op1, op2;
    int result;
    
    allocStack(&operandStc);
    
    token = strtok(expr, del);
    
    while(token != NULL){
        name = checkName(token);
        if(name == operand){
            item.key = atoi(token);
            push(operandStc, item);
        }
        
        else{
            if(name == unminus || name == unplus || name == not){
                op1 = pop(operandStc).key;
                item.key = calculate(name, op1, op2);
                push(operandStc, item);
            }
            
            else{
                op2 = pop(operandStc).key;
                op1 = pop(operandStc).key;
                item.key = calculate(name, op1, op2);
                push(operandStc, item);
            }
        }
        
        token = strtok(NULL, del);
    }
    
    result = pop(operandStc).key;
    stackFree(&operandStc);
    
    
    
    return result;
    
}

char* printValue(value name){
    switch (name) {
        case plus:
            return "+";
            break;
            
        case minus:
            return "-";
            break;
            
        case multi:
            return "*";
            break;
            
        case division:
            return "/";
            break;
            
        case mod:
            return "%";
            break;
            
        case unplus:
            return "+";
            break;
            
        case unminus:
            return "-";
            break;
            
        case and:
            return "&&";
            break;
            
        case or:
            return "||";
            break;
            
        case not:
            return "!";
            break;
            
        case bigger:
            return ">";
            break;
            
        case smaller:
            return "<";
            break;
            
        case shl:
            return "<<";
            break;
            
        case shr:
            return ">>";
            break;
            
        case equal:
            return "==";
            break;
            
        case diff:
            return "!=";
            break;
            
        case eorbig:
            return ">=";
            break;
            
        case eorsmall:
            return "<=";
            break;
            
            
        default:
            printf("Error! Wrong Operator\n");
            exit(EXIT_FAILURE);
            break;
    }
    
    
}

void makeExp(value name, char *op1, char *op2, char *answer){
    strcpy(answer, "( ");
    if(name == unplus || name == unminus || name == not){
        strcat(answer, printValue(name));
        strcat(answer, " ");
        strcat(answer, op1);
        
        
    }

    else{
        strcat(answer, op1);
        strcat(answer, printValue(name));
        strcat(answer, " ");
        strcat(answer, op2);
    }
    strcat(answer, ")");
}

void postfixToInfix(char *expr, char *result){
    char del[] = " ";
    stack* expStack;
    char *token;
    value name;
    element item;
    char op1[MAX_EXPR_LEN], op2[MAX_EXPR_LEN], answer[MAX_EXPR_LEN];
    

    allocStack(&expStack);
    
    token = strtok(expr, del);
    
    while(token != NULL){
        name = checkName(token);
        
        if(name == operand){
            strcpy(item.strKey, token);
            strcat(item.strKey, " ");
            push(expStack, item);
        }
        
        else if(name == unplus || name == unminus || name == not){
            strcpy(op1, pop(expStack).strKey);
            makeExp(name, op1, op2, answer);
            strcpy(item.strKey, answer);
            strcat(item.strKey, " ");
            push(expStack, item);
            
        }
        
        else{
            strcpy(op2, pop(expStack).strKey);
            strcpy(op1, pop(expStack).strKey);
            makeExp(name, op1, op2, answer);
            strcpy(item.strKey, answer);
            strcat(item.strKey, " ");
            push(expStack, item);
            
        }
        token = strtok(NULL, del);
    }
    
    strcpy(result, pop(expStack).strKey);
    result[strlen(result)-1] = '\0';
    stackFree(&expStack);
}

void infixToPostfix(char *expr, char *result){ //need
    stack *opStack;
    char del[] = " ";
    char *token;
    value name, stcTopName;
    element item;
    
    
    strcpy(result, "");
    
    allocStack(&opStack);
    strcpy(item.strKey, "\0");
    push(opStack, item);
    
    
    token = strtok(expr, del);
    while(token != NULL){
        name = checkName(token);
        
        if(name == operand){
            strcat(result, token);
        }
        
        else if(name == rparen){
            
            while(strcmp(opStack->stc[opStack->top].strKey, "(")){
                strcat(result, pop(opStack).strKey);
            }
            pop(opStack);
        }
        
        else{
            stcTopName = checkName(opStack->stc[opStack->top].strKey);
            
            while(isp[stcTopName] >= icp[name]){
                strcat(result, pop(opStack).strKey);
                stcTopName = checkName(opStack->stc[opStack->top].strKey);
            }
            
            strcpy(item.strKey, token);
            push(opStack, item);
        }
        
        token = strtok(NULL, del);
    }
    
    stcTopName = checkName(opStack->stc[opStack->top].strKey);
    while(stcTopName != eos){
        strcat(result, pop(opStack).strKey);
        stcTopName = checkName(opStack->stc[opStack->top].strKey);
    }
    
    stackFree(&opStack);
}

int prefixEval(char *expr);

char* prefixToInfix(char *expr);

char* infixToPrefix(char *expr);

char* prefixToPostfix(char *expr);

char* postfixToPrefix(char *expr);



