#pragma once
#include "afxwin.h"



// BottomView 폼 뷰입니다.

class BottomView : public CFormView
{
	DECLARE_DYNCREATE(BottomView)
public:
	CBitmap m_background;
protected:
	CBitmap m_bmpBackSkin;
public:
	virtual void OnInitialUpdate();
protected:
	BottomView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~BottomView();

public:
	enum { IDD = IDD_BOTTOMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	bool toggle = FALSE;
	afx_msg void OnClickedButton1();
	afx_msg void OnTimer(UINT nIDEvent);
	CListBox m_chatListBox;
	CEdit m_ChatEditBox;
};


