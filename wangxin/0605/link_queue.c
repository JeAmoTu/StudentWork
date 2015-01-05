#include <stdio.h>
#define MALLOC_ERROR 1
#define POP_OK 0
#define POP_NO -1
#define EMPTY_OK -2
#define EMPTY_NO -3

typedef struct link
{
    int queue;
    struct link *next;
}*Link;

typedef struct link_queue
{
    Link rear;
    Link front;
}Link_queue;

int is_empty_queue(Link_queue *my_link_queue)
{
    if((my_link_queue->rear == NULL) && (my_link_queue->front == NULL))
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

void init_link_queue(Link_queue *my_link_queue)
{
    my_link_queue->rear = NULL;
    my_link_queue->front = NULL;
}

void push_link_queue(Link_queue *my_link_queue, int num)
{
    
    Link p;
    
    p = (Link)malloc(sizeof(struct link));
    is_malloc(p);
    
    p->queue = num;

    if(my_link_queue->rear == NULL)
    {
        my_link_queue->rear = p;
        my_link_queue->front = p;
	p->next = NULL;
    }

    my_link_queue->rear->next = p;
    p->next = NULL;
    my_link_queue->rear = p;

}

int pop_link_queue(Link_queue *my_link_queue)
{
    Link p;
    p = (Link)malloc(sizeof(struct link));
    is_malloc(p);

    if(is_empty_queue(my_link_queue) == EMPTY_OK)
    {
        return POP_NO;
    }
    
    p = my_link_queue->front;
    my_link_queue->front = my_link_queue->front->next;

    return p->queue;
}

int main()
{
    int i;
    int pop_num;
    Link_queue my_link_queue;

    init_link_queue(&my_link_queue);
    
    for(i = 0; i < 10; i++)
    {
        push_link_queue(&my_link_queue,i + 1);
    }
    
    for(i = 0; i < 10; i++)
    {
        if((pop_num = pop_link_queue(&my_link_queue)) == POP_NO)
	{
	    printf("queue is empty!\n");
	    exit(EMPTY_OK);
	}
	else
	{
	    printf("the pop_num is %d\n",pop_num);
	}
    }
    return 0;
}
