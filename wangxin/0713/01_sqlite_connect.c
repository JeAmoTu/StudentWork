#include<stdio.h>
#include<sqlite3.h>

int main()
{
    sqlite3 *db = NULL;
    char *err_msg = NULL;

    int rc = sqlite3_open("score_mgr.db",&db);
    printf("rc = %d\n",rc);
    if(rc != SQLITE_OK)
    {
        fprintf(stderr,"open failed\n",sqlite3_errmsg(db));
    }
    else
    {
        fprintf(stderr,"open database successful\n");
    }
    
    sqlite3_close(db);
    return 0;
}
