#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

#define QUEUE_LEN  10

enum{CMD_PUT = 1,CMD_GET,CMD_DEL};

typedef struct msg_tag
{
	int type;
	int len;
}msg_t;

typedef struct file_info_tag
{
	char opt;
	char name[256];
	int len;
}file_info_t;

int block_write(int fd, char*buf, int len)
{
    int write_size = 0;
    int n = 0;

    while(write_size < len)
    {
        n = write(fd,buf+write_size,len-write_size);
	if(n < 0)
	{
	    perror(strerror(errno));
	    break;
	}
	else if(0 == n)
	{
	    perror(strerror(errno));
	    break;
	}
	write_size += n;
    }

    return 0;
}

int block_read(int fd, char*buf, int len)
{
	int read_size = 0;
	int n = 0;

	while(read_size < len)
	{
		n = read(fd, buf + read_size,len-read_size);
		if(n < 0)
		{
			perror(strerror(errno));
			break;
		}
		else if(0 == n)
		{
			perror(strerror(errno));
			break;
		}
		read_size += n;
	}
	return 0;
}

void *thread_handle(void *arg)
{
	int connectfd = *((int *)arg); 
	free(arg);

	msg_t msg = {0};

	int num = read(connectfd, &msg, sizeof(msg));
	
	if(num != sizeof(msg))
	{
		perror(strerror(errno));
		close(connectfd);
		return 0;
	}

	char *buf = NULL;

	switch(msg.type)
	{
		case CMD_PUT:
			{
				buf = (char*)malloc(msg.len + 1);
				memset(buf, 0, msg.len + 1);
				num = read(connectfd, buf, msg.len);
				if(num != msg.len)
				{
					perror(strerror(errno));
					close(connectfd);
					return 0;
				}


				int ack = 1;
				int ret = write(connectfd,&ack,sizeof(ack));
				
				if(ret != sizeof(ack))
				{
					perror(strerror(errno));
					return 0;
				}

				free(buf);

				file_info_t file_info;
				num = read(connectfd, &file_info, sizeof(file_info));

				char *data = NULL;
				data = (char *)malloc(file_info.len + 1);
				memset(data,0,file_info.len + 1);
				int fd = open(file_info.name,O_RDWR|O_CREAT|O_APPEND,0664);

				if(fd < 0)
				{
					perror(strerror(errno));
					close(fd);
					return 0;
				}
				block_read(connectfd,data,file_info.len);
				block_write(fd,data,file_info.len);
                                
				close(fd);
				close(connectfd);
				break;
			}
		case CMD_GET:
			{	
				buf = (char*)malloc(msg.len + 1);
				memset(buf, 0, msg.len + 1);
				num = read(connectfd, buf, msg.len);
				if(num != msg.len)
				{
					perror(strerror(errno));
					close(connectfd);
					return 0;
				}


				int ack = 2;
				int ret = write(connectfd,&ack,sizeof(ack));

				if(ret != sizeof(ack))
				{
					perror(strerror(errno));
					return 0;
				}
				
				file_info_t file_info = {.opt = 1};
				int fd = open(buf,O_RDONLY);
                                int len = lseek(fd,0,SEEK_END) ;

				lseek(fd,0,SEEK_SET);
				file_info.len = len;

				strcpy(file_info.name,buf);

				ret = write(connectfd,&file_info,sizeof(file_info));

				char *data = NULL;

				data = (char *)malloc(len + 1);
				memset(data,0,len + 1);

				num = read(fd,data,len);
				printf("num = %d\n",num);
				block_write(connectfd,data,len);
				
				free(buf);
				close(fd);
				close(connectfd);
				break;
			}
		case CMD_DEL:
			{	
				buf = (char*)malloc(msg.len + 7);
				memset(buf, 0, msg.len + 7);
				
				char *name = (char*)malloc(msg.len + 1);
				memset(name, 0, msg.len + 1);

				strcpy(buf,"rm -f ");
				num = read(connectfd, buf + 6, msg.len);
				strcpy(name,buf + 6);
				
				if(num != msg.len)
				{
					perror(strerror(errno));
					close(connectfd);
					return 0;
				}


				int ack = 3;
				int ret = write(connectfd,&ack,sizeof(ack));

				if(ret != sizeof(ack))
				{
					perror(strerror(errno));
					return 0;
				}
			        
				int fd = open(name,O_RDWR);
				if(fd < 0)
				{
				    perror(strerror(errno));
				    close(connectfd);
				    return 0;
				}
				system(buf);
				printf("delete success!\n");
				free(buf);
				close(connectfd);
			        break;
			}

		default:
			{
				printf("unknow order\n");
				close(connectfd);
				break;
			}
	}
}

int main(int argc, char **argv)
{
	int count = 0;

	if(argc != 3)
	{
		printf("use ./server ip port!\n");
		return 0;
	}

	int listenfd = socket(PF_INET, SOCK_STREAM, 0);

	if(listenfd < 0)
	{
		perror(strerror(errno));
		close(listenfd);
		return 0;
	}

	int opt = SO_REUSEADDR;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	server.sin_addr.s_addr = inet_addr(argv[1]);

	int ret = bind(listenfd, (struct sockaddr*)&server, sizeof(server));

	if(ret < 0)
	{
		perror(strerror(errno));
		close(listenfd);
		return 0;
	}

	listen(listenfd, 10);

	struct sockaddr_in client;
	socklen_t addrlen = sizeof(client);

	while(1)
	{
		int connectfd = accept(listenfd, (struct sockaddr*)&client, &addrlen);

		printf("accepting!\n");
		int *temp_connfd = (int *)malloc(sizeof(connectfd));
		*temp_connfd = connectfd;


		if(connectfd < 0)
		{
			perror(strerror(errno));
			close(listenfd);
			close(connectfd);
			return 0;
		}

		pthread_t pid;

		pthread_create(&pid,NULL,thread_handle,(void *)temp_connfd);
		printf("thread num %d\n\n",count);
		count++;

		pthread_detach(pid);
	}

	close(listenfd);
	return 0;
}

