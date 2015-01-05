#include <stdio.h>  
#include <stdlib.h>

#define MALLOC_ERROR -1

struct node  
{  
    int num;  
    struct node *next;  
};  

typedef struct node * link;

void creat_num(link *head)  
{  
    *head = (link)malloc(sizeof(struct num));  
    
    if(head == NULL)
    {
        printf("malloc error!\n");
	exit(MALLOC_ERROR);
    }
    
    (*head)->num = -1;
    (*head)->next = *head;
  
}  

void in_num(int num)  
{  
    struct num *p=(struct num *)malloc(sizeof(struct num));  
    p->num=num;  
    p->next=head;  
    head=p;  
}  

void rm_num(int n)  
{  
    link p = NULL;  
    link temp=NULL;  
    int i = 10;  
    int count = 0;  
    
    while(i>1)   
    {  
          
        if(p==NULL)  
        {  
            p = head;  
        }  
        
	count++;  
        
	if(count == n)  
        {  
            if(head == p)  
            {  
                temp = head;  
                head = head->next;  
                p = head;  
                free(temp);  
                temp = NULL;  
            }  
            else  
            {  
                temp->next = p->next;  
                temp = p;  
                p = p->next;  
                free(temp);  
                temp = NULL;  
            }   
            i--;  
            count = 0;  
        }  
        else  
        {  
            temp = p;  
            p = p->next;  
        }  
    }  
}  

void display_num()  
{  
       link p = head;  
       
       while(p)  
       {  
           printf("%d",p->num);  
           p = p->next;  
       }  
       printf("\n");  
}

int main()  
{  
    int i=0;  
    int delete;  
    link head;

    printf("please input a num:");  
    scanf("%d",&delete);  
    
    if(delete < 0)  
    {  
        printf("input error!\n");  
    }  
    
    printf("delete=%d\n",delete);  
    
    creat_link(&head);  
    
    for(i=10;i>0;i--)  
    {  
         in_num(i);  
    }  
    
    display_num();  
    rm_num(delete);  
    printf("output:");  
    display_num();  
    
    return 0;   
}  
