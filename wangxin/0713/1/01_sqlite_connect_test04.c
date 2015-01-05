#include <stdio.h>
#include <sqlite3.h>

int main(int argc, char *argv[])
{
	sqlite3 *db=NULL;
	char *err_msg = NULL;

	int rc = sqlite3_open("score_mgr.db", &db);
	if(rc!=SQLITE_OK){
		fprintf(stderr, "open failed %s\n", sqlite3_errmsg(db));	
	}else{
		fprintf(stderr, "opended database successful\n");
	}
        
	sqlite3_close(db);
	return 0;
}
