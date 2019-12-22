// DB.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DB.h"


#define DBNAME TEXT("Sample")
#define ID	   TEXT("jun")
#define PW		TEXT("jun")
// CDB

IMPLEMENT_DYNAMIC(CDB, CWnd)

CDB::CDB()
{
	if (DBConnect() != TRUE)
		AfxMessageBox(TEXT("DB�������"));
}

CDB::~CDB()
{
	DBDConnect();
}

BOOL CDB::DBConnect()
{

	// ���� ������ ���� ������
	SQLRETURN Ret;

	// 1, ȯ�� �ڵ��� �Ҵ��ϰ� ���� �Ӽ��� �����Ѵ�.(p1741)
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS)
		return false;
	if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS)
		return false;

	// 2. ���� �ڵ��� �Ҵ��ϰ� �����Ѵ�.
	if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS)
		return false;
	// ����Ŭ ������ �����ϱ�
	Ret = SQLConnect(hDbc, (SQLTCHAR *)DBNAME, SQL_NTS, (SQLTCHAR *)ID, SQL_NTS, (SQLTCHAR *)PW, SQL_NTS);

	if ((Ret != SQL_SUCCESS) && (Ret != SQL_SUCCESS_WITH_INFO))
		return false;

	// ��� �ڵ��� �Ҵ��Ѵ�.
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS)
		return false;

	return true;
}


BOOL CDB::DBDConnect()
{
	// ������
	if (hStmt) ::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	if (hDbc) ::SQLDisconnect(hDbc);
	if (hDbc) ::SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	if (hEnv) ::SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

	return TRUE;
}


BOOL CDB::InsertData(CString str1, int score)
{
	TCHAR str[1024];
	wsprintf(str, TEXT("INSERT INTO GameScore(name,score) \
					   					   		VALUES('%s',%d);"),
												str1, score);

	if (CommandSql(str) == TRUE)
	{
		return CommandSql(TEXT("commit"));
	}
	return FALSE;
}

BOOL CDB::CommandSql(TCHAR *str)
{
	if (SQLExecDirect(hStmt, (SQLTCHAR *)str, SQL_NTS) != SQL_SUCCESS)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CDB::GetDataAll(vector<wbData>* pdata)
{
	try
	{
		int score;
		SQLTCHAR  str3[50];
		SQLINTEGER lstr2, lstr3;


		SQLBindCol(hStmt, 2, SQL_C_ULONG, &score, 0, &lstr2);
		SQLBindCol(hStmt, 1, SQL_C_TCHAR, str3, sizeof(str3), &lstr3);

		TCHAR sql[256] = TEXT("select * from GameScore order by score desc");

		if (SQLExecDirect(hStmt, (SQLTCHAR*)sql, SQL_NTS) != SQL_SUCCESS)
		{
			return FALSE;
		}

		for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
		{

			CString cstr = (CString)str3;
			wbData data(score, cstr);
			pdata->push_back(data);
		}
	}
	catch(exception ex)
	{
		return TRUE;
	}
	return TRUE;
}


BEGIN_MESSAGE_MAP(CDB, CWnd)
END_MESSAGE_MAP()



// CDB �޽��� ó�����Դϴ�.


