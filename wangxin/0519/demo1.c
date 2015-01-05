#include<stdio.h>
#include<malloc.h>
#define LEN sizeof(struct list)
#define MALLOC_ERROR 0 
struct list
{
   long num;
   struct list *next;
};

int n;

void is_malloc(struct list *p)
{
    if(p == NULL)
    {
        printf("malloc error!\n");
	exit(MALLOC_ERROR);
    }
}

struct list *creat(void)
{
    struct list * head;
    struct list * p1;
    struct list * p2;

    n = 0;

    p1 = p2 = (struct list * )malloc(LEN);
    
    is_malloc(p1);
    is_malloc(p2);
    
    scanf("%ld",& p1 -> num);
    
    head = NULL;
    
    while(p1 -> num != 0)
    {
        n = n + 1;
	
	if(n == 1)
	{
	    head = p1;
	}
	
	else
	{
	    p2 -> next = p1;
	}
	
	p2 = p1;
	p1 = (struct list *)malloc(LEN);
	is_malloc(p1);
	scanf("%ld",& p1 -> num);
    }
    
    p2 -> next = NULL;
    
    return head;
}

void print(struct list *head)
{
    struct list * p;
    
    printf("\nNow,these %d record are :\n",n);
    p = head;
    
    if(head != NULL)
    
    do
    {
        printf("%ld\n",p -> num);
	p = p -> next;
    }
    while(p != NULL);
}

struct list *insert(struct list *head,struct list *stud)
{
    struct list *p0;
    struct list *p1;
    struct list *p2;

    p1 = head;
    p0 = stud;

    if(head == NULL)
    {
        head = p0;
	p0 -> next = NULL;
    }
    
    else
    {
        while ((p0 -> num > p1 -> num) && (p1 -> next != NULL))
	{
	    p2 = p1;
	    p1 = p1 -> next;
	}
	
	if(p0 -> num <= p1 -> num)
	{
	    if(head == p1)
	    {
	        head = p0;
	    }
	    
	    else
	    {
	        p2 -> next = p0;
		p0 -> next = p1;
	    }
	}
	
	else
	{
	    p1 -> next = p0;
	    p0 -> next = NULL;
	}
    }
    
    n = n + 1;
    
    return head;
}

int main()
{
    
    struct list *head;
    struct list *stu;
    
    printf("please input record:\n");
    head = creat();
    print(head);
    
    printf("please input insert record:\n");
    stu = (struct list *)malloc(LEN);
    is_malloc(stu);
    scanf("%ld",& stu -> num);

    while(stu -> num != 0)
    {
        head = insert(head,stu);
	print(head);
	printf("please input the insert record:\n");
	stu = (struct list *)malloc(LEN);
        is_malloc(stu);
	scanf("%ld",& stu -> num);
    }

    return 0;
}



