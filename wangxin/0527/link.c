#include <stdio.h>
#define MALLOC_ERROR -1

struct node
{
    int num;
    struct node *next;
};

typedef struct node * link;

void create_link(link *head)
{
    *head = NULL;
}


void insert_head_link(link *head, link newnode)
{
    link temp = *head;
    newnode->next = temp;
    *head = newnode;
}

int insert_tail_link(link *head, link newnode)
{
    link temp = *head;
    
    if(*head == NULL)
    {
        newnode->next = NULL;
        *head = newnode;
	return 0;
    }

    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newnode;
    newnode->next = NULL;
}

int insert_mid_link(link *head, link newnode)
{
    if(*head == NULL)
    {
        printf("link error!\n");
	return -1;
    }
    
    link temp = *head;
    
    while(temp != NULL)
    {
        if(temp->num == 5)
	{
	    newnode->next = temp->next;
	    temp->next = newnode;
	    return 0;
	}
	
	temp = temp->next;
    }
    
    return -1;
}

void display_link(link *head)
{
    link temp = *head;
    
    while(temp != NULL)
    {
        printf("%d\n",temp->num);
	temp = temp->next;
    }
}

int main()
{
    link head;
    create_link(&head);

    link newnode;
    int i;
    for(i = 0; i < 10; i++)
    {
        newnode = (link)malloc(sizeof(struct node));

	if(NULL == newnode)
	{
	    printf("malloc error!\n");
	    exit(MALLOC_ERROR);
	}

	newnode->num = i + 1;
        
	//insert_head_link(&heaf,newnode);
	insert_tail_link(&head,newnode);
    }
    
    newnode = (link)malloc(sizeof(struct node));
    if(NULL == newnode)
    {
        printf("malloc error!\n");
	exit(MALLOC_ERROR);
    }

    newnode->num = 11;
    insert_mid_link(&head,newnode);

    display_link(&head);
    
    return 0;
}








