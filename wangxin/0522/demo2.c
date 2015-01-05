#include<stdio.h>

void make(int num,int aim_num[])
{
    int i;
    int j = 0;

    for(i = 31;i >= 0; i--)
    {
	aim_num[i] = (num >> j) & 1;
	j++;
    }
}

void print(int p_bit,int v,int aim_num[])
{
    int i;

    for(i = 0; i < 32; i++)
    {
        if(i == (32-p_bit))
	{
	    aim_num[i] = v;
	}

	printf("%d",aim_num[i]);
    }
}

int main()
{
   int num;
   int p_bit;
   int v;
   int aim_num[32];

   printf("please input a num:");
   scanf("%d",&num);

   printf("please input the bit and the num you want repalce:");
   scanf("%d %d",&p_bit,&v);

   make(num,aim_num);
   print(p_bit,v,aim_num);

}
