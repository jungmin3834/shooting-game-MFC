// LeftView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCApplication1Doc.h"
#include "MFCApplication1.h"
#include "MFCApplication1View.h"
#include "LeftView.h"
#include "MainFrm.h"

// LeftView
#define TIMER_RATE	1
#define TIMER_END	2

IMPLEMENT_DYNCREATE(LeftView, CFormView)

LeftView::LeftView()
	: CFormView(LeftView::IDD)
{

}

LeftView::~LeftView()
{
}

void LeftView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
	DDX_Control(pDX, IDC_EDIT1, m_nickname);
}

BEGIN_MESSAGE_MAP(LeftView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &LeftView::OnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &LeftView::OnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &LeftView::OnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &LeftView::OnClickedButton5)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
//	ON_BN_CLICKED(IDC_BUTTON_START, &LeftView::OnClickedButtonStart)
//	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &LeftView::OnClickedButtonPause)
END_MESSAGE_MAP()


// LeftView 진단입니다.

#ifdef _DEBUG
void LeftView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void LeftView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// LeftView 메시지 처리기입니다.

void LeftView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	//배경 깔기

	m_bmpBackSkin.LoadBitmap(IDB_BITMAP1);
	((CStatic*)GetDlgItem(IDC_STATIC_SKIN))->SetBitmap(m_bmpBackSkin);
	((CStatic*)GetDlgItem(IDC_STATIC_SKIN))->ModifyStyle(0, WS_CLIPSIBLINGS);


	m_ctrlList.InsertColumn(0, _T("이름"), LVCFMT_LEFT, 100); // 표의 맨윗부분 

	m_ctrlList.InsertColumn(1, _T("스코어"), LVCFMT_LEFT, 100);
	m_ctrlList.DeleteAllItems();
	m_ctrlList.InsertItem(0, TEXT("손정민"));
	m_ctrlList.SetItemText(0, 1,TEXT("1000"));


	CMFCApplication1Doc *pDoc;
	pDoc = (CMFCApplication1Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveView()
		->GetDocument();


	
	vector<wbData> temp;
	temp.clear();
	//pDoc->m_database->GetDataAll(&(pDoc->m_printdata));
	temp = (pDoc->m_printdata);

	if (temp.size() == 0)
		return;
	

	int flags=0;


	for (int i = 0; i < temp.size(); i++)
	{
		m_ctrlList.InsertItem(i, temp[i].str3);
		TCHAR buf[500];
		wsprintf(buf, TEXT("%d"), temp[i].score);
		m_ctrlList.SetItemText(i,1,buf);
	}
}

void LeftView::OnClickedButton1()
{
	// 접속
	CMFCApplication1Doc *pDoc;
	pDoc = (CMFCApplication1Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveView()
		->GetDocument();
	login = true;
	
	m_nickname.GetWindowText((pDoc->name));
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void LeftView::OnClickedButton2()
{
	// 시작
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!login){
		MessageBox(TEXT("접속을 해주십시오."), 0, 0);
		return;
	}
	gamestart = true;
	m_gameStartState = true;
	
}


void LeftView::OnClickedButton3()
{
	// 정지
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_gameStartState){
		m_gameStartState = false;
		gamestart = false;
	}
}


void LeftView::OnClickedButton5()
{
	// 나가기
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//LeftView::OnDestroy();

	AfxGetMainWnd()->PostMessageW(WM_CLOSE);
}


//void LeftView::OnClickedButtonStart()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}


//void LeftView::OnClickedButtonPause()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}


void LeftView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CMFCApplication1Doc *pDoc;
	pDoc = (CMFCApplication1Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveView()
		->GetDocument();

	m_ctrlList.DeleteAllItems();

	vector<wbData> temp;
	temp.clear();
	//pDoc->m_database->GetDataAll(&(pDoc->m_printdata));
	temp = pDoc->m_printdata;


	if (temp.size() == 0)
		return;

	for (int i = 0; i < temp.size(); i++)
	{
		m_ctrlList.InsertItem(i, temp[i].str3);
		TCHAR buf[500];
		wsprintf(buf, TEXT("%d"), temp[i].score);
		m_ctrlList.SetItemText(i, 1, buf);
	}
}
