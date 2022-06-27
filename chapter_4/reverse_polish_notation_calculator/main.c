#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#define MAX_OP_SIZE 100
int main() {
    int type;
    double op2;
    char s[MAX_OP_SIZE];
    while((type=getop(s))!=EOF) {
        switch(type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop()+pop(0));
                break;
            case '-':
                op2=pop();
                push(pop()-op2);
                break;
            case '*':
                push(pop()*pop(0));
                break;
            case '/':
                op2=pop();
                push(op2/pop());
                break;
        }
    }
    printf("%f",pop());
}