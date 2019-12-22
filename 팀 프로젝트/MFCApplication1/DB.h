#pragma once

#include <sql.h>
#include <sqlext.h>
#pragma comment(lib, "odbc32.lib")
// CDB

class CDB : public CWnd
{
	DECLARE_DYNAMIC(CDB)
	SQLHSTMT hStmt;
	SQLHENV hEnv;
	SQLHDBC hDbc;

public:
	CDB();
	virtual ~CDB();

protected:
	DECLARE_MESSAGE_MAP()


public:
	BOOL DBConnect();
	BOOL DBDConnect();
	BOOL InsertData(CString str1, int score);
	BOOL GetDataAll(vector<wbData>* pdata);

private:
	BOOL CommandSql(TCHAR *str);
};


