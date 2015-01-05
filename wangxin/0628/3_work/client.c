#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define INFO_SIZE 24

enum
{
	INSERT, SHOW, RECORD_NUM, MAN_NUM, FEMALE_NUM, CHANGE, ORDER, DELETE, QUIT
};

typedef struct msg_tag
{
	int type;
}msg_t;

typedef struct student_info_tag
{
	char name[20];
	char blank_01;
	char blank_02;
	char age;
	char gender;
}student_info_t;

void interface()
{
	printf("/*******************************************\n");
	printf("insert\n");
	printf("show\n");
	printf("query_record_num\n");
	printf("query_man_num\n");
	printf("query_female_num\n");
	printf("change\n");
	printf("order\n");
	printf("delete\n");
	printf("quit\n");
	printf("please input your order:\n");
}

int insert(int sockfd)
{
	msg_t msg;
	student_info_t stu;

	memset(&stu, 0, sizeof(stu));
	stu.blank_01 = ' ';
	stu.blank_02 = ' ';
	msg.type = INSERT;
	int ret = write(sockfd, &msg, sizeof(msg_t));
	if(ret != sizeof(msg_t))
	{
		perror(strerror(errno));
		close(sockfd);
		return -1;
	}

	printf("Please input the information of new student(name age gender):\n");
	ret = scanf("%s %d %c", stu.name, &stu.age, &stu.gender);
	if(ret != 3)
	{
		setbuf(stdin, NULL);
		printf("input error");
		return -1;
	}

	ret = write(sockfd, &stu, INFO_SIZE);
	printf("ret = %d\n",ret);
	if(ret != INFO_SIZE)
	{
		perror(strerror(errno));
		close(sockfd);
		return -1;
	}
	return 0;
}

int show(int sockfd)
{
	msg_t msg;
	char name[20] = {0};
	student_info_t stu;

	msg.type = SHOW;
	int ret = write(sockfd, &msg, sizeof(msg_t));
	if(ret != sizeof(msg_t))
	{
		perror(strerror(errno));
		close(sockfd);
		return -1;
	}
	printf("please input a name for seek:\n");
	ret = scanf("%s", name);
	if(ret < 0)
	{
		perror(strerror(errno));
		setbuf(stdin, NULL);
		return -1;
	}

	ret = write(sockfd, name, sizeof(name));
	if(ret != sizeof(name))
	{
		perror(strerror(errno));
		close(sockfd);
		return -1;
	}

	ret = read(sockfd, &stu, sizeof(stu));
	if(ret != sizeof(stu))
	{
		perror(strerror(errno));
		close(sockfd);
		return -1;
	}

	printf("name:    %s\n", stu.name);
	printf("age:     %d\n", stu.age);
	printf("gender:  %c\n", stu.gender);

	return 0;
}

int query_record_num(int sockfd)
{
	msg_t msg = {0};
	int num_record = 0;

	msg.type = RECORD_NUM;
	int ret = write(sockfd, &msg, sizeof(msg));
	if(ret != sizeof(msg))
	{
		perror(strerror(errno));
		close(sockfd);
		return 0;
	}

	ret = read(sockfd, &num_record, sizeof(int));
	if(ret != sizeof(int))
	{
		perror(strerror(errno));
		close(sockfd);
		return 0;
	}

	return num_record;

}

int query_man_num(int sockfd)
{
	msg_t msg = {0};
	int num_man;

	msg.type = MAN_NUM;
	int ret = write(sockfd, &msg, sizeof(msg));
	if(ret != sizeof(msg))
	{
		perror(strerror(errno));
		close(sockfd);
		return 0;
	}

	ret = read(sockfd, &num_man, sizeof(int));
	if(ret != sizeof(int))
	{
		perror(strerror(errno));
		close(sockfd);
		return 0;
	}

	return num_man;
}

int query_female_num(int sockfd)
{
	msg_t msg = {0};
	int num_female = 0;

	msg.type = FEMALE_NUM;
	int ret = write(sockfd, &msg, sizeof(msg));
	if(ret != sizeof(msg))
	{
		perror(strerror(errno));
		close(sockfd);
		return 0;
	}

	ret = read(sockfd, &num_female, sizeof(int));
	if(ret != sizeof(int))
	{
		perror(strerror(errno));
		close(sockfd);
		return 0;
	}

	return num_female;
}

int change(int sockfd)
{
	msg_t msg = {0};
	student_info_t student = {0};

	msg.type = CHANGE;
	int ret = write(sockfd, &msg, sizeof(msg));
	if(ret != sizeof(msg))
	{
		perror(strerror(errno));
		close(sockfd);
		return -1;
	}

	memset(&student, 0, sizeof(student));
	printf("please input the new information(name age gender):\n");
	ret = scanf("%s %d %c", student.name, &student.age, &student.gender);
	if(ret != 3)
	{
		perror(strerror(errno));
		setbuf(stdin, NULL);
		return -1;
		
	}

	ret = write(sockfd, &student, INFO_SIZE);
	if(ret != INFO_SIZE)
	{
		perror(strerror(errno));
		close(sockfd);
		return -1;
	}
	
	return 0;
}

int order(int sockfd)
{
	msg_t msg;
	student_info_t student;
	int count;

	msg.type = ORDER;
	int ret = write(sockfd, &msg, sizeof(msg));
	if(ret != sizeof(msg))
	{
		perror(strerror(errno));
		close(sockfd);
		return 0;
	}

	memset(&student, 0, sizeof(student));

	ret = read(sockfd, &count, sizeof(int));
	if(ret != sizeof(int))
	{
		perror(strerror(errno));
		close(sockfd);
		return 0;
	}

	int i = 0;
	for(i = 0; i < count; i++)
	{
		ret = read(sockfd, &student, INFO_SIZE);
		if(ret != INFO_SIZE)
		{
			perror(strerror(errno));
			close(sockfd);
			return 0;
		}
		printf("\nname:     %s\n", student.name);
		printf("age:      %d\n", student.age);
		printf("gender:   %c\n", student.gender);
	}
}

int delete(int sockfd)
{
	msg_t msg = {0};
	char name[20] = {0};
	student_info_t student = {0};

	msg.type = DELETE;
	int ret = write(sockfd, &msg, sizeof(msg));
	if(ret != sizeof(msg))
	{
		perror(strerror(errno));
		close(sockfd);
		return 0;
	}

	printf("please input the people's name you want delete:\n");
	ret = scanf("%s", name);
	if(ret < 0)
	{
		perror(strerror(errno));
		return -1;
	}

	ret = write(sockfd, name, sizeof(name));
	if(ret != sizeof(name))
	{
		perror(strerror(errno));
		close(sockfd);
		return -1;
	}
	return 0;
}

int quit(int sockfd)
{
	msg_t msg;

	msg.type = QUIT;
	int ret = write(sockfd, &msg, sizeof(msg));
	if(ret != sizeof(msg))
	{
		perror(strerror(errno));
		close(sockfd);
		return -1;
	}

	close(sockfd);

	return 0;
}

int main(int argc, char **argv)
{
	char chose[40] = {0};
	char name[20] = {0};
	int num_record = 0;
	int num_man = 0;
	int num_female = 0;

	if(3 != argc)
	{
		printf("./client ip port\n");
		return 0;
	}
	
	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	server.sin_addr.s_addr = inet_addr(argv[1]);
	
	student_info_t student;
	int i;
	int count;

	while(1)
	{
		interface();

		scanf("%s", chose);

		int sockfd = socket(PF_INET, SOCK_STREAM, 0);
		if(sockfd < 0)
		{
			perror(strerror(errno));
			return 0;
		}

		int num = connect(sockfd, (struct sockaddr *)&server, sizeof(server));
		if(num < 0)
		{
			perror(strerror(errno));
			close(sockfd);
			return 0;
		}

		if(strcmp(chose, "insert") == 0)
		{
			insert(sockfd);
		        continue;
		}
		if(strcmp(chose, "show") == 0)
		{
			show(sockfd);
		        continue;
		}
		if(strcmp(chose, "query_record_num") == 0)
		{
			num_record = query_record_num(sockfd);
			printf("record num is %d\n", num_record);
		        continue;
		}
		if(strcmp(chose, "query_man_num") == 0)
		{
			num_man = query_man_num(sockfd);
			printf("man num is %d\n", num_man);
		        continue;
		}
		if(strcmp(chose, "query_female_num") == 0)
		{ 
			num_female = query_female_num(sockfd);
			printf("female num is %d\n", num_female);
		        continue;
		}
		if(strcmp(chose, "change") == 0)
		{
			change(sockfd);
		        continue;
		}
		if(strcmp(chose, "order") == 0)
		{
			order(sockfd);
		        continue;
		}
		if(strcmp(chose, "delete") == 0)
		{
			delete(sockfd);
		        continue;
		}
		if(strcmp(chose, "quit") == 0)
		{
			quit(sockfd);
			return 0;
		}
		else
		{
			printf("input error!\n");
		        continue;
		}

	}
}
