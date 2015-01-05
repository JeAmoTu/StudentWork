/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:      see
  Author:    Wanxin   Version: 1.0       Date: 2014.6.10
  Description:    该程序查看停车场情况
  Others:         无
  Function List:  
                  see
		  查看停车场情况
  History:        no
*************************************************/

#include <stdio.h>
#include "../../include/typedef.h"

/*************************************************
  Function:       see
  Description:    查看停车场清况
  Calls:          conut_wait_queue time 
                  localtime  interface
  Called By:      choose
  Input:          park_stack,temp_stack,wait_queue
  Output:         no
  Return:         no
  Others:         no
*************************************************/

void see(Stack *park_stack, Stack *temp_stack, Link_queue *wait_queue)
{
    int i;
    int j;
    int count;
    int pop_num;
    
    j = park_stack->top;
    count = count_wait_queue(wait_queue);   //遍历等待队列

    printf("\t\033[40;36m当前停车场的情况:\033[0m\n\n");
    printf("\t\033[40;36m停车场一共有\033[0m\033[40;31m10\033[0m\033[40;36m个车位,当前已使用\033[0m\033[40;31m%d\033[0m\033[40;36m个车位，等待区有\033[0m\033[40;31m%d\033[0m\033[40;36m辆车在等候停车。\033[0m\033[0m\n\n",(park_stack->top) + 1,count);
    
    for(i = park_stack->top + 1; i > 0; i--)
    {
            struct tm *t;                           
	    time_t park_time;
	    
	    park_time = park_stack->i_time[j--];
	    t = localtime(&park_time);                //取出时间
	    pop_num = pop_park_stack(park_stack,i);   //取栈值

	    printf("\t\033[40;36m第\033[0m\033[40;31m%d\033[0m\033[40;36m个车位的车牌号是:\033[0m\033[40;31m %ld\033[0m\033[40;36m,\033[0m",i,pop_num);
	    printf("\033[40;36m停车时间为:\033[0m \033[40;31m%d:%d:%d\033[0m\033[40;36m.\033[0m\n\n",t->tm_hour,t->tm_min,t->tm_sec);
	
    }

    printf("\t\033[40;36m请输入任意键回主菜单: \033[0m");
    scanf("%d",&i);
    system("reset");
    interface(park_stack,temp_stack,wait_queue);   //返回主界面

}
