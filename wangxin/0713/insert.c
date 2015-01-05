#include<stdio.h>
#include<sqlite3.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{
    if(argc != 5)
    {
        printf("use ./insert id name gender age\n");
        return 0;
    }

    sqlite3 *db = NULL;
    char *err_msg = NULL;

    int rc = sqlite3_open("score_mgr.db",&db);
    
    if(rc != SQLITE_OK)
    {
        fprintf(stderr,"open falied %s\n",sqlite3_errmsg(db));
        return 0;
    }
    else
    {
        fprintf(stderr,"open database successful\n");
    }
    
    char *sql_create_student = "create table student(\
        id INTEGER,\
	name TEXT,\
	gender TEXT,\
	age INTEGER,\
        primary key(id)\
	);";
    
    rc = sqlite3_exec(db, sql_create_student, NULL, 0, &err_msg);
    if(SQLITE_OK != rc)
    {
        fprintf(stderr, "sql error %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    else
    {
        fprintf(stderr, "table create successfully\n");
    }
    
    char *sql_insert_student = (char *)malloc(100);
    
    sprintf(sql_insert_student,"insert into student(id,name,gender,age)values(%d,'%s','%s',%d);",atoi(argv[1]),argv[2],argv[3],atoi(argv[4]));
    
    printf("sql_insert = %s\n",sql_insert_student);
    rc = sqlite3_exec(db, sql_insert_student, NULL, 0, &err_msg);
    if(SQLITE_OK != rc)
    {
        fprintf(stderr,"sql err : %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    else
    {
        fprintf(stderr, "table insert successfully\n");
    }
    
    free(sql_insert_student);
    sqlite3_close(db);
    
    return 0;
}
