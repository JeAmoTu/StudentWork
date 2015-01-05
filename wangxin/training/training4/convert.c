/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:     convert
  Author:        wangxin    Version:  1.0      Date: 2014.05.01
  Description:   该程序实现将一个整数转换成任意进制
  Others:        no
  Function List: 
                 convert(int num,int to_num,char *array)
		 进制转换
  History:       no
*************************************************/

#include<stdio.h>
#define FUNCTION_ERROR 0

/*************************************************
  Function:    convert 
  Description: 进制转换
  Calls:       no
  Called By:   main
  Input:      
              num   原数
              to_num  要转换的进制
	      array  保存数组
  Output:     no
  Return:     no
  Others:     no
*************************************************/

char * convert(int num,int to_num,char *array)
{
    int j;
    int i = 0;
    char temp;
    char *p;
    char aim_array[64] = "";

    while(num != 0)
    {
        array[i] = num % to_num;             //求余保存数组中
	
	if(array[i] >= 10)
	{
	    array[i] = array[i] - 10 + 'A';  //大于十的用符号输出
	}
	
	else
	{
	    array[i] += 48;                  
	}
	
	num /= to_num;                       
	i++;
    }
    
    i--;
    j = 0;
    p = aim_array;

    while(i >= 0)
    {
        if(j < sizeof(array))
	{
	    aim_array[j] = array[i];
	    j++;
	}
	i--;
    }
    
    return p;
}

/*************************************************
  Function:    main
  Description: 实现基本输入输出
  Calls:       convert
  Called By:   no
  Input:       no
  Output:      no
  Return:      0
  Others:      no
*************************************************/

int main()
{
    int i;
    int num;
    int to_num;
    char *p;
    char array[64] = "";
    
    printf("please input a num and a num you want to change:\n");
    scanf("%d %d",&num,&to_num);

    printf("the number after changed is : ");
    
    if((p = convert(num,to_num,array)) == NULL)
    {
        printf("function opporated error!\n");
	exit(FUNCTION_ERROR);
    }
    
    
    printf("%s",p);
    printf("\n");
    
    return 0;
}
