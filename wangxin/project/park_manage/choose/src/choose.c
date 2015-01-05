/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:      choose
  Author:    Wanxin   Version: 1.0       Date: 2014.6.10
  Description:    该程序实现选择功能
  Others:         无
  Function List:  
                  1.choose
		  选择功能
		  2.my_strcmp
		  比较两个字符串的大小
  History:        no
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../../include/typedef.h"

/*************************************************
  Function:       choose
  Description:    选择功能
  Calls:          my_strcmp
  Called By:      main
  Input:          park_stack,temp_stack,wait_queue
  Output:         no
  Return:         no
  Others:         no
*************************************************/

void choose(Stack *park_stack, Stack *temp_stack, Link_queue *wait_queue)
{
    char rec[10];
    
    printf("\t\033[40;36m请输入你的选择: \033[0m");
    scanf("%s",rec);

    if(my_strcmp(rec,"1") == 0)                       //比较输入
    {
        system("reset");
	park(park_stack,temp_stack,wait_queue);      //调用函数
    }
    else if(my_strcmp(rec,"2") == 0)
    {
        system("reset");
	out(park_stack,temp_stack,wait_queue);
    }
    else if(my_strcmp(rec,"3") == 0)
    {
        system("reset");
	see(park_stack,temp_stack,wait_queue);
    }
    else if(my_strcmp(rec,"4") == 0)
    {
        system("reset");
	printf("\n\033[40;36m感谢你使用新智停车管理系统,祝你旅途愉快！~^.^~\033[0m\n\n");
	exit(0);
    }
    else
    {
        printf("\t\033[40;36m选择错误,请正确选择你要使用的功能。\033[0m\n\n");
	choose(park_stack,temp_stack,wait_queue);
    }
}
