#include<stdio.h>

int func(int num)
{
    printf("%d\n",num);
}

int func1(int num)
{
    printf("%d\n",num + 1);
}

int func2(int num)
{
    printf("%d\n",num + 2);
}

int func3(int num)
{
    printf("%d\n",num + 3);
}


int main()
{
    int i = 0;
    int num = 0;

    int (*p_func)(int num);

    int (* pa_func[4])(int num);

    pa_func[0] = func;
    pa_func[1] = func1;
    pa_func[2] = func2;
    pa_func[3] = func3;
    p_func = func;

    p_func(5);

    for(i = 0; i < 4; i++)
    {
        pa_func[i](num);
    }
    
    
    return 0;


}
