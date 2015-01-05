#include<stdio.h>
#include<string.h>

int main(int argc, char **argv)
{
    char name[24] = {0};
    int age = 0;
    char gender = 'M';

    while(1)
    {
        memset(name, 0, sizeof(name));
	age = 0;
	gender = 'M';

	int ret  = scanf("%s %d %c",name, &age, &gender);
	printf("ret: %d name: %s age: %d gender: %c\n",ret,name,age,gender);
	
	if(3 == ret)
	{
	    //do something
	}
	else
	{
	    setbuf(stdin,NULL);
            continue;
	}
    }
    
    return 0;
}
