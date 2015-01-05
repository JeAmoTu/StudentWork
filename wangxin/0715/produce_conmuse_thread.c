#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MALLOC_ERROR 1
#define POP_OK 0
#define POP_NO -1
#define EMPTY_OK -2
#define EMPTY_NO -3

static pthread_mutex_t q_mutex;

typedef struct link
{
    char ch;
    int num;
    struct link *next;
}*Link;

typedef struct link_queue
{
    Link rear;
    Link front;
}Link_queue;

Link_queue my_queue;

int is_empty_queue(Link_queue *my_queue)
{
    if((my_queue->rear == NULL) && (my_queue->front == NULL))
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

void init_link_queue(Link_queue *my_queue)
{
    my_queue->rear = NULL;
    my_queue->front = NULL;
}

int push_link_queue(Link_queue *my_queue, char ch, int num)
{
    
    Link p;
    
    p = (Link)malloc(sizeof(struct link));
    is_malloc(p);
    
    p->ch = ch;
    p->num = num;
    if(my_queue->rear == NULL && my_queue->front == NULL)
    {
        my_queue->rear = p;
        my_queue->front = p;
	p->next = NULL;
        
	return 0;
    }

    my_queue->rear->next = p;
    p->next = NULL;
    my_queue->rear = p;

    return 0;
}


void display_queue(Link_queue * my_queue)
{
    Link p;
    p = (Link)malloc(sizeof(struct link));
    is_malloc(p);
    
    printf("now the produce line is");
    p = my_queue->front;
    
    while(p != NULL)
    {
	printf(" %c",p->ch);
	p = p->next;
    }
    printf("\n");
}

void *thread_handle0(void *arg)
{
    int i = 0;
    int num = 0;

    Link_queue *my_queue = (Link_queue *)arg;
    
    while(1)
    {
	char ch = 'A' + i;

	printf("in produce thread[0] produce char %c\n",ch);

        i++;
	
	if(i == 26)
	{
	    i = 0;
	}

	pthread_mutex_lock(&q_mutex,NULL);

        push_link_queue(my_queue,ch,num);

	display_queue(my_queue);

	pthread_mutex_unlock(&q_mutex,NULL);
        
	sleep(2);
    }
}

void *thread_handle1(void *arg)
{
    int i = 0;
    int num = 1;

    Link_queue *my_queue = (Link_queue *)arg;
    
    while(1)
    {
	char ch = 'A' + i;

	printf("in produce thread[1] produce char %c\n",ch);

        i++;
	
	if(i == 26)
	{
	    i = 0;
	}

	pthread_mutex_lock(&q_mutex,NULL);

        push_link_queue(my_queue,ch,num);

	display_queue(my_queue);

	pthread_mutex_unlock(&q_mutex,NULL);
        
	sleep(2);
    }
}

#if 1

int *thread_handle2(void *arg)
{
    Link_queue *my_queue = (Link_queue *)arg;
    
    Link p;
    p = (Link)malloc(sizeof(struct link));
    is_malloc(p);

    if(is_empty_queue(my_queue) == EMPTY_OK)
    {
        printf("the produce is empty!\n");
        return 0;
    }
    
    while(1)
    {
        pthread_mutex_lock(&q_mutex,NULL);

	p = my_queue->front;
        my_queue->front = my_queue->front->next;
	my_queue->rear = my_queue->rear->next;
        printf("in produce thread[%d] get char %c\n\n",p->num,p->ch);
        free(p);

        pthread_mutex_unlock(&q_mutex,NULL);
    
        sleep(1);
    }
    
    return NULL;
}

#endif

int main()
{
    int i;
    pthread_t pid[3];
    pthread_mutex_init(&q_mutex,NULL);

    init_link_queue(&my_queue);
   
    int ret = pthread_create(&pid[0],NULL,thread_handle0,&my_queue);
    ret = pthread_create(&pid[2],NULL,thread_handle2,&my_queue);
    ret = pthread_create(&pid[1],NULL,thread_handle1,&my_queue);

    for(i = 0; i < 3; i++)
    {
        pthread_join(pid[i],NULL);
    }

    return 0;
}


