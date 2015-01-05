#include <stdio.h>

#define SIZE_STACK 100

enum{FULL_OK,FULL_NO,PUSH_OK,PUSH_NO,EMPTY_OK,EMPTY_NO,POP_OK,POP_NO = -6};

struct q_queue
{
    int queue[SIZE_STACK];
    int rear;
    int front;
};

typedef struct q_queue Stack;

void init_queue(Stack *my_queue)
{
    my_queue->front = -1;
    my_queue->rear = -1;
}

int is_full_queue(Stack *my_queue)
{
    if(my_queue->rear == SIZE_STACK - 1)
    {
        return FULL_OK;
    }
    else
    {
        return FULL_NO;
    }
}

int is_empty_queue(Stack *my_queue)
{
    if((my_queue->rear == -1) && (my_queue->front == -1))
    {
        return EMPTY_OK;
    }
    else
    {
        return EMPTY_NO;
    }
}

int push_queue(Stack *my_queue, int num)
{
    if(is_full_queue(my_queue) == FULL_NO)
    {
        (my_queue->rear)++;
        my_queue->queue[my_queue->rear] = num;
        return PUSH_OK;
    }
    else
    {
        return PUSH_NO;
    }
}

int pop_queue(Stack *my_queue)
{
    if(is_empty_queue(my_queue) == EMPTY_OK)
    {
        return POP_NO;
    }

    return my_queue->queue[++(my_queue->front)];
}

int main()
{
    int i;
    int pop_num;
    Stack my_queue;

    init_queue(&my_queue);
    
    for(i = 0; i < 10; i++)
    {
        if(is_full_queue(&my_queue) == FULL_OK)
	{
	    printf("the queue is full!\n");
	    exit(FULL_OK);
	}

	push_queue(&my_queue,i + 1);
    }
    
    for(i = 0; i < 10; i++)
    {
        if((pop_num = pop_queue(&my_queue)) == POP_NO)
	{
	    printf("the queue is empty!\n");
	    exit(POP_NO);
	}

	printf("the popnum is %d\n",pop_num);
    }

    return 0;
}
