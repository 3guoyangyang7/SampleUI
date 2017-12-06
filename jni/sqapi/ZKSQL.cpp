/*
 * ZKSQL.cpp
 *
 *  Created on: 2017年12月5日
 *      Author: Kwolve
 */

#include <string>
#include "utils/Log.h"
#include "ZKSQL.h"

const char *sql_create_table="create table t(user varchar(128) ,id varchar(128))";
#ifndef NULL
#define NULL ((void*)0)
#endif

ZKSQL::ZKSQL(const char* dbname) {
	char *errmsg = 0;
	int ret;
	std::string path="/mnt/extsd/"+std::string(dbname)+".db";
	/*读写打开一个数据库文件，无此文件打开失败*/
	 ret = sqlite3_open_v2(path.c_str(),&mdb,SQLITE_OPEN_READWRITE,NULL);
	 if(ret != SQLITE_OK){
		/*无此文件，创建一个文件*/
		ret = sqlite3_open(path.c_str(),&mdb);
		if(ret != SQLITE_OK){
			 LOGD("Cannot open db: %s\n",sqlite3_errmsg(mdb));
		}
		/*创建一个表*/
		 ret = sqlite3_exec(mdb,sql_create_table,NULL,NULL,&errmsg);
		 if(ret != SQLITE_OK){
			 LOGD("create table fail: %s\n",errmsg);
		 }
	 }
	LOGD("Open database\n");
	sqlite3_free(errmsg);
}

ZKSQL::~ZKSQL() {
	// TODO Auto-generated destructor stub
	sqlite3_close(mdb);
	LOGD("Close database\n");
}
char **ZKSQL::rawQuery(char *sql,int *row,int *column,char **result)
{
    sqlite3_get_table(mdb,sql,&result,row,column,0);
    return result;
}
void ZKSQL::releaseRawQuery(char **query)
{
	sqlite3_free_table(query);
}

void ZKSQL::execSQL(char *sql)
{
    sqlite3_exec(mdb,sql,0,0,0);
}
