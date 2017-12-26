#include "stdafx.h"
#include "TCalcFuncSets.h"
#include "sqlite3\sqlite3.h"

#if 0

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

int sqlite3_main(void){
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  rc = sqlite3_open("test.db", &db);
  if( rc ){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return(1);
  }
  rc = sqlite3_exec(db, "CREATE TABLE students(number varchar(10), name varchar(10), sex varchar(6), age varchar(2));", callback, 0, &zErrMsg);
  if( rc!=SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  sqlite3_close(db);
  return 0;
}

void MagicNum_API_9(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc)
{

	sqlite3_main();
}

#endif


bool bNeedPrintHeader = true;
static void print_row(int nCols, char** columnValues)
{
    for (int i=0; i<nCols; i++)
    {
        printf("%10s", columnValues[i]);
    }
    printf("\n");
}

static int print_result(void* data, int nCols, char** columnValues, char** columnNames)
{
    if (bNeedPrintHeader)
    {
        print_row(nCols, columnNames);
        bNeedPrintHeader = false;
    }

    print_row(nCols, columnValues);
    return 0;
}

void MagicNum_API_9(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc)
{

    sqlite3 *db = NULL;
    char *errMsg = NULL;

    int rCode = sqlite3_open("test.db", &db);

    if (rCode)
    {
        fprintf(stderr, "Can't open database:%s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    else
    {
        printf("open test.db successfully!\n");		
    }


    rCode = sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    rCode = sqlite3_exec(db, "CREATE TABLE students(number varchar(10), name varchar(10), sex varchar(6), age varchar(2));", NULL, NULL, NULL);
    rCode = sqlite3_exec(db, "INSERT INTO students VALUES('00001', 'Mary', 'female', '15');\
                                INSERT INTO students VALUES('00002', 'John', 'male', '16');\
                                INSERT INTO students VALUES('00003', 'Mike', 'male', '15');\
                                INSERT INTO students VALUES('00004', 'Kevin', 'male', '17');\
                                INSERT INTO students VALUES('00005', 'Alice', 'female', '14');\
                                INSERT INTO students VALUES('00006', 'Susan', 'female', '16');\
                                INSERT INTO students VALUES('00007', 'Christina', 'female', '15');\
                                INSERT INTO students VALUES('00008', 'Brian', 'male', '16');\
                                INSERT INTO students VALUES('00009', 'Dennis', 'male', '14');\
                                INSERT INTO students VALUES('00010', 'Daphne', 'female', '18');", NULL, NULL, &errMsg);

    bNeedPrintHeader = true;
    rCode = sqlite3_exec(db, "SELECT students.* FROM students WHERE sex='female';", print_result, NULL, &errMsg);
    printf("\n");

    bNeedPrintHeader = true;
    rCode = sqlite3_exec(db, "SELECT students.* FROM students WHERE sex='male';", print_result, NULL, &errMsg);
    rCode = sqlite3_exec(db, "COMMIT TRANSACTION;", NULL, NULL, NULL);

    printf("error code: %d\n", rCode);
    printf("error message: %s\n", errMsg);
    sqlite3_close(db);
}



