#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"

void choose();

int my_strcmp(char *src, char *str)
{
    int i;

    while((*src  != '\0') && (*str != '\0'))
    {
        if(*src == *str)
	{
	    src++;
            str++;           //相同继续遍历
	}
	
	if(*src > *str)
	{
	    return 1;         //大返回1
	}

        if(*src < *str)
	{
	    return -1;
	}
    }

    if(*src == '\0')
    {
        if(*str == '\0')
	{
	    return 0;
	}
	else
	{
	    return -1;
        }
    }
    else
    {
        return 1;
    }
}

void my_strcpy(char *dest, const char *src)
{
    while(*src != '\0')
    {
        *dest = *src;        //遍历字符串赋值
	dest++;
	src++;
    }

    *dest = '\0';
}

void is_malloc(link test)
{
    if(test == NULL)
    {
         printf("Mallo error!\n");   //为空打印退出
	 exit(MALLOC_ERROR);
    }
}

void interface(link *head, link newfriend)
{
    printf("\033[40;36m\t\t+===============================================+\n\033[0m");
    printf("\033[40;36m\t\t|\t\t\t\t\t\t|\n\033[0m");
    printf("\033[40;36m\t\t|\t\t多功能电子通讯录\t\t|\n\033[0m");
    printf("\033[40;36m\t\t|\t\t\t\t\t\t|\n\033[0m");
    printf("\033[40;36m\t\t|\t\t\t\t\t\t|\n\033[0m");
    printf("\033[40;36m\t\t|\t\t\t\t\t版本:1.0|\n\033[0m");
    printf("\033[40;36m\t\t|-----------------------------------------------|\n\033[0m");
    printf("\033[40;36m\t\t|\t1:添加好友信息    2:查看好友信息\t|\n\033[0m");
    printf("\033[40;36m\t\t|-----------------------------------------------|\n\033[0m");
    printf("\033[40;36m\t\t|\t3:搜索好友信息    4:删除好友信息\t|\n\033[0m");
    printf("\033[40;36m\t\t+===============================================+\n\033[0m");
    printf("\n\t\t\033[40;36m请选择你要实现的功能:\033[0m");
    printf("\n\n\t\t\033[40;36mINSERT/DISPLAY/SEARCH/DELETE: \033[0m");
    
    choose(head,newfriend);   //函数调用
}


void create(link *head)
{
    *head = (link)malloc(sizeof(struct friend));
    is_malloc(*head);

    (*head)->next = *head;    //双向链表
    (*head)->prior = *head;
    
    (*head)->Id = 1;
    my_strcpy((*head)->Address,"A");
    my_strcpy((*head)->Phone_num,"B");   //赋值
    my_strcpy((*head)->Firm_num,"C");
    my_strcpy((*head)->Name,"D");

}

void input(link newfriend)
{
    printf("\033[40;36m请输入你要添加的好友信息:\033[0m\n");
    printf("\033[40;36mId:        \033[0m");
    scanf("%ld",&(newfriend->Id));
    setbuf(stdin,NULL);
    printf("\033[40;36m姓名:      \033[0m");
    scanf("%s",newfriend->Name);
    setbuf(stdin,NULL);
    printf("\033[40;36m手机号码:  \033[0m");
    scanf("%s",newfriend->Phone_num);
    setbuf(stdin,NULL);
    printf("\033[40;36m家庭住址:  \033[0m");
    scanf("%s",newfriend->Address);
    setbuf(stdin,NULL);
    printf("\033[40;36m公司电话:  \033[0m");
    scanf("%s",newfriend->Firm_num);
    setbuf(stdin,NULL);
}

void output(link temp)
{
    printf("\033[40;36mId:        %ld\033[0m\n",temp->Id);
    printf("\033[40;36m姓名:      %s\033[0m\n",temp->Name);
    printf("\033[40;36m手机号码:  %s\033[0m\n",temp->Phone_num);
    printf("\033[40;36m家庭住址:  %s\033[0m\n",temp->Address);
    printf("\033[40;36m公司号码:  %s\033[0m\n\n",temp->Firm_num);

}



void insert(link *head, link newfriend)
{
    
    char test;
    
    newfriend = (link)malloc(sizeof(struct friend));
    is_malloc(newfriend);
    input(newfriend);            //输入新结点数据
    
    link temp = (*head)->next;
    
    while(temp != *head)
    {
        if(my_strcmp(newfriend->Name,temp->Name) == -1)
        {
	        //QIANMIAN
	        newfriend->next = temp;
	        temp->prior->next = newfriend;    //姓名小于头用头插
	        newfriend->prior = temp->prior;
	        temp->prior = newfriend;
		break;
        }

        if(my_strcmp(newfriend->Name,temp->Name) == 0) //姓名相同比较ID
        {
            if(newfriend->Id < temp->Id)
	    {
	        //QIANMIAN
	        newfriend->next = temp;           //ID小头插
	        temp->prior->next = newfriend;
	        newfriend->prior = temp->prior;
	        temp->prior = newfriend;
		break;
	    }
	    else
            {
                
		newfriend->prior = temp;
                newfriend->next = temp->next;
		temp->next->prior = newfriend;   //ID大后插
		temp->next = newfriend;
                
	        break;
	    }
        } 
	
	if(temp->next == *head)
	{
	    newfriend->prior = temp;
	    newfriend->next = temp->next;
	    temp->next->prior = newfriend; //插到最后
	    temp->next = newfriend;     
	    break;
	}

        if(my_strcmp(newfriend->Name,temp->Name) == 1)
        {
            temp = temp->next;             //最大姓名
	}
    }

    if(temp == *head)
    {
        temp->next = newfriend;
        newfriend->prior = temp;
        newfriend->next = *head;         //第一个数据
        (*head)->prior = newfriend;
    }

    printf("\n\033[40;36m添加成功！\033[0m\n\n");
    printf("\033[40;36m你要继续添加吗？ Y/N: \033[0m");
    scanf("%c",&test);
    setbuf(stdin,NULL);

    if(test == 'Y')
    {
        system("reset");
	insert(head,newfriend);
    }
    else
    {
        system("reset");
	interface(head,newfriend);
    }
}

void display(link *head, link newfriend)
{
    char rec;
    link temp = (*head)->next;

    printf("\033[40;36m已拥有好友的信息:\033[0m\n\n");

    while(temp != *head)
    {
        output(temp);            //打印信息
	temp = temp->next;       //遍历链表
    }
    printf("\033[40;36m请输入任意键返回主菜单: \033[0m");
    setbuf(stdin,NULL);
    scanf("%c",&rec);
    system("reset");
    interface(head,newfriend);    //函数调用
}

void search(link *head, link newfriend)
{
   
    char rec;
    int count = 0;

    printf("\033[40;36m请输入你要查找的好友的姓名: \033[0m");
    
    char aim_name[20];
    setbuf(stdin,NULL);
    scanf("%s",aim_name);
   
    link temp = (*head)->next;
    
    while(temp != *head)
    {
         if(my_strcmp(aim_name,temp->Name) == 0)
	 {
	     count++;
	     output(temp);
	 }     
	 
	 temp = temp->next;
    }
    
    if(count == 0)
    {
        
	printf("\n\033[40;36m查找失败！\033[0m\n\n");
	printf("\033[40;36m没有你要查找的好友信息！\n\033[0m");
	printf("\n\033[40;36m请输入任意键返回主菜单: \033[0m");
	setbuf(stdin,NULL);
	scanf("%c",&rec);
	system("reset");
	interface(head,newfriend);
    } 
    else
    {
	printf("\n\033[40;36m查找成功！\033[0m\n\n");
	printf("\n\033[40;36m请输入任意键返回主菜单: \033[0m");
	setbuf(stdin,NULL);
	scanf("%c",&rec);
	system("reset");
	interface(head,newfriend);
    }
}

void delete(link *head, link newfriend)
{
    char rec;
    long int id;
    int count = 0;
    char name[20];
    
    printf("\033[40;36m请输入你要删除的好友的姓名: \033[0m");
    setbuf(stdin,NULL);
    scanf("%s",name);

    link temp = (*head)->next;

    while(temp != *head)
    {
         if(my_strcmp(temp->Name,name) == 0) //遍历链表
	 {
	     count++;                        //出现次数计数
	 }
	 temp = temp->next;
    }

    if(count == 0)
    {
        printf("\033[40;36m\n没有这个好友！\n\n\033[0m");
        printf("\033[40;36m请输入任意键返回主菜单: \033[0m");
	setbuf(stdin,NULL);
	scanf("%c",&rec);
	system("reset");
	interface(head,newfriend);   
    }

    else if(count == 1)
    {
        temp = (*head)->next;
        
	while(temp != *head)
	{
	    if((my_strcmp(temp->Name,name)) == 0)
	    {
		temp->prior->next = temp->next;       //删除结点
		temp->next->prior = temp->prior;
		printf("\033[40;36m\n删除成功！\033[0m\n");
		printf("\033[40;36m请输入任意键返回主菜单: \033[0m");
		setbuf(stdin,NULL);
		scanf("%c",&rec);
		system("reset");
		interface(head,newfriend);
	    }
	    temp = temp->next;
	}
    }
    
    else
    {
        printf("\n\033[40;36m你输入的名字有下面几个人:\n\n\033[0m");
	temp = (*head)->next;
        
	while(temp != *head)
	{
	    if(my_strcmp(temp->Name,name) == 0)   //打印结点
	    {
	        output(temp);
		printf("\n");
	    }
	    
	    temp = temp->next;
	}

	printf("\033[40;36m请输入你要删除的好友的ID: \033[0m");
        setbuf(stdin,NULL);
	scanf("%ld",&id);
        
	temp = (*head)->next;

	while(temp != *head)
	{
	    if(temp->Id == id)
	    {
	        temp->prior->next = temp->next;   //删除结点
		temp->next->prior = temp->prior;
		printf("\033[40;36m\n删除成功！\033[0m\n\n");
		printf("\033[40;36m请输入任意键返回主菜单: \033[0m");
		setbuf(stdin,NULL);
		scanf("%c",&rec);
		system("reset");
		interface(head,newfriend);
	    }
	    
	    temp = temp->next;
	}
    }
}


void choose(link *head, link newfriend)
{
    char rec[10];
    char func[10];

    scanf("%s",func);                  //字符串用来判断
    setbuf(stdin,NULL);

    if(my_strcmp(func,"INSERT") == 0)  //判断字符串
    {
        system("reset");               //清屏
	insert(head,newfriend);        //函数调用
    }
    
    else if(my_strcmp(func,"DISPLAY") == 0)
    {
        system("reset");
	display(head,newfriend);
    }
    
    else if(my_strcmp(func,"SEARCH") == 0)
    {
        system("reset");
        search(head,newfriend);
    }
    else if(my_strcmp(func,"DELETE") == 0)
    {
        system("reset");
	delete(head,newfriend);
    }
    else
    {
        printf("\n\t\t\033[40;36m选择有误！\n\033[0m");
        printf("\n\t\t\033[40;36m请输入任意键返回主菜单或者输入“EXIT”退出程序\n\t\t:\033[0m");
        scanf("%s",rec);
	
	if(my_strcmp(rec,"EXIT") == 0)  //退出程序
	{
	    system("reset");
	    exit(SUCCESS);
	}
	else
	{
	    system("reset");
	    interface(head,newfriend);
	}
    }
}




int main()
{
    link head;
    link newfriend;
    
    create(&head);              //创建结点
    interface(&head,newfriend); //函数调用

    return 0;
}
