#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sqlite3.h>

static int callback(void *not_used, int argc, char **argv, char **col_name)
{
    static print_head = 0;
    
    int i;
    
    #if 1
    if(0 == print_head)
    {
        for(i = 0; i < argc; i++)
	{
	    printf("%s\t",col_name[i]);
	}
	printf("\n");
	print_head = 1;
    }
    #endif

    for(i = 0; i < argc; i++)
    {
        printf("%s\t",argv[i]?argv[i]:"NULL");
        //printf("%s\t",argv[0]);
    }
    
    printf("\n");
    return 0;
}

int main(int argc, char *argv[])
{
    sqlite3 *db = NULL;
    char *err_msg = NULL;

    int rc = sqlite3_open("score_mgr.db",&db);
    
    if(rc != SQLITE_OK)
    {
        fprintf(stderr,"open falied %s\n",sqlite3_errmsg(db));
    }
    else
    {
        fprintf(stderr,"open database successful\n");
    }
    
    char *sql_select_student = (char *)malloc(100);
    memset(sql_select_student,0,100);

    sprintf(sql_select_student,"select name,age from %s;",argv[1]);

    rc = sqlite3_exec(db, sql_select_student, callback, 0, &err_msg);
    if(SQLITE_OK != rc)
    {
        fprintf(stderr,"sql err : %s\n", err_msg);
	sqlite3_free(err_msg);
    }
    else
    {
        fprintf(stderr, "table query successfully\n");
    }
    sqlite3_close(db);
    
    return 0;
}
