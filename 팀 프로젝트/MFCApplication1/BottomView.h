#pragma once
#include "afxwin.h"



// BottomView �� ���Դϴ�.

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
	BottomView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	bool toggle = FALSE;
	afx_msg void OnClickedButton1();
	afx_msg void OnTimer(UINT nIDEvent);
	CListBox m_chatListBox;
	CEdit m_ChatEditBox;
};


