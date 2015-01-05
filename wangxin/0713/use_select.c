#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sqlite3.h>

static int callback(void *not_used, int argc, char **argv, char **col_name)
{
    for(i = 0; i < argc; i++)
    {
        printf("%s\t",argv[1]);
    }
    
    printf("\n");
    return 0;
}

int main()
{
    sqlite3 *db = NULL;
    char *err_msg = NULL;

    int rc = sqlite3_open("user.db",&db);
    
    if(rc != SQLITE_OK)
    {
        fprintf(stderr,"open falied %s\n",sqlite3_errmsg(db));
    }
    
    char *sql_select_student = (char *)malloc(100);
    memset(sql_select_student,0,100);

    strcpy(sql_select_student,"select count * from name");

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
