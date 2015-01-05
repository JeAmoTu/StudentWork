/*************************************************
  Copyright (C)   1994-2014, Wangxin
  File name:      prime
  Author:         Wangxin     Version: 1.0       Date: 2014.05.01
  Description:    该函数实现找出1－100中的素数个数 
  Others:         无
  Function List:  
                  find_prime()  该函数实现找出1－100内的素数
  History:        no
*************************************************/


#include<stdio.h>
#include<math.h>  

/*************************************************
  Function:       find_prime
  Description:    该函数实现找出1－100内的素数
  Calls:          no
  Called By:      main
  Input:          no 
  Output:         no
  Return:         no
  Others:         no
*************************************************/

void find_prime() 
{
    int i;
    int k;
    int m;
    float j;
    
    for(i = 2; i <= 100; i++) 
    {
        j = sqrt(i);             /* 开平方 */
	for(k = 2; k < j; k++)  
	{
            m = i % k;           /* 求余 */
	    if(m == 0)          
            {
                break;
            }

	}
	
	if(k>j)                  /* 无余数为素数 */
        {
	    printf("\033[40;33m%d \033[0m",i);
        }
    }
    
    printf("\n");

}

/*************************************************
  Function:       main
  Description:    实现基本输入输出
  Calls:          find_prime
  Called By:      no
  Input:          no
  Output:         no
  Return:         0
  Others:         no
*************************************************/
int main()
{
	printf("\033[40;33mthe sushu of 1-100 have:\033[0m\n");
	find_prime();            /* 调用函数 */
	
	return 0;

}
