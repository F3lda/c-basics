#include <stdio.h>
#include <stdlib.h>


#define STACK_INT_TO_DATA(x) (ParserStackData)((int)x)
#define STACK_CHAR_TO_DATA(x) (ParserStackData)((char)x)
#define STACK_FLOAT_TO_DATA(x) (ParserStackData)((float)x)
#define STACK_TOKEN_TO_DATA(x) (ParserStackData)((char *)x)

#define STACK_DATA_TO_INT(x) ((int)x.result)
#define STACK_DATA_TO_CHAR(x) ((char)x.term)
#define STACK_DATA_TO_FLOAT(x) ((float)x.value)
#define STACK_DATA_TO_TOKEN(x) ((char *)x.token)

typedef union {
	int result;
	char term;
	float value;
	char * token;
} ParserStackData;

typedef struct parserStackNode {
	ParserStackData data;
	struct parserStackNode *next;
} *ParserStackPtr;



void parserStackInit(ParserStackPtr *stack)
{
	(*stack) = NULL;
}

ParserStackData parserStackPush(ParserStackPtr *stack, ParserStackData data)
{
    ParserStackPtr item = malloc(sizeof(struct parserStackNode));
	if(item != NULL){
		item->data = data;
		item->next = (*stack);
		(*stack) = item;
		return STACK_INT_TO_DATA(0);
	}
	return STACK_INT_TO_DATA(-1);
}

ParserStackData parserStackPeek(ParserStackPtr *stack)
{
	if((*stack) != NULL){
		return (*stack)->data;
	}
	return STACK_INT_TO_DATA(-1);
}

ParserStackData parserStackPop(ParserStackPtr *stack)
{
	ParserStackPtr top = (*stack);
	if(top != NULL){
		(*stack) = top->next;
		ParserStackData data = top->data;
		free(top);
		return data;
	}
	return STACK_INT_TO_DATA(-1);
}

void parserStackFree(ParserStackPtr *stack)
{
	while(STACK_DATA_TO_INT(parserStackPop(stack)) >= 0){}
	parserStackInit(stack);
}

int main()
{
    ParserStackPtr semanticStack = NULL;
	float value = 3.14;
	int result = 1;
    parserStackPush(&semanticStack, STACK_FLOAT_TO_DATA(value));
    parserStackPush(&semanticStack, STACK_INT_TO_DATA(result));
    printf("Value: %d\n", STACK_DATA_TO_INT(parserStackPop(&semanticStack)));
    printf("Value: %f\n", STACK_DATA_TO_FLOAT(parserStackPeek(&semanticStack)));
    parserStackFree(&semanticStack);
    return 0;
}
