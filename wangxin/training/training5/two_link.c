#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  

typedef struct str  
{  
     char name[10];  
     int age;  
     struct str *next;  
}str;  

str *insert_list(str *temp,char name[],int age)  
{  
     str *p = (str*)malloc(sizeof(str));  
     strcpy(p->name,name);  
     p->age = age;  
     p->next = temp;  
     temp = p;  
     return temp;  
}  

int display_list(str *p)  
{  
    printf("  output :\n");  
    while(p)  
    {  
	 printf("name:%s   age:%d\n",p->name,p->age);  
         p = p->next;  
    }
    printf("\n");
}  
  
int main()  
{  
    str *Man = NULL;  
    str *Woman = NULL;  

    Man = insert_list(Man,"zhangsan",12);  
    Man = insert_list(Man,"lisi",12);  
    Man = insert_list(Man,"zhaosan",13);  
    Man = insert_list(Man,"wangwu",15);  
    printf("boy");  
    display_list(Man);  
    
    Woman = insert_list(Woman,"zhangli",12);  
    Woman = insert_list(Woman,"shenli",12);  
    Woman = insert_list(Woman,"xiaoli",12);  
    printf("girl");  
    display_list(Woman);  
    
    return 0;  
}  

