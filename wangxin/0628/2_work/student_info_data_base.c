#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

typedef struct student_info_tag
{
	char name[20];
	char blank_01;
	char age;
	char blank_02;
	char gender;
}student_info_t;

void interface()
{   
	setbuf(stdin,NULL);
	printf("/********************************/\n");
	printf("1.insert\n");
	printf("2.show\n");
	printf("3.query_record_num\n");
	printf("4.query_man_num\n");
	printf("5.query_female_num\n");
	printf("6.change\n");
	printf("7.order_by_name\n");
	printf("8.delete\n");
	printf("9.quit\n");
}

int insert()
{
	setbuf(stdin,NULL);

	char name[24] = {0};
	int age = 0;
	char gender = 'M';

	setbuf(stdin,NULL);

	int ret  = scanf("%s %d %c",name, &age, &gender);

	if(3 != ret)
	{
		setbuf(stdin,NULL);
		printf("\033[46;31minsert failed!\033[0m\n\n");
		choose();
	}

	setbuf(stdin,NULL);

	student_info_t stu = {0};
	stu.blank_01 = ' ';
	stu.blank_02 = ' ';
	memcpy(stu.name,name,20);
	stu.age = (char)age;
	stu.gender = gender;

	append_record(&stu);
	printf("\n\033[47;31minsert success!\033[0m\n\n");
	choose();
}

int append_record(student_info_t *stu)
{
	int fd = open("student_info.db",O_RDWR|O_CREAT|O_APPEND,0664);

	if(fd < 0)
	{
		perror(strerror(errno));
		close(fd);
	}

	int num = write(fd, stu, sizeof(student_info_t));

	if(num != sizeof(student_info_t))
	{
		perror(strerror(errno));
		close(fd);
	}

	close(fd);
}

int show()
{
	int i;
	char name[20];
	student_info_t stu;

	printf("please input the people's name you want show: ");
	scanf("%s",name);

	int fd = open("student_info.db",O_RDONLY|O_CREAT,0664);
	if(fd < 0)
	{
		perror(strerror(errno));
		close(fd);
		return 0;
	}

	int len = lseek(fd, 0, SEEK_END); 
	lseek(fd, 0, SEEK_SET);

	if(len == 0)
	{
		printf("not exist!\n\n");
		choose();
	}

	for(i = 0; i < len; i += 24)
	{
		int ret = read(fd, &stu, sizeof(student_info_t));

		if(strcmp(name,stu.name) == 0)
		{
			printf("\nname: %s,age: %d,gender: %c\n\n",stu.name,stu.age,stu.gender);
			choose();
		}	
	}
	printf("\nnot exists!\n\n");
	close(fd);
	choose();
}

void query_record_num()
{
	int fd = open("student_info.db",O_RDONLY);
	int count = lseek(fd,0,SEEK_END);
	printf("\nrecord num is %d\n\n",count/24);
	close(fd);
	choose();
}

void query_man_num()
{
	int i;
	int count = 0;
	int fd = open("student_info.db",O_RDONLY);
	int len = lseek(fd,0,SEEK_END);
	lseek(fd,0,SEEK_SET);

	student_info_t stu = {0};

	for(i = 0; i < len; i += 24)
	{
		int ret = read(fd,&stu,sizeof(stu));

		if(ret < 0)
		{
			perror(strerror(errno));
			close(fd);
		}

		if(stu.gender == 'M')
		{
			count++;
		}
	}
	printf("\nthe man num is %d\n\n",count);
	close(fd);
	choose();
}

void query_female_num()
{
	int i;
	int count = 0;
	int fd = open("student_info.db",O_RDONLY);
	int len = lseek(fd,0,SEEK_END);
	lseek(fd,0,SEEK_SET);

	student_info_t stu = {0};

	for(i = 0; i < len; i += 24)
	{
		int ret = read(fd,&stu,sizeof(stu));

		if(ret < 0)
		{
			perror(strerror(errno));
			close(fd);
		}

		if(stu.gender == 'F')
		{
			count++;
		}
	}
	printf("\nthe famale nun is %d\n\n",count);
	close(fd);
	choose();
}

void change()
{
	int i;
	char age;
	char gender; 
	int count;
	char name[24] = {0};

	printf("please input the people's name you want change: ");
	scanf("%s",name);

	int fd = open("student_info.db",O_RDWR);
	if(fd < 0)
	{
		perror(strerror(errno));
		close(fd);
	}

	student_info_t stu = {0};

	int len = lseek(fd,0,SEEK_END);

	lseek(fd,0,SEEK_SET);
	count = -sizeof(stu);

	for(i = 0;i < len;i + 24)
	{
		int ret = read(fd,&stu,sizeof(stu));

		if(ret != sizeof(stu))
		{
			perror(strerror(errno));
			exit(0);
		}

		count += ret;

		if(strcmp(stu.name,name) == 0)
		{
			printf("please input the people's new info:\n");
			printf("age: ");

			setbuf(stdin,NULL);
			scanf("%d",&age);

			printf("gender('M' or 'F'):");

			setbuf(stdin,NULL);
			scanf("%c",&gender);

			stu.age = age;
			stu.gender = gender;

			lseek(fd,count,SEEK_SET);

			int ret = write(fd,&stu,sizeof(stu));

			if(ret != sizeof(stu))
			{
				perror(strerror(errno));
				exit(0);
			}

			close(fd);
			choose();
		}

	}
	printf("\nno this people!\n");
	close(fd);
	choose(); 
}

void order_by_name()
{
	int i;
	int j;
	int num;
	int fd = open("student_info.db",O_RDWR);
	if(fd < 0)
	{
		perror(strerror(errno));
		exit(0);
	}

	num  = lseek(fd,0,SEEK_END);
	lseek(fd,0,SEEK_SET);

	num = num / sizeof(student_info_t);
	student_info_t stu[num];
	student_info_t temp;

	for(i = 0; i < num; i++)
	{
		int ret = read(fd,&stu[i],sizeof(student_info_t));
		if(ret != sizeof(student_info_t))
		{
			perror(strerror(errno));
			exit(0);
		}
	}

	for(i = 0; i < num; i++)
	{
		for(j = 1; j < num - i; j++)
		{
			if(strcmp(stu[j].name,stu[j - 1].name) < 0)
			{
				temp = stu[j];
				stu[j] = stu[j - 1];
				stu[j - 1] = temp;
			}
		}
	}

	for(i = 0; i < num; i++)
	{
		printf("\n%s %d %c\n\n",stu[i].name,stu[i].age,stu[i].gender);
	}

	close(fd);
	choose();
}

void delete()
{
	int i;
	int count;
	int length;
	int ret;
	int sign = 0;
	char name[20];
	student_info_t temp;

	printf("please input th people's name you want delete:\n");
	ret = scanf("%s", name);
	if(ret < 0)
	{
		setbuf(stdin, NULL);
		perror(strerror(errno));
		exit(0);
	}

	int fd = open("student_info.db",O_RDWR);
	if(fd < 0)
	{
		perror(strerror(errno));
		exit(0);
	}
	length = lseek(fd, 0, SEEK_END);

	if(length < 0)
	{
		perror(strerror(errno));
		exit(-1);
	}
	count = length/sizeof(student_info_t);
	student_info_t student[count];

	ret = lseek(fd, 0, SEEK_SET);
	if(ret < 0)
	{
		perror(strerror(errno));
		exit(-1);
	}

	for(i = 0; i < count; i++)
	{
		memset(&student[i], 0, sizeof(student_info_t));

		ret = read(fd, &student[i], sizeof(student_info_t));
		if(ret < 0)
		{
			perror(strerror(errno));
			exit(-1);
		}
	}

	close(fd);
	fd = open("student_info.db", O_RDWR|O_TRUNC);
	if(fd < 0)
	{
		perror(strerror(errno));
		exit(-1);
	}

	for(i = 0; i < count; i++)
	{
		if(0 == strcmp(student[i].name, name))
		{
			sign = 1;
		}
		else
		{
			ret = write(fd, &student[i], sizeof(student_info_t));
			if(ret < 0)
			{
				perror(strerror(errno));
				exit(-1);
			}
		}
	}

	if(0 == sign)
	{
		printf("can't find the student named %s\n", name);
		exit(-1);
	}
	else
	{
		printf("delete success\n");
		exit(-1);
	}
}

choose()
{
	interface();
	char rec[30] = {0};
	memset(rec,0,30);
	printf("please input you choice: ");
	setbuf(stdin,NULL);
	scanf("%s",rec);
	if(strcmp(rec,"insert") == 0)
	{
		insert();
	}
	if(strcmp(rec,"show") == 0)
	{
		show();
	}
	if(strcmp(rec,"query_record_num") == 0)
	{
		query_record_num();
	}
	if(strcmp(rec,"query_man_num") == 0)
	{
		query_man_num();
	}
	if(strcmp(rec,"query_female_num") == 0)
	{
		query_female_num();
	}
	if(strcmp(rec,"change") == 0)
	{
		change();
	}
	if(strcmp(rec,"order_by_name") == 0)
	{
		order_by_name();
	}
	if(strcmp(rec,"delete") == 0)
	{
		delete();
	}
	if(strcmp(rec,"quit") == 0)
	{
		exit(0);
	}
}


int main(int argc, char **argv)
{
	choose();
}
