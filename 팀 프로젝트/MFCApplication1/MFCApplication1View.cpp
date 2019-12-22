
// MFCApplication1View.cpp : CMFCApplication1View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"
#include "MFCApplication1.h"
#include "MainFrm.h"
#include "LeftView.h"

#define TIMER_RATE	1
#define	TIMER_END	2

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMFCApplication1View 생성/소멸

CMFCApplication1View::CMFCApplication1View()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_HandClosedCursor = AfxGetApp()->LoadCursor(IDC_CURSOR1);	// 커서 모양 설정

	m_hHandNormalCursor = AfxGetApp()->LoadCursor(IDC_CURSOR1);	// 커서 모양 설정
}

CMFCApplication1View::~CMFCApplication1View()
{
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCApplication1View 그리기
#define MAX 150
void CMFCApplication1View::OnDraw(CDC* pDC)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	char buf[50];
	sprintf(buf, "  남은시간: %d / %d점", lefttime, GetDocument()->g_count);
	SetWindowTextA(GetDocument()->text, buf);
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CenterImage(pDC);
	if (m_gameStartState == true){
		for (int i = 0; i < 15; i++)
		{
			Target data = GetDocument()->target[i];
			if (data.shot == false)
				continue;//pDC->Rectangle(data.tp.x, data.tp.y, data.tp.x + MAX, data.tp.y + 10);
			else
				//pDC->Rectangle(data.tp.x, data.tp.y, data.tp.x + MAX, data.tp.y + MAX);
			
			if (data.flag == 1)			//인질
				Image(pDC, &data);
			else if (data.flag == 2)	//악당
				Image(pDC, &data);
			else						//과녁
				Image(pDC, &data);		
		}
	}

		//for (int i = 0; i < 15; i++)
		//{
		//	Target data = GetDocument()->target[i];
		//	pDC->Rectangle(data.tp.x, data.tp.y, data.tp.x + MAX, data.tp.y + 10);
		//}
	
}


// CMFCApplication1ViewView 인쇄

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

// CMFCApplication1View 진단

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View 메시지 처리기

void CMFCApplication1View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nIDEvent){
		case TIMER_RATE:{
			for (int i = 0; i < 15; i++)
			{
				Target &data = GetDocument()->target[i];
				data.shot = false;
			}
			vector<Target>&temp = GetDocument()->target;




			srand(time(NULL));
			int change = (rand() % 10)+5;

			for (int i = 0; i <= change; i++)
			{
				int ran = (rand() % 15);
				temp[i].flag = (rand() % 10);
				temp[ran].shot = true;
			}
			Invalidate();
			break;
		}

		case TIMER_END:{	
			if (m_gameStartState == true){
				lefttime = lefttime - 1;
				if (lefttime == 0){
					/*KillTimer(TIMER_RATE);
					KillTimer(TIMER_END);*/
					lefttime = 30;
					gamestart = false;
					m_gameStartState = false;
					GetDocument()->m_printdata.clear();
					GetDocument()->m_database->InsertData(GetDocument()->name, GetDocument()->g_count);
					GetDocument()->g_count = 0;
					GetDocument()->UpdateAllViews(0);

				}
				char buf[50];
				sprintf(buf, "  남은시간: %d / %d점", lefttime, GetDocument()->g_count);
				SetWindowTextA(GetDocument()->text, buf);
			}
			break;
		}
		CView::OnTimer(nIDEvent);
	}
}

void CMFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (!gamestart)
		return;
	vector<Target>&temp = GetDocument()->target;
	CPoint pt = point;
	bool shot = false;

	for (int i = 0; i < temp.size(); i++)
	{

		if (pt.x >= temp[i].tp.x&&pt.x <= temp[i].tp.x + MAX){
			if (pt.y >= temp[i].tp.y&&pt.y <= temp[i].tp.y + MAX)
			{
				if (temp[i].shot == true)
				{
					if (temp[i].flag == 1)
						GetDocument()->g_count -= 3;
					else if (temp[i].flag == 2)
						GetDocument()->g_count += 3;
					else
						GetDocument()->g_count++;
					temp[i].shot = false;
					shot = true;
					Invalidate();
				}

			}
		}
	}
	if (!shot){
		GetDocument()->g_count--;
		Invalidate();
	}

	CView::OnLButtonDown(nFlags, point);
}


void CMFCApplication1View::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	HINSTANCE hInstance = AfxGetInstanceHandle();
	SetTimer(TIMER_RATE, 1500, 0);
	SetTimer(TIMER_END, 1000, 0);
	GetDocument()->text = CreateWindow(_T("static"), _T("아아아"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 0, 170, 30, m_hWnd, (HMENU)0, hInstance, NULL);

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CMFCApplication1View::CenterImage(CDC* pDC)
{
	CBitmap myBit, *pOldBit;

	CDC memDC;
	BITMAP bm;

	myBit.LoadBitmap(IDB_BITMAP4);
	myBit.GetObject(sizeof(BITMAP), &bm);
	memDC.CreateCompatibleDC(pDC);
	pOldBit = memDC.SelectObject(&myBit);

	CRect rc;
	GetClientRect(rc);
	int x = 0;
	int y = 0;

	pDC->BitBlt(x, y, bm.bmWidth, bm.bmHeight, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBit);

}


void CMFCApplication1View::Image(CDC* pDC, Target* data)
{
	CBitmap myBit, *pOldBit;

	CDC memDC;
	BITMAP bm;

	if (data->flag == 1){				//인질
		myBit.LoadBitmap(IDB_BITMAP7);
	}
	else if (data->flag == 2){			//악당
		myBit.LoadBitmap(IDB_BITMAP6);
	}
	else{								//과녁
		myBit.LoadBitmap(IDB_BITMAP5);
	}

	myBit.GetObject(sizeof(BITMAP), &bm);
	memDC.CreateCompatibleDC(pDC);
	pOldBit = memDC.SelectObject(&myBit);

	CRect rc;
	GetClientRect(rc);
	int x = data->tp.x;
	int y = data->tp.y;

	pDC->BitBlt(x, y, bm.bmWidth, bm.bmHeight, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBit);

}


BOOL CMFCApplication1View::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_hHandNormalCursor)
	{
		SetCursor(m_hHandNormalCursor);
		//::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));
		return TRUE;
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);

}

