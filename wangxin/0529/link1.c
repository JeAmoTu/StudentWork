#include <stdio.h>

struct node
{
    int num;
    struct node *next;
};


typedef struct node *link;

void create_link(link *head)
{
    *head = NULL;
}

void insert_head_link(link *head, link newnode)
{
    link temp = *head;
    newnode -> next = temp;
    *head = newnode;
}

int insert_tail_link(link *head, link newnode)
{
    link temp = *head;
    
    if(*head == NULL)
    {
        newnode -> next = NULL;
	*head = newnode;
	return 0;        
    }
    
    while(temp -> next != NULL)
    {
        temp = temp -> next;
    }

    temp -> next = newnode;
    newnode -> next = NULL;
    
}

int insert_mid_link(link *head,link newnode)
{
    link temp = *head;
    
    if(*head == NULL)
    {
        printf("error!\n");
	return -1;
    }

    while(temp != NULL)
    {
        if(temp -> num == 5)
	{
	    newnode -> next = temp -> next;
	    temp -> next = newnode;
	}
	temp = temp -> next;

    }

    return 0;
}

int delete_node(link *head, int num)
{
    if(NULL == *head)
    {
        printf("link error!\n");
	return -1;
    }

    link temp = *head;
    link temp1;
    
    if((*head) -> num == num)
    {
        *head = (*head) -> next;
	free(temp);
	return 0;
    }

    while(temp != NULL)
    {
        if(temp -> num == num)
	{
	    temp1 -> next = temp -> next;
	    free(temp);
	    return 0;
	}
        
	temp1 = temp;
	temp = temp -> next;
    }

    return -1;
}

#if 0
int delete_odd(link *head)
{
    if(*head == NULL)
    {
        printf("link error!\n");
	return -1;
    }

    if(((*head) -> num) % 2 != 0)
    {
        *head = (*head) -> next;
    }
    
    link temp = *head;
    link temp1;
    
    while(temp != NULL)
    {
        while((temp -> num) % 2 != 0)
	{
	    temp1 = temp -> next;
	    temp = temp -> next;
	}
	temp1 = temp;
	temp = temp->next;
    }
}
#endif
int len_link(link *head)
{
    int len = 0;
    link temp = *head;

    while(temp != NULL)
    {
        len++;
	temp = temp -> next;
    }
    
    return len;
}

int inversion_link(link *head)
{
    if(*head == NULL)
    {
        printf("link erroe!\n");
	return -1;
    }
    int len;
    len = len_link(head);
    
    if(len == 1)
    {
        printf("no needing!\n");
	return 0;
    }

    link temp = *head;
    link temp1 = (*head) -> next;
    link temp2 = temp1 -> next;

    if(len == 2)
    {
        temp1 -> next = temp;
	temp -> next = NULL;
	*head = temp1;
	return 0;
    }

    while(temp2 != NULL)
    {
        temp1 -> next = temp;
	temp = temp1;
	temp1 = temp2;
	temp2 = temp2 -> next;
    }

    temp1 -> next = temp;
    (*head) -> next = NULL;
    *head = temp1;
    
    return 0;
}

void display_link(link *head)
{
    link temp = *head;
    
    while(temp != NULL)
    {
        printf("%d\n",temp -> num);
        temp = temp -> next;
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
            return -1;
	}

	newnode -> num = i + 1;

	//insert_head_link(&head,newnode);
	insert_tail_link(&head,newnode);
    }

    newnode = (link)malloc(sizeof(struct node));

    if(NULL == newnode)
    {
        printf("malloc error!\n");
	exit(0);
    }

    newnode -> num = 11;
    insert_mid_link(&head,newnode);
    
    //delete_node(&head,10);
    //delete_odd(&head);
    inversion_link(&head);
    
    display_link(&head);

    return 0;
}
