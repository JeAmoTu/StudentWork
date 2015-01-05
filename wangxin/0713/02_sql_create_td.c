#include<stdio.h>
#include<sqlite3.h>

int main(int argc, char *argv[])
{
    sqlite3 *db = NULL;
    char *err_msg = NULL;

    int rc = sqlite3_open("score_mgr_01.db",&db);
    
    if(rc != SQLITE_OK)
    {
        fprintf(stderr,"open falied %s\n",sqlite3_errmsg(db));
    }
    else
    {
        fprintf(stderr,"open database successful\n");
    }
    
    #if 0
    char *sql_create_student = "create table student(\
        id INTEGER,\
	name TEXT,\
	gender TEXT,\
	age INTEGER,\
        primary key(id)\
	);";
    
    rc = sqlite3_exec(db, sql_create_student, NULL, 0, &err_msg);
    printf("rc = %d\n",rc);
    if(SQLITE_OK != rc)
    {
        fprintf(stderr, "sql error %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    else
    {
        fprintf(stderr, "table create successfully\n");
    }
    #endif
    char *sql_insert_student = "insert into student(\
        id,name,gender,age)\
	values(3,\"rose\",\"female\",20);";
    rc = sqlite3_exec(db, sql_insert_student, NULL, 0, &err_msg);
    printf("rc = %d\n",rc);
    if(SQLITE_OK != rc)
    {
        fprintf(stderr,"sql err : %s\n", err_msg);
	sqlite3_free(err_msg);
    }
    else
    {
        fprintf(stderr, "table insert successfully\n");
    }
    
    sqlite3_close(db);
    
    return 0;
}
