#include <stdio.h>
#define MALLOC_ERROR 1
#define POP_OK 0
#define POP_NO -1
#define EMPTY_OK -2
#define EMPTY_NO -3

typedef struct link
{
    int stack;
    struct link *next;
}*Link;

typedef struct link_stack
{
    Link top;
}Link_stack;

int is_empty_stack(Link_stack *my_link_stack)
{
    if(my_link_stack->top == NULL)
    {
        return EMPTY_OK;
    }
    else
    {
        return EMPTY_NO;
    }
}

int is_malloc(Link temp)
{
    if(temp == NULL)
    {
        printf("malloc error!\n");
	exit(MALLOC_ERROR);
    }
}

void init_link_stack(Link_stack *my_link_stack)
{
    my_link_stack->top = NULL;
}

void push_link_stack(Link_stack *my_link_stack, int num)
{
    
    Link p;
    p = (Link)malloc(sizeof(struct link));
    is_malloc(p);
    
    p->stack = num;
    p->next = my_link_stack->top;
    my_link_stack->top = p;
}

int pop_link_stack(Link_stack *my_link_stack)
{
    Link p;
    p = (Link)malloc(sizeof(struct link));
    is_malloc(p);

    if(is_empty_stack(my_link_stack) == EMPTY_OK)
    {
        return POP_NO;
    }
    
    p = my_link_stack->top;
    my_link_stack->top = my_link_stack->top->next;

    return p->stack;
}

int main()
{
    int i;
    int pop_num;
    Link_stack my_link_stack;

    init_link_stack(&my_link_stack);
    
    for(i = 0; i < 10; i++)
    {
        push_link_stack(&my_link_stack,i + 1);
    }
    
    for(i = 0; i < 10; i++)
    {
        if((pop_num = pop_link_stack(&my_link_stack)) == POP_NO)
	{
	    printf("stack is empty!\n");
	    exit(EMPTY_OK);
	}
	else
	{
	    printf("the pop_num is %d\n",pop_num);
	}
    }
    return 0;
}
