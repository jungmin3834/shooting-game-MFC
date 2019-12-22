#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// LeftView �� ���Դϴ�.

class LeftView : public CFormView
{
	DECLARE_DYNCREATE(LeftView)
public:
	CBitmap m_background;
protected:
	CBitmap m_bmpBackSkin;
public:
	virtual void OnInitialUpdate();
protected:
	LeftView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~LeftView();

public:
	enum { IDD = IDD_LEFTVIEW };
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
	afx_msg void OnClickedButton1();
	afx_msg void OnClickedButton2();
	afx_msg void OnClickedButton3();
	afx_msg void OnClickedButton5();
//	afx_msg void OnClickedButtonStart();
//	afx_msg void OnClickedButtonPause();
	CListCtrl m_ctrlList;
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	CEdit m_nickname;
};


