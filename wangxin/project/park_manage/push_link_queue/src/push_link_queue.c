/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:      count_9
  Author:    Wanxin   Version: 1.0       Date: 2014.6.1
  Description:    该程序实现入队列
  Others:         无
  Function List:  
                  push_link_queue
		  入队列
  History:        no
*************************************************/

#include <stdlib.h>
#include "../../include/typedef.h"

/*************************************************
  Function:       push_link_queue
  Description:    入队列
  Calls:          no
  Called By:      park
  Input:          wait_queue car_num
  Output:         no
  Return:         no
  Others:         no
*************************************************/

void push_link_queue(Link_queue *wait_queue, long int car_num)
{
    Link p;                                     //定义中间变量

    p = (Link)malloc(sizeof(struct link));
    is_malloc(p);

    p->num = car_num;

    if((wait_queue->rear == NULL) && (wait_queue->front == NULL))
    {
        wait_queue->rear = p;
	wait_queue->front = p;             //队列空都指向第一个
	p->next = NULL;
    }

    wait_queue->rear->next = p;            //尾插入队列
    p->next = NULL;
    wait_queue->rear = p;
}
