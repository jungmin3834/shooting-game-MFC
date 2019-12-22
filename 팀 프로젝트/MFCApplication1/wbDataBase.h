#pragma once

#include <sql.h>
#include <sqlext.h>
#pragma comment(lib, "odbc32.lib")

class wbDataBase
{
	SQLHSTMT hStmt;
	SQLHENV hEnv;
	SQLHDBC hDbc;
public:
	wbDataBase();
	~wbDataBase();

public:
	BOOL DBConnect();
	BOOL DBDConnect();
	BOOL InsertData(int score, CString str2, CString str3);
	BOOL GetDataAll(vector<wbData>*pdata);
private:
	BOOL CommandSql(TCHAR *str);
};

