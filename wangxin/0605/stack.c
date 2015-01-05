#include <stdio.h>

#define SIZE_STACK 100

enum{FULL_OK,FULL_NO,PUSH_OK,PUSH_NO,EMPTY_OK,EMPTY_NO,POP_OK,POP_NO = -6};

struct q_stack
{
    int stack[SIZE_STACK];
    int top;
};

typedef struct q_stack Stack;

void init_stack(Stack *my_stack)
{
    my_stack->top = -1;
}

int is_full_stack(Stack *my_stack)
{
    if(my_stack->top == SIZE_STACK - 1)
    {
        return FULL_OK;
    }
    else
    {
        return FULL_NO;
    }
}

int is_empty_stack(Stack *my_stack)
{
    if(my_stack->top == -1)
    {
        return EMPTY_OK;
    }
    else
    {
        return EMPTY_NO;
    }
}

int push_stack(Stack *my_stack, int num)
{
    if(is_full_stack(my_stack) == FULL_NO)
    {
        (my_stack->top)++;
        my_stack->stack[my_stack->top] = num;
        return PUSH_OK;
    }
    else
    {
        return PUSH_NO;
    }
}

int pop_stack(Stack *my_stack)
{
    if(is_empty_stack(my_stack) == EMPTY_OK)
    {
        return POP_NO;
    }

    return my_stack->stack[(my_stack->top)--];
}

int main()
{
    int i;
    int pop_num;
    Stack my_stack;

    init_stack(&my_stack);
    
    for(i = 0; i < 10; i++)
    {
        if(is_full_stack(&my_stack) == FULL_OK)
	{
	    printf("the stack is full!\n");
	    exit(FULL_OK);
	}

	push_stack(&my_stack,i + 1);
    }
    
    for(i = 0; i < 10; i++)
    {
        if((pop_num = pop_stack(&my_stack)) == POP_NO)
	{
	    printf("the stack is empty!\n");
	    exit(POP_NO);
	}

	printf("the popnum is %d\n",pop_num);
    }

    return 0;
}
