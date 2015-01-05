#include <stdio.h>
#include <sqlite3.h>

int main(int argc, char *argv[])
{
	sqlite3 *db=NULL;
	char *err_msg = NULL;

	int rc = sqlite3_open("score_mgr_01.db", &db);
	if(rc!=SQLITE_OK){
		fprintf(stderr, "open failed %s\n", sqlite3_errmsg(db));	
	}else{
		fprintf(stdout, "opended database successful\n");
	}

	char *sql_create_student = "create table student(\
		id	INTEGER,\
		name	TEXT,\
		gender	TEXT,\
		age	INTEGER,\
		primary key(id)\
		);";

	rc = sqlite3_exec(db, sql_create_student, NULL, 0, &err_msg);
	if(SQLITE_OK!=rc){
		fprintf(stderr, "sql error: %s\n", err_msg);
		sqlite3_free(err_msg);
	}else{
		fprintf(stdout, "table create succfully\n");
	}

	sqlite3_close(db);
	return 0;
}
