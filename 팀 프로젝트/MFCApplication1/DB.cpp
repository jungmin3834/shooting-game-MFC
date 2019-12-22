// DB.cpp : 구현 파일입니다.
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
		AfxMessageBox(TEXT("DB연결오류"));
}

CDB::~CDB()
{
	DBDConnect();
}

BOOL CDB::DBConnect()
{

	// 연결 설정을 위한 변수들
	SQLRETURN Ret;

	// 1, 환경 핸들을 할당하고 버전 속성을 설정한다.(p1741)
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS)
		return false;
	if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS)
		return false;

	// 2. 연결 핸들을 할당하고 연결한다.
	if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS)
		return false;
	// 오라클 서버에 연결하기
	Ret = SQLConnect(hDbc, (SQLTCHAR *)DBNAME, SQL_NTS, (SQLTCHAR *)ID, SQL_NTS, (SQLTCHAR *)PW, SQL_NTS);

	if ((Ret != SQL_SUCCESS) && (Ret != SQL_SUCCESS_WITH_INFO))
		return false;

	// 명령 핸들을 할당한다.
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS)
		return false;

	return true;
}


BOOL CDB::DBDConnect()
{
	// 뒷정리
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



// CDB 메시지 처리기입니다.


