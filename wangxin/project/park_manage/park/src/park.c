/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:      park
  Author:    Wanxin   Version: 1.0       Date: 2014.6.10
  Description:    该程序实现停车
  Others:         无
  Function List:  
                  park
		  该函数实现停车
  History:        no
*************************************************/

#include <stdio.h>
#include "../../include/typedef.h"

/*************************************************
  Function:       park
  Description:    停车
  Calls:          push_park_stack push_wait_queue 
  Called By:      choose
  Input:          park_stack,wait_queue,temp_stack
  Output:         no
  Return:         no
  Others:         no
*************************************************/

void park(Stack *park_stack, Stack *temp_stack, Link_queue *wait_queue)
{
    int top;
    char rec[10];
    long int car_num;

    if(is_full_stack(park_stack) == FULL_OK)  //是否满栈
    {
        printf("\t\033[40;36m当前车位已满,你是否要等待? \033[0m\033[40;31mY/N:\033[0m ");
	scanf("%s",rec);
        
	if((my_strcmp(rec,"Y") == 0)||(my_strcmp(rec,"y") == 0))
	{
	    printf("\n\t\033[40;36m请输入你的车牌号: \033[0m");
	    scanf("%ld",&car_num);
	    
	    push_link_queue(wait_queue,car_num);  //进入等候队列
	    
	    printf("\t\033[40;36m等待成功,当有人取车走时,你的车会自动停入！\033[0m\n\n");
	    printf("\t\033[40;36m请输入任意键回主菜单: \033[0m");
	    scanf("%s",rec);
	    
	    system("reset");
	    interface(park_stack,temp_stack,wait_queue);//主菜单
	}
	else
	{
	    system("reset");
	    interface(park_stack,temp_stack,wait_queue);  //主菜单
	}
    }
    else
    {
        struct tm *t;
	time_t park_time;
	
	time(&park_time);
	t = localtime(&park_time);

	printf("\t\033[40;36m请输入你的车牌号: \033[0m");
	scanf("%ld",&car_num);
	
	top = push_park_stack(park_stack,car_num,park_time); //停车
	
	printf("\n\t\033[40;36m停车成功！\033[0m\n\n");
	printf("\t\033[40;36m你的车位是第\033[40;31m%d\033[0m\033[40;36m位,你的车牌号为:\033[0m \033[40;31m%ld\033[0m\033[40;36m,\033[0m",top,car_num);
	printf("\033[40;36m你的停车时间为:\033[0m\033[40;31m %d:%d:%d\033[0m\033[40;36m.\033[0m\n\n",t->tm_hour,t->tm_min,t->tm_sec);
        printf("\t\033[40;36m请输入任意键回主菜单: \033[0m");
	scanf("%ls",&car_num);
        
	system("reset");
	interface(park_stack,temp_stack,wait_queue);  //主菜单
    }
}
