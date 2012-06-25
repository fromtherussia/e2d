#include <stdio.h>
#include <stdexcept>
#include <exception>
#include <string.h>

#include <postgresql/libpq-fe.h>
#include "pg_access.h"

int main(int argc, char** argv) {
	//printf("Hello BOGS!\n");
	try {
		PgConnection connection("host=localhost port=5432 dbname=object_database_test user= password=");
		PgResult result = connection.Select("SELECT id, uid, name FROM nodes;");
		//printf("Rows count: %d, Cols count: %d", result.NumRows(), result.NumCols());
		//result.Next();
		//result.Next();
		//result.Next();
		//result.Next();
		//printf("Value: %s", result.GetString(3).c_str());
	} catch (PgError& e) {
		printf("pg error: %s", e.what());
	} catch(...) {
		printf("unknown exception");
	}
	
	return 0;
}
