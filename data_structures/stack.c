#define STACK_INT_TO_DATA(x) (ParserStackData)((int)x)
#define STACK_TERM_TO_DATA(x) (ParserStackData)((Term_type)x)
#define STACK_SYMTABLE_TO_DATA(x) (ParserStackData)((SymTableBinTreePtr)x)
#define STACK_TOKEN_TO_DATA(x) (ParserStackData)((Token)x)
#define STACK_TOKEN_TYPE_TO_DATA(x) (ParserStackData)((Token_type)x)

#define STACK_DATA_TO_INT(x) ((int)x.result)
#define STACK_DATA_TO_TERM(x) ((Term_type)x.TERM_NONTERM)
#define STACK_DATA_TO_SYMTABLE(x) ((SymTableBinTreePtr)x.SYM_TABLE)
#define STACK_DATA_TO_TOKEN(x) ((Token)x.token)
#define STACK_DATA_TO_TOKEN_TYPE(x) ((Token_type)x.tokenType)

typedef union {
	int result;
	Term_type TERM_NONTERM;
	SymTableBinTreePtr SYM_TABLE;
	Token token;
	Token_type tokenType;
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
    parserStackPush(semanticStack, STACK_TOKEN_TO_DATA(currentToken));
    parserStackPush(semanticStack, STACK_TERM_TO_DATA(GrammmarExprLeftRuleList[PREC_GRAMM_RULES_TO_RULE(found)]));
    STACK_DATA_TO_TERM(parserStackPeek(&semanticStack));
    parserStackFree(&semanticStack);
    return 0;
}
