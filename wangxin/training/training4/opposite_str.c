/*************************************************
  Copyright (C), 1994-2014    wangxin
  File name:     opposite
  Author:        wangxin    Version:  1.0        Date:   2014.05.01
  Description:   将一个字符串逆序 
  Others:        no
  Function List:  
                 opposite_str(char *dest)
		 将一个字符串逆序
  History:       no
*************************************************/

#include<stdio.h>
#include<string.h>
# define MAX 1024
#define INPUT_ERROR 0
#define FUNCTION_ERROR -1

/*************************************************
  Function:       opposite_str
  Description:    将一个字符串逆序
  Calls:          no
  Called By:      main
  Input:          dest   传入一个字符串
  Output:         no
  Return:         0
  Others:         no
*************************************************/

char * opposite_str(char *dest)
{
    if(dest == NULL)
    {
        printf("input error!\n");
	exit(INPUT_ERROR);
    }

    int i;
    int j;
    char *p;
    char aim[100] = "";
    int d_len = strlen(dest);
    
    j = 0;
    p = aim;
    dest = dest + d_len - 1;     //指针跳到字符串最后一位
    
    for(i = 0; i < d_len; i++)   //change string
    {
        aim[j] = *dest;
	dest--;
	j++;
    }
    
    return p;
}

/*************************************************
  Function:       main
  Description:    实现基本输入输出
  Calls:          opposite_str
  Called By:      no
  Input:          no
  Output:         no
  Return:         0
  Others:         no
*************************************************/

int main()
{
    char *p;
    char src[1024];
    
    printf("please input a string:\n");
    scanf("%s",src);
    
    printf("the opposite string is:\n");
    
    if((p = opposite_str(src)) == NULL)                  //函数调用
    {
        printf("function opporate error!\n");
	exit(FUNCTION_ERROR);
    }
    
    printf("%s\n",p);
    
    return 0;
}
