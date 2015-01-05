#include<stdio.h>

struct student
{
    char *name;
    int num;
}stu1;

int main()
{
    //stu1.name = "wangxin";
    //stu1.num = 208120630;

    struct student *p;
    p = &stu1;
    
    p->name = "wangxin";
    p->num = 208120630;

    printf("stu1's name is %s.\n",p->name);
    printf("stu1's number is %d.\n",p->num);
    
    return 0;
}
