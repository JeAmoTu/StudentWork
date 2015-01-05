#include <stdio.h>

struct pepole
{
    char name[20];
    int age;
    int gender;
};

int main()
{
    int i = 0;
    int j;
    struct pepole pep[3];

    while(i < 3)
    {
        setbuf(stdin,NULL);
	printf("please input the people's 'name' 'age' 'gender':\n");
        printf("name: ");
	j = scanf("%s",pep[i].name);
	
	while(j == 0)
	{
            setbuf(stdin,NULL);
	    printf("input error!please input again!\n");
	    printf("name: ");
	    j = scanf("%s",pep[i].name);
	}
	
        setbuf(stdin,NULL);
	printf("age: ");
	j = scanf("%d",&(pep[i].age));
	
	while(j == 0)
	{
	    setbuf(stdin,NULL);
	    printf("input error!please input again!\n");
	    printf("age: ");
	    j = scanf("%d",&pep[i].age);
	}
	
        setbuf(stdin,NULL);
	printf("gender(man:1 woman: 0): ");
	scanf("%d",&(pep[i].gender));
	
	while(j == 0)
	{
            setbuf(stdin,NULL);
	    printf("input error!please input again!\n");
	    printf("gender(man:1 woman: 0): ");
	    j = scanf("%d",&pep[i].age);
        }
	
	printf("\ninput info:    name: %s   age:%d\n\n",pep[i].name,pep[i].age);
	
	i++;
    }

    printf("agerave age is %d\n",(pep[0].age + pep[1].age + pep[2].age) / 3);
    return 0;
}
