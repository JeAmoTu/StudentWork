#include<stdio.h>
void convert(int num,int p1_bit,int p2_bit,int bin[])
{
    int i;
    int j = 0;
    int my_num = 0;
    int aim_num = 0;
    int sub = p2_bit - p1_bit + 1;

    for(i = 0; i < sub; i++)
    {
        my_num = ((my_num << 1 ) | 1);
    }
    
    num = (num >> (p1_bit - 1));

    aim_num = (my_num^num);
    
    for(i = sub - 1; i >= 0; i--)
    {
	bin[i] = (aim_num >> j) & 1;
        j++;
	printf("%d",bin[i]);
    }



}

int main()
{
    int p1_bit;
    int p2_bit;
    int bin[32] = {0};
    unsigned int num;

    printf("please input a number:");
    scanf("%d",&num);

    printf("please input the p1_bit and p2_bit:");
    scanf("%d,%d",&p1_bit,&p2_bit);

    convert(num,p1_bit,p2_bit,bin);
    
    return 0;
}
