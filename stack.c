#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define size 1000

/*
 * Item: An item that is being pushed to or popped from the stack
 *       It may be float (to be used while evaluating the postfix)
 *       It may be char* (to be used while converting infix to postfix)
 */
typedef union {
	float fData;
	char* cpData;
} Item;
/*
 *
 */
typedef struct Stack{
	Item data[size];
    int top;
} Stack;
/*
 *
 */
void init(Stack *s) {
	s->top=-1;
}
/*
 *
 */
int isEmpty(Stack *s) {
    if(s->top==-1) return -1;
    else return 1;
}
/*
 *
 */
Item top(Stack *s) {
	return s->data[s->top];
}
/*
 *
 */
Item pop(Stack *s) {
	if(s->top==-1){printf("Stack Is Already Empty"); return;}
	s->top--;
	return s->data[s->top];
}
/*
 *
 */
void push(Stack *s, Item val) {
    if(s->top==size-1){printf(" Stack Overflow "); return;}
    //create a new array of double the size and move previous
    //array elements there
    s->top++;
    s->data[s->top]=val;
}
/*
 *
 */
void destroy(Stack *s) {
	free(s);
}
/*
 * infixToPostfix: converts an expression in infix notation to
 *					to a postfix notation (Reverse-Polish Notation)
 *					ASSUME ^*+-/ operators
 *					e.g., 2 + 3 --> 2 3 +
 *					e.g., ( -2.5 + 3.14 ) * 4 --> -2.5 3.14 + 4 *
 */
void infixToPostfix(char* infix, char* postfix)
{
    strtok(infix," ");
    while (infix!=NULL){
        printf("%s ",infix);
        strtok(NULL," ");
    }
}
/*
 * evaluatePostfix: Evaluates an expression in postfix notation
 *					 (Reverse-Polish Notation)
 *					ASSUME single-digit operands
 */
float evaluatePostfix(char* postfix)
{
    /*while (isEmpty(s)){
        if(isdigit(pop())){
            postfix++ =pop();
        }
    }*/
	return 0;
}
/*
 *
 */
void replaceNewLineBySpace(char *s) {
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
/*
 *
 */
int main(int argc, char**argv) {
    char infixExpr[256] = "";
	char postfixExpr[256] = "";

    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);

        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);

		float result = evaluatePostfix(postfixExpr);
        printf("Result: %f\n\n", result);

		printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
	}
	return 0;
}
