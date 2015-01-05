#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define SUCCESS 0
#define ERROR -1

struct node
{
    int num;
    struct node *next;
};

typedef struct node * link;

int is_malloc(link test)
{
    if(test == NULL)
    {
        printf("malloc error!\n");
	return ERROR;
    }
}

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
    if(*head == NULL)
    {
        newnode->next = NULL;
	*head = newnode;
	return SUCCESS;
    }
    
    link temp = *head;
    
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
	return ERROR;
    }

    link temp = *head;

    while(temp != NULL)
    {
        if(temp->num == 5)
	{
	    newnode->next = temp->next;
	    temp->next = newnode;
	    
	    return SUCCESS;
	}

	temp = temp->next;
    }

    return ERROR;
}

int delete_link(link *head, int num)
{
    if(*head == NULL)
    {
        printf("link error!\n");
	return ERROR;
    }

    if((*head)->num == num)
    {
        link temp = *head;
	*head = (*head)->next;
	return SUCCESS;
	free(temp);
    }

    link temp = *head;
    link temp1 = temp->next;

    while(temp1 != NULL)
    {
        if(temp1->num == num)
	{
	    temp->next = temp1->next;
	    return SUCCESS;
	}
	
	temp = temp1;
	temp1 = temp1->next;

    }
}

int len_link(link *head)
{
    link temp = *head;
    int count = 0;

    while(temp != NULL)
    {
        count++;
	temp = temp->next;
    }

    return count;
}


int inversion_link(link *head)
{
    if(*head == NULL)
    {
        printf("link error!\n");
	return ERROR;
    }

    int len;
    len = len_link(head);

    if(len == 1)
    {
        printf("no needing!\n");
	return SUCCESS;
    }

    if(len == 2)
    {        
        link temp = (*head)->next;
	temp->next = *head;
	(*head)->next = NULL;
	*head = temp;
	
	return SUCCESS;
    }

    link start = *head;
    link temp = start->next;
    link end = temp ->next;;
    
    while(end != NULL)
    {
        temp->next = start;
	start = temp;
	temp = end;
	end = end->next;
    }

    temp->next = start;
    (*head)->next = NULL;
    *head = temp;
    
    return SUCCESS;
}

int dispaly_link(link *head)
{
    if(*head == NULL)
    {
        printf("link error!\n");
	return ERROR;
    }

    link temp = *head;

    while(temp != NULL)
    {
        printf("%d ",temp->num);
	temp = temp->next;
    }
    printf("\n");
}

int main()
{
    link head;   
    
    create_link(&head);
    
    link newnode;
    
    int i;
    
    for(i = 0; i< 10; i++)
    {
        newnode = (link)malloc(sizeof(struct node));
        
        is_malloc(newnode);

	newnode->num = i + 1;
	
	insert_head_link(&head,newnode);
	//insert_tail_link(&head,newnode);
    }
    
    delete_link(&head,3);
    
    newnode = (link)malloc(sizeof(struct node));

    is_malloc(newnode) ;

    newnode->num = 11;
    
    insert_mid_link(&head,newnode);

    inversion_link(&head);

    dispaly_link(&head);
    
    return 0;
}
