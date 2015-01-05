/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:      is_empty_queue
  Author:    Wanxin   Version: 1.0       Date: 2014.6.10
  Description:    该程序实现判断队列是否为空
  Others:         无
  Function List:  
                  is_empty_queue
		  判断队列是否为空
  History:        no
*************************************************/

#include "../../include/typedef.h"

/*************************************************
  Function:       is_empty_queue
  Description:    判断队列是否为空
  Calls:          no
  Called By:      out
  Input:          my_link_queue
  Output:         no
  Return:         0,-1
  Others:         no
*************************************************/

int is_empty_queue(Link_queue *my_link_queue)
{
    if((my_link_queue->rear == NULL) &&                                            (my_link_queue->front == NULL))        // 头尾都为空
    {                                                     
        return EMPTY_OK;                              //队列空
    }
    else
    {
        return EMPTY_NO;                                  //队列非空
    }
}
