/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:      is_malloc
  Author:    Wanxin   Version: 1.0       Date: 2014.6.10
  Description:    该程序实现判断是否成功分配内存
  Others:         无
  Function List:  
                  is_malloc
		  判断是否成功分配内存
  History:        no
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../../include/typedef.h"
#define MALLOC_ERROR 0

/*************************************************
  Function:       is_malloc
  Description:    判断是否成功分配内存
  Calls:          no
  Called By:      park
  Input:          temp
  Output:         no
  Return:         no
  Others:         no
*************************************************/

int is_malloc(Link temp)
{
    if(temp == NULL)
    {
        printf("malloc error!\n");
	exit(MALLOC_ERROR);
    }
}
