/*
 * ZKSQL.h
 *
 *  Created on: 2017年12月5日
 *      Author: Kwolve
 */

#ifndef ZKSQL_H_
#define ZKSQL_H_

#include "platform/sqlite3.h"

class ZKSQL {
public:
	ZKSQL(const char* dbname);
	virtual ~ZKSQL();
	void execSQL(char* sql);
	char **rawQuery(char *sql,int *row,int *column,char **result);
	void releaseRawQuery(char **query);
private :
	sqlite3 *mdb;
};

#endif /* ZKSQL_H_ */
