#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>


typedef struct file_info_tag
{
    char opt;
    char name[256];
    int len;
}file_info_t;

enum{CMD_PUT = 1,CMD_GET,CMD_DEL};

typedef struct msg_tag
{
    int type;
    int len;
}msg_t;

int block_write(int fd, char* buf, int len)
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

int block_read(int fd, char* buf, int len)
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

int main(int argc, char **argv)
{
    int ack;

    if(argc != 3)
    {
        printf("use ./a.out ip port");
        return 0;
    }
    
    while(1)
    {
	    int sockfd = socket(PF_INET,SOCK_STREAM,0);
	    if(sockfd < 0)
	    {
		    perror(strerror(errno));
		    close(sockfd);
		    return 0;
	    }

	    struct sockaddr_in server;
	    memset(&server,0,sizeof(server));
	    server.sin_family = AF_INET;
	    server.sin_port = htons(atoi(argv[2]));
	    server.sin_addr.s_addr = inet_addr(argv[1]);

	    int ret = connect(sockfd,(struct sockaddr *)&server,sizeof(server));
	    if(ret < 0)
	    {
		    perror(strerror(errno));
		    close(sockfd);
		    return 0;
	    }

	    msg_t msg = {0};
	    char buf[20];
	    char cmd[20];

	    memset(buf,0,strlen(buf));
	    memset(cmd,0,strlen(cmd));
	    setbuf(stdin,NULL);
	    scanf("%s %s",cmd,buf);

	    if(strcmp(cmd,"put") == 0)
	    {
		    msg.type = CMD_PUT;
		    msg.len = strlen(buf);

		    int num = write(sockfd,&msg,sizeof(msg));

		    if(num != sizeof(msg))
		    {
			    perror(strerror(errno));
			    close(sockfd);
			    return 0;
		    }

		    num = write(sockfd,buf,strlen(buf));

		    if(num != strlen(buf))
		    {
			    perror(strerror(errno));
			    close(sockfd);
			    return 0;
		    }

		    file_info_t file_info = {.opt = 1};
		    strcpy(file_info.name,buf);

		    int fd = open(file_info.name,O_RDONLY);
		    int len = lseek(fd,0,SEEK_END);

		    lseek(fd,0,SEEK_SET);
		    file_info.len = len;
		    num = write(sockfd,&file_info,sizeof(file_info));

		    if(num != sizeof(file_info))
		    {
			    perror(strerror(errno));
			    close(sockfd);
			    return 0;
		    }

		    read(sockfd,&ack,sizeof(ack));
		    printf("ACK = %d\n",ack);
		    char *data = NULL;

		    data = (char *)malloc(file_info.len + 1);
		    memset(data,0,file_info.len + 1);

		    num = read(fd,data,file_info.len);
		    block_write(sockfd,data,file_info.len);
		    
		    close(sockfd);
	    }
	    else if(strcmp(cmd,"get") == 0)
	    {
		    msg.type = CMD_GET;
		    msg.len = strlen(buf);

		    int num = write(sockfd,&msg,sizeof(msg));

		    if(num != sizeof(msg))
		    {
			    perror(strerror(errno));
			    close(sockfd);
			    return 0;
		    }

		    num = write(sockfd,buf,strlen(buf));

		    if(num != strlen(buf))
		    {
			    perror(strerror(errno));
			    close(sockfd);
			    return 0;
	                    
		    }
		    
		    num = read(sockfd,&ack,sizeof(ack));
		    
		    if(num != sizeof(ack))
		    {
		        perror(strerror(errno));
			close(sockfd);
			return 0;
		    }
		    
		    printf("ACK = %d",ack);
			
		    file_info_t file_info = {0};
		    
		    num = read(sockfd,&file_info,sizeof(file_info));
		    
		    if(num != sizeof(file_info))
		    {
		        perror(strerror(errno));
			close(sockfd);
			return 0;
		    }
		    
		    int fd = open(file_info.name,O_RDWR|O_CREAT,0666);

		    char *data = NULL;
		    
		    data = (char *)malloc(file_info.len + 1);
		    memset(data,0,file_info.len + 1);
                    
		    num = read(sockfd,data,file_info.len);
                    
		    block_write(fd,data,file_info.len);
		    close(fd);
		    close(sockfd);

	    }
	    else if(strcmp(cmd,"del") == 0)
	    {
		    msg.type = CMD_DEL;
		    msg.len = strlen(buf);

		    int num = write(sockfd,&msg,sizeof(msg));

		    if(num != sizeof(msg))
		    {
			    perror(strerror(errno));
			    close(sockfd);
			    return 0;
		    }

		    num = write(sockfd,buf,strlen(buf));

		    if(num != strlen(buf))
		    {
			    perror(strerror(errno));
			    close(sockfd);
			    return 0;
	                    
		    }
		    
		    num = read(sockfd,&ack,sizeof(ack));
		    
		    if(num != sizeof(ack))
		    {
		        perror(strerror(errno));
			close(sockfd);
			return 0;
		    }
		    
		    printf("ACK = %d",ack);
	    }
	    else
	    {
	            printf("input error,please input again!\n");
   }

    } 
    return 0;
}
