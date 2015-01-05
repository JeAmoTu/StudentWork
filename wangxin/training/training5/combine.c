#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  

struct stu  
{  
     char name[10];  
     int age;  
     struct stu *next;  
};  

typedef struct stu * link;

link insert_list(link temp,char name[],int age)  
{  
     link p = (link)malloc(sizeof(struct stu));  
     strcpy(p->name,name);  
     p->age = age;  
     p->next = temp;  
     temp = p;  
     return temp;  
}  

int display_list(link p)  
{  
    printf("out:\n");  
    while(p)  
    {  
         printf("name:%s   age:%d\n",p->name,p->age);  
         p = p->next;  
    }  
}  

link connect(link q,link p)  
{  
    link temp = NULL;  
    temp = q;  
    
    if(temp == NULL)  
    {  
        return p;  
    }  
    
    while(temp->next != NULL)  
    {  
        temp = temp->next;  
    }  
    
    temp->next = p;  
    
    return q;  
}  

link rank_list(link p)  
{  
   link temp = p;  
   link ptr =  p;  
   int  between = 0;  
   char string[10];  
   
   while(temp->next)  
   {  
       while(ptr->next)  
       {  
           if((ptr->age)>(ptr->next->age))  
           {  
               between = ptr->age;  
               ptr->age = ptr->next->age;  
               ptr->next->age = between;  
               strcpy(string,ptr->name);  
               strcpy(ptr->name,ptr->next->name);  
               strcpy(ptr->next->name,string);  
           }  
           ptr = ptr->next;  
       }  
       temp = temp->next;  
       ptr = p;  
   }  
   return p;  
}  

int main()  
{  
    link student = NULL;  
    link Man = NULL;  
    link Woman = NULL;  
    
    Man = insert_list(Man,"zhangsan",14);  
    Man = insert_list(Man,"lisi",13);  
    Man = insert_list(Man,"zhaosan",12);  
    Man = insert_list(Man,"wangwu",15);  
    Woman = insert_list(Woman,"zhangli",16);  
    Woman = insert_list(Woman,"shenli",10);  
    Woman = insert_list(Woman,"xiaoli",11);  
    
    student=connect(Man,Woman);  
    student=rank_list(student);  
    
    printf("student  ");  
    display_list(student);  
    
    return 0;  
}  
