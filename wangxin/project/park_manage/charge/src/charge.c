/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:      charge
  Author:    Wanxin   Version: 1.0       Date: 2014.6.10
  Description:    该程序实现出车计费
  Others:         无
  Function List:  
                  charge
		  出车计费
  History:        no
*************************************************/

#include <stdio.h>
#include <time.h>
#include "../../include/typedef.h"

/*************************************************
  Function:       charge
  Description:    出车计费
  Calls:          no
  Called By:      out
  Input:          park_stack,i,car_num
  Output:         no
  Return:         no
  Others:         no
*************************************************/

void charge(Stack *park_stack, int i, long int car_num)
{
    struct tm *pre_time;
    time_t park_time;
		    
    park_time = park_stack->i_time[i];
    pre_time = localtime(&park_time);  //取停车时间
    
    printf("\n\t\033[40;36m取车成功！\033[0m\n\n");
    printf("\t\033[40;36m感谢你使用新智停车系统！\033[0m\n\n");		    
    printf("\t\033[40;36m你的车牌号为: \033[0m\033[40;31m%ld\033[0m\n",car_num);
    printf("\t\033[40;36m你停车时间为: \033[0m\033[40;31m%d:%d:%d\033[0m\n",pre_time->tm_hour,pre_time->tm_min,pre_time->tm_sec);
    
    struct tm *now_time;
    time_t leave_time;
		    
    time(&leave_time);
    now_time = localtime(&leave_time);  //取取车时间
    printf("\t\033[40;36m你取车的时间为: \033[0m\033[40;31m%d:%d:%d\033[0m\n",now_time->tm_hour,now_time->tm_min,now_time->tm_sec);
    
    int min;
    int sec;
    double stop_time;
		    
    stop_time = difftime(leave_time,park_time);
    min = stop_time / 60;
    sec = stop_time - min * 60;   //计算费用

    printf("\t\033[40;36m你一共停了\033[0m\033[40;31m%d分%d秒\033[0m\033[40;36m。\033[0m\n",min,sec);
    printf("\t\033[40;36m本停车场收费为\033[0m\033[40;31m36元/小时\033[0m\033[40;36m,你应付费用为\033[40;31m%.2lf元\033[0m\033[40;36m。\033[0m\n\n",36*stop_time/3600);

}
