#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
#include<time.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sqlite3.h>

#define PORT 9666
#define QUEUE_LEN 10
#define MAX_LINE 80

enum{
    ERROR = -1,
    LOG = 1,
    LOG_SUCSF,
    LOG_NOEXIST,
    LOG_ONLINE,
    LOG_FAILED,
    REG,
    REG_ERROR,
    REG_SUCSF,
    SHOW,
    SAY,
    SAY_FAILED,
    SAY_TOSUCSF,
    SAY_SUCSF,
    SALL,
    STOALL,
    EXP,
    REPLACE,
    OFF,
    OUT,
    OUTO,
    OUT_FAILED,
    BAN,
    BANTO,
    BAN_FAILED,
    RMBAN,
    RMBANTO,
    RMFAILED,
    CHG_PSD,
    CHG_PSD_FAILED,
    CHG_NAM,
    CHG_NAM_FAILED,
    EXIT
};

typedef struct msg_tag
{
    int action;
    int id;
    char name[100];
    char toname[100];
    char passwd[100];
    char message[1000];
}msg_t;

