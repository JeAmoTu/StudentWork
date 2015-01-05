/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:      out
  Author:    Wanxin   Version: 1.0       Date: 2014.6.10
  Description:    该程序实现取车
  Others:         无
  Function List:  
                  out
		  取车
  History:        no
*************************************************/

#include <stdio.h>
#include <malloc.h>
#include "../../include/typedef.h"

/*************************************************
  Function:       out
  Description:    取车
  Calls:          charge time local_time
  Called By:      choose
  Input:          park_stack,temp_stack,wait_queue
  Output:         no
  Return:         no
  Others:         no
*************************************************/

void out(Stack *park_stack, Stack *temp_stack, Link_queue *wait_queue)
{
    int i;
    int j;
    long int car_num;

    printf("\t\033[40;36m请输入你的车牌号: \033[0m");
    scanf("%ld",&car_num);
    
    for(i = 0; i <= park_stack->top; i++)    //遍历停车栈
    {
        if(park_stack->p_num[i] == car_num) //判断要取车
	{
	    if(i == park_stack->top)        //是否最外面的车
	    {
	        if(is_empty_queue(wait_queue) == EMPTY_OK)  //是否有等待车辆
		{
                    charge(park_stack,i,car_num);  //出车
		    
		    (park_stack->top)--;        //无等待
		    
		    printf("\t\033[40;36m请输入任意键回主菜单: \033[0m");
		    scanf("%d",&i);

		    system("reset");
		    interface(park_stack,temp_stack,wait_queue);//主菜单
		}
		else
		{
                    charge(park_stack,i,car_num);   //出车
		    
		    Link p;

		    p = (Link)malloc(sizeof(struct link));
		    p = wait_queue->front;

		    park_stack->p_num[i] = p->num;    
		    wait_queue->front = wait_queue->front->next;//等待车进入
		    
		    if(wait_queue->front == NULL)
		    {
		        wait_queue->rear = NULL;
		    }
		    
		    struct tm *now_time;
		    time_t park_time;
		    time(&park_time);
		    now_time = localtime(&park_time);  
                    park_stack->i_time[i] = park_time;   //刚进入车计时
		    
		    printf("\t\033[0m请输入任意键回主菜单: \033[0m");
		    
		    scanf("%d",&i);

		    system("reset");
		    interface(park_stack,temp_stack,wait_queue);//主菜单
		}
	    }
	    else
	    {	
		charge(park_stack,i,car_num);   //出车

		for(j = park_stack->top; j > i; j--)
		{
		    push_temp_stack(temp_stack,                                                 park_stack->p_num[j],park_stack->i_time[j]);
		}           //进临时栈

		for(i; i < park_stack->top; i++)
		{
		    park_stack->p_num[i] =                                                      temp_stack->p_num[temp_stack->top];
		    
		    park_stack->i_time[i] =                                                     temp_stack->i_time[temp_stack->top];
		    
		    (temp_stack->top)--;
		}     //临时栈进去
	        
		if(is_empty_queue(wait_queue) == EMPTY_OK)//等待队列空
		{
		    (park_stack->top)--;
		    
		    printf("\t\033[40;36m请输入任意键回主菜单: \033[0m");
		    scanf("%d",&i);

		    system("reset");
		    interface(park_stack,temp_stack,wait_queue);//主菜单
		}
		else
		{
		    Link p;
		    
		    p = (Link)malloc(sizeof(struct link));
		    p = wait_queue->front;          //等待队列非空

		    park_stack->p_num[park_stack->top] = p->num;
		    wait_queue->front = wait_queue->front->next; //前移 
		    
		    if(wait_queue->front == NULL)
		    {
		        wait_queue->rear = NULL;
		    }
		    
		    struct tm *now_time;
		    time_t park_time;
		    time(&park_time);
		    now_time = localtime(&park_time);
                    park_stack->i_time[i] = park_time;  //刚进入车计时
		    
		    printf("\t\033[40;36m请输入任意键回主菜单: \033[0m");
		    scanf("%d",&i);

		    system("reset");
		    interface(park_stack,temp_stack,wait_queue);//主菜单
		}
	    }
	}
    }
    
    printf("\n\t\033[40;36m没有你要取的车,请核对车牌号！\033[0m\n\n");
    printf("\t\033[40;36m请输入任意键回主菜单: \033[0m");
    scanf("%d",&i);
    
    system("reset");
    interface(park_stack,temp_stack,wait_queue);//主菜单
}
