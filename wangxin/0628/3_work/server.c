#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define PORT 1234
#define QUEUE_LEN 10
#define INFO_SIZE 24

enum
{
	INSERT, SHOW, RECORD_NUM, MAN_NUM, FEMALE_NUM, CHANGE, ORDER, DELETE, QUIT
};

typedef struct msg_tag
{
	int type;
	int len;
}msg_t;

typedef struct student_info_tag
{
	char name[20];
	char blank_01;
	char blank_02;
	char age;
	char gender;
}student_info_t;

int show(int fd, int connectfd, char *name)
{
	int i;
	int count;
	int length;
	int ret;
	student_info_t student;

	length = lseek(fd, 0, SEEK_END);
	if(length < 0)
	{
		perror(strerror(errno));
		return -1;
	}
	count = length/INFO_SIZE;
	
	ret = lseek(fd, 0, SEEK_SET);
	if(ret < 0)
	{
		perror(strerror(errno));
		return -1;
	}

	for(i = 0; i < count; i++)
	{
		memset(&student, 0, INFO_SIZE);
		if(ret < 0)
		{
			perror(strerror(errno));
			return -1;
		}

		ret = read(fd, &student, INFO_SIZE);
		if(ret < 0)
		{
			perror(strerror(errno));
			return -1;
		}


		if(0 == strcmp(student.name, name))
		{
			ret = write(connectfd, &student, INFO_SIZE);
			if(ret != INFO_SIZE)
			{
				perror(strerror(errno));
				return 0;
			}
			return 0;
		}
	}
}

int query_record_num(int fd)
{
	int length;
	int count;

	length = lseek(fd, 0, SEEK_END);
	if(length < 0)
	{
		perror(strerror(errno));
		return -1;
	}
	count = length/INFO_SIZE;

	return count;
}


int query_man_num(int fd)
{
	int i;
	int count;
	int length;
	int ret;
	int man_num = 0;
	student_info_t student;

	length = lseek(fd, 0, SEEK_END);
	if(length < 0)
	{
		perror(strerror(errno));
		return -1;
	}
	count = length/INFO_SIZE;
	
	ret = lseek(fd, 0, SEEK_SET);
	if(ret < 0)
	{
		perror(strerror(errno));
		return -1;
	}

	for(i = 0; i < count; i++)
	{
		memset(&student, 0, INFO_SIZE);

		ret = read(fd, &student, INFO_SIZE);
		if(ret < 0)
		{
			perror(strerror(errno));
			return -1;
		}

		if('M' == student.gender)
		{
			man_num++;
		}
	}

	return man_num;
}

int query_female_num(int fd)
{
	int female_num = query_record_num(fd) - query_man_num(fd);

	return female_num;
}

int change(int fd, student_info_t * student)
{
	int i;
	int count;
	int ret;
	student_info_t student_temp;

	count = query_record_num(fd);

	printf("%d\n", __LINE__);
	ret = lseek(fd, 0, SEEK_SET);
	if(ret < 0)
	{
		perror(strerror(errno));
		return -1;
	}
	printf("%d\n", __LINE__);
	for(i = 0; i < count; i++)
	{
		memset(&student_temp, 0, INFO_SIZE);

		ret = read(fd, &student_temp, INFO_SIZE);
		if(ret < 0)
		{
			perror(strerror(errno));
			return -1;
		}

		if(0 == strcmp(student_temp.name, student->name))
		{
	printf("%d\n", __LINE__);
			ret = lseek(fd, -INFO_SIZE, SEEK_CUR);
			if(ret < 0)
			{
				perror(strerror(errno));
				return -1;
			}

			ret = write(fd, student, INFO_SIZE);
			if(ret != INFO_SIZE)
			{
				perror(strerror(errno));
				return -1;
			}

			return 0;
		}
	}
	return -1;
}

int delete(int fd, char * name)
{
	int i;
	int count;
	int length;
	int ret;
	int sign = 0;
	student_info_t temp_stu;

	length = lseek(fd, 0, SEEK_END);
	if(length < 0)
	{
		perror(strerror(errno));
		return -1;
	}
	count = length/INFO_SIZE;
	student_info_t student[count];
	
	ret = lseek(fd, 0, SEEK_SET);
	if(ret < 0)
	{
		perror(strerror(errno));
		return -1;
	}

	for(i = 0; i < count; i++)
	{
		memset(&student[i], 0, INFO_SIZE);

		ret = read(fd, &student[i], INFO_SIZE);
		if(ret < 0)
		{
			perror(strerror(errno));
			return -1;
		}
	}

	close(fd);
	fd = open("student_info.db", O_RDWR|O_TRUNC);
	if(fd < 0)
	{
		perror(strerror(errno));
		return 0;
	}

	for(i = 0; i < count; i++)
	{
		if(0 == strcmp(student[i].name, name))
		{
			sign = 1;
		}
		else
		{
			ret = write(fd, &student[i], INFO_SIZE);
			if(ret < 0)
			{
				perror(strerror(errno));
				return -1;
			}
		}
	}
}

int order(int fd, int connectfd)
{
	int i;
	int j;
	int count;
	int length;
	int ret;
	student_info_t temp_stu;

	count = query_record_num(fd);
	student_info_t student[count];
	
	ret = lseek(fd, 0, SEEK_SET);
	if(ret < 0)
	{
		perror(strerror(errno));
		return -1;
	}

	for(i = 0; i < count; i++)
	{
		memset(&student[i], 0, INFO_SIZE);

		ret = read(fd, &student[i], INFO_SIZE);
		if(ret < 0)
		{
			perror(strerror(errno));
			return -1;
		}
	}

	for(i = 0; i < count; i++)
	{
		for(j = 1; j < count - i; j++)
		{
			if(strcmp(student[j].name, student[j-1].name) < 0)
			{
				temp_stu = student[j];
				student[j] = student[j-1];
				student[j-1] = temp_stu;
			}
		}
	}

	ret = write(connectfd, &count, sizeof(int));
	if(ret < 0)
	{
		perror(strerror(errno));
		return -1;
	}

	for(i = 0; i < count; i++)
	{
		ret = write(connectfd, &student[i], INFO_SIZE);
		if(ret < 0)
		{
			perror(strerror(errno));
			return -1;
		}
	}

	return 0;
}

int main(int argc, char ** argv)
{
	int count;
	int num_man;
	int num_female;

	if(3 != argc)
	{
		printf("input error!\n");
		return 0;
	}

	//1.create socket
	int listenfd = socket(PF_INET, SOCK_STREAM, 0);
	if(listenfd < 0)
	{
		perror(strerror(errno));
		return 0;
	}

	//set addr reuse
	int opt = SO_REUSEADDR;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	//2.bind
	struct sockaddr_in server = {0};
	memset(&server, 0, sizeof(server));
	server.sin_family         = AF_INET;
	server.sin_port           = htons(atoi(argv[2]));
	server.sin_addr.s_addr    = inet_addr(argv[1]);
	int n = bind(listenfd, (struct sockaddr *)&server, sizeof(server));
	if(n < 0)
	{
		perror(strerror(errno));
		close(listenfd);
		return 0;
	}

	//3.listen
	listen(listenfd, QUEUE_LEN);

	//4.accept
	struct sockaddr_in client = {0};
	socklen_t addrlen = sizeof(client);
	int connectfd;

	msg_t msg;
	student_info_t student;
	char name[20];

	while(1)
	{
		memset(&client, 0, sizeof(client));

		connectfd = accept(listenfd,(struct sockaddr *)&client, &addrlen);
		if(connectfd < 0)
		{
			perror(strerror(errno));
			close(listenfd);
			return 0;
		}

		//5.recv msg
		memset(&msg, 0, sizeof(msg));

		n = read(connectfd, &msg, sizeof(msg));

		int fd = open("student_info.db", O_RDWR|O_CREAT, 0664);
		if(fd < 0)
		{
			perror(strerror(errno));
			return 0;
		}

		switch(msg.type)
		{
			
			case INSERT:
			{
				memset(&student, 0, INFO_SIZE);

				n = read(connectfd, &student, INFO_SIZE);
				if(n != INFO_SIZE)
				{
					perror(strerror(errno));
					close(listenfd);
					close(connectfd);
					return 0;
				}

				lseek(fd, 0, SEEK_END);
				n = write(fd, &student, INFO_SIZE);
				if(n != INFO_SIZE)
				{
					perror(strerror(errno));
					close(listenfd);
					close(connectfd);
					return 0;
				}

				break;
			}
			case SHOW:
			{
				memset(name, 0, sizeof(name));
				n = read(connectfd, name, sizeof(name));
				if(n != sizeof(name))
				{
					perror(strerror(errno));
					close(listenfd);
					close(connectfd);
					return 0;
				}

				show(fd, connectfd, name);

				break;
			}
			case RECORD_NUM:
			{
				count = query_record_num(fd);
				n = write(connectfd, &count, sizeof(int));
				if(n != sizeof(int))
				{
					perror(strerror(errno));
					return 0;
				}
				
				break;
			}
			case MAN_NUM:
			{
				num_man = query_man_num(fd);

				n = write(connectfd, &num_man, sizeof(int));
				if(n != sizeof(int))
				{
					perror(strerror(errno));
					return 0;
				}

				break;
			}
			case FEMALE_NUM:
			{
				num_female = query_female_num(fd);
				n = write(connectfd, &num_female, sizeof(int));
				if(n != sizeof(int))
				{
					perror(strerror(errno));
					return 0;
				}
				break;
			}
			case CHANGE:
			{
				memset(&student, 0, INFO_SIZE);

				n = read(connectfd, &student, INFO_SIZE);
				if(n != INFO_SIZE)
				{
					perror(strerror(errno));
					close(listenfd);
					close(connectfd);
					return 0;
				}
				
				change(fd, &student);
				break;
			}
			case ORDER:
			{
				order(fd, connectfd);
				break;
			}
			case DELETE:
			{
				memset(name, 0, sizeof(name));
				n = read(connectfd, name, sizeof(name));
				if(n != sizeof(name))
				{
					perror(strerror(errno));
					close(listenfd);
					close(connectfd);
					return 0;
				}

				delete(fd, name);

				break;
			}
			case QUIT:
			{
				close(listenfd);
				close(connectfd);
				return 0;
			}
			default:
			{
				//close(connectfd);
				printf("can't distingush msgsage type\n");
				break;
			}
		}
	}


	return 0;
}
