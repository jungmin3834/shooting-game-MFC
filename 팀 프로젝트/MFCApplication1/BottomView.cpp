// BottomView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCApplication1.h"

#include "MFCApplication1Doc.h"
#include "BottomView.h"
#include "MainFrm.h"
#include "LeftView.h"
// BottomView

IMPLEMENT_DYNCREATE(BottomView, CFormView)

BottomView::BottomView()
	: CFormView(BottomView::IDD)
{

}

BottomView::~BottomView()
{
}

void BottomView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_chatListBox);
	DDX_Control(pDX, IDC_EDIT1, m_ChatEditBox);
}

BEGIN_MESSAGE_MAP(BottomView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &BottomView::OnClickedButton1)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// BottomView 진단입니다.

#ifdef _DEBUG
void BottomView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void BottomView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// BottomView 메시지 처리기입니다.


void BottomView::OnClickedButton1()
{//체팅
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	CString strTemp;


	CMFCApplication1Doc *pDoc;
	pDoc = (CMFCApplication1Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveView()->GetDocument();
	CString buf;
	buf = pDoc->name;
	m_ChatEditBox.GetWindowText(strTemp);


	TCHAR str[200] = { 0 };
	wcscat(str, buf);
	wcscat(str, TEXT(" : "));
	wcscat(str, strTemp);
	

	m_chatListBox.AddString(str);
	//m_chatListBox.AddString(TEXT("\r\n"));


}

void BottomView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	
		//배경 깔기
		m_bmpBackSkin.LoadBitmap(IDB_BITMAP2);
		((CStatic*)GetDlgItem(IDC_STATIC_SKIN))->SetBitmap(m_bmpBackSkin);
		((CStatic*)GetDlgItem(IDC_STATIC_SKIN))->ModifyStyle(0, WS_CLIPSIBLINGS);

	SetTimer(1, 1000, NULL);
	//SetTimer(2, 3000, NULL);
}



void BottomView::OnTimer(UINT nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
	{

			  toggle = !toggle;
			  if (toggle == TRUE)
			  {
				  // 대화상자에 생성된 Picture 컨트롤의 주소를 얻는다. ( Picture 컨트롤도 CStatic 컨트롤이다. )
				  CStatic *p_lamp_image = (CStatic *)GetDlgItem(IDC_STATIC_SKIN);

				  // 리소스에 있는 비트맵 이미지를 읽기 위해서 CBitmap 클래스 객체를 선언한다.
				  CBitmap lamp_image;
				  // 리소스에서 IDB_BITMAP2 이미지를 읽는다.
				  lamp_image.LoadBitmap(IDB_BITMAP3);

				  // Picture 컨트롤에 새로 읽어들인 이미지를 설정하고 이전에 사용하던 이미지 핸들을
				  // p_old_ bitmap 변수에 저장한다.
				  HBITMAP h_old_bitmap = p_lamp_image->SetBitmap(lamp_image);

				  // Picture 컨트롤이 이전에 사용하던 이미지가 있었다면 제거한다.
				  if (h_old_bitmap != NULL) ::DeleteObject(h_old_bitmap);

				  // Picture 컨트롤에 이미지를 설정하기 위해서 생성했던 이미지는 Picture 컨트롤이 사용하기
				  // 때문에 lamp_image 객체가 종료되면서 삭제되지 않도록 연결을 해제한다.
				  // 이 코드를 사용하지 않아도 되는 것처럼 보이지만 해당 Picture 컨트롤이 가려졌다가
				  // 다시 보이게 되는 경우 그림이 그려지지 않는다. 따라서 꼭 사용해야 합니다.
				  lamp_image.Detach();
 
			  }
			  else if (toggle == FALSE)
			  {
				  // 대화상자에 생성된 Picture 컨트롤의 주소를 얻는다. ( Picture 컨트롤도 CStatic 컨트롤이다. )
				  CStatic *p_lamp_image = (CStatic *)GetDlgItem(IDC_STATIC_SKIN);

				  // 리소스에 있는 비트맵 이미지를 읽기 위해서 CBitmap 클래스 객체를 선언한다.
				  CBitmap lamp_image;
				  // 리소스에서 IDB_BITMAP2 이미지를 읽는다.
				  lamp_image.LoadBitmap(IDB_BITMAP2);

				  // Picture 컨트롤에 새로 읽어들인 이미지를 설정하고 이전에 사용하던 이미지 핸들을
				  // p_old_ bitmap 변수에 저장한다.
				  HBITMAP h_old_bitmap = p_lamp_image->SetBitmap(lamp_image);

				  // Picture 컨트롤이 이전에 사용하던 이미지가 있었다면 제거한다.
				  if (h_old_bitmap != NULL) ::DeleteObject(h_old_bitmap);

				  // Picture 컨트롤에 이미지를 설정하기 위해서 생성했던 이미지는 Picture 컨트롤이 사용하기
				  // 때문에 lamp_image 객체가 종료되면서 삭제되지 않도록 연결을 해제한다.
				  // 이 코드를 사용하지 않아도 되는 것처럼 보이지만 해당 Picture 컨트롤이 가려졌다가
				  // 다시 보이게 되는 경우 그림이 그려지지 않는다. 따라서 꼭 사용해야 합니다.
				  lamp_image.Detach();
				
			  }
			  Invalidate();
	}break;
	}
}