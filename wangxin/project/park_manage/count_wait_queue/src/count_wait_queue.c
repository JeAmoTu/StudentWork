/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:      count_wait_queue
  Author:    Wanxin   Version: 1.0       Date: 2014.6.10
  Description:    该程序实现遍历等待队列
  Others:         无
  Function List:  
                  count_wait_queue
		  遍历队列,返回队列值个数
  History:        no
*************************************************/

#include "../../include/typedef.h"

/*************************************************
  Function:       conut_wait_queue
  Description:    遍历队列
  Calls:          no
  Called By:      see
  Input:          wait_queue
  Output:         no
  Return:         0  count
  Others:         no
*************************************************/

int count_wait_queue(Link_queue *wait_queue)
{
    int count = 0;
    Link temp;

    temp = wait_queue->front;

    if(temp == NULL)
    {
        return 0;        //队列空
    }

    while(temp != NULL)
    {
        count++;             //计数
	temp = temp->next;  //遍历队列
    }
    
    return count;          //返回个数
}
