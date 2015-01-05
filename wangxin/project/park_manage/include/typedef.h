#include <time.h>

typedef struct stack
{
    long int p_num[10];
    time_t i_time[10];
    int top;
}Stack;

typedef struct link
{
    long int num;
    struct link *next;
}*Link;

typedef struct link_queue
{
    Link rear;
    Link front;
}Link_queue;

enum
{
    FULL_OK,
    FULL_NO,
    EMPTY_OK,
    EMPTY_NO
};
