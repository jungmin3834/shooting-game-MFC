// BottomView.cpp : ���� �����Դϴ�.
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


// BottomView �����Դϴ�.

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


// BottomView �޽��� ó�����Դϴ�.


void BottomView::OnClickedButton1()
{//ü��
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.


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
	
		//��� ���
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
				  // ��ȭ���ڿ� ������ Picture ��Ʈ���� �ּҸ� ��´�. ( Picture ��Ʈ�ѵ� CStatic ��Ʈ���̴�. )
				  CStatic *p_lamp_image = (CStatic *)GetDlgItem(IDC_STATIC_SKIN);

				  // ���ҽ��� �ִ� ��Ʈ�� �̹����� �б� ���ؼ� CBitmap Ŭ���� ��ü�� �����Ѵ�.
				  CBitmap lamp_image;
				  // ���ҽ����� IDB_BITMAP2 �̹����� �д´�.
				  lamp_image.LoadBitmap(IDB_BITMAP3);

				  // Picture ��Ʈ�ѿ� ���� �о���� �̹����� �����ϰ� ������ ����ϴ� �̹��� �ڵ���
				  // p_old_ bitmap ������ �����Ѵ�.
				  HBITMAP h_old_bitmap = p_lamp_image->SetBitmap(lamp_image);

				  // Picture ��Ʈ���� ������ ����ϴ� �̹����� �־��ٸ� �����Ѵ�.
				  if (h_old_bitmap != NULL) ::DeleteObject(h_old_bitmap);

				  // Picture ��Ʈ�ѿ� �̹����� �����ϱ� ���ؼ� �����ߴ� �̹����� Picture ��Ʈ���� ����ϱ�
				  // ������ lamp_image ��ü�� ����Ǹ鼭 �������� �ʵ��� ������ �����Ѵ�.
				  // �� �ڵ带 ������� �ʾƵ� �Ǵ� ��ó�� �������� �ش� Picture ��Ʈ���� �������ٰ�
				  // �ٽ� ���̰� �Ǵ� ��� �׸��� �׷����� �ʴ´�. ���� �� ����ؾ� �մϴ�.
				  lamp_image.Detach();
 
			  }
			  else if (toggle == FALSE)
			  {
				  // ��ȭ���ڿ� ������ Picture ��Ʈ���� �ּҸ� ��´�. ( Picture ��Ʈ�ѵ� CStatic ��Ʈ���̴�. )
				  CStatic *p_lamp_image = (CStatic *)GetDlgItem(IDC_STATIC_SKIN);

				  // ���ҽ��� �ִ� ��Ʈ�� �̹����� �б� ���ؼ� CBitmap Ŭ���� ��ü�� �����Ѵ�.
				  CBitmap lamp_image;
				  // ���ҽ����� IDB_BITMAP2 �̹����� �д´�.
				  lamp_image.LoadBitmap(IDB_BITMAP2);

				  // Picture ��Ʈ�ѿ� ���� �о���� �̹����� �����ϰ� ������ ����ϴ� �̹��� �ڵ���
				  // p_old_ bitmap ������ �����Ѵ�.
				  HBITMAP h_old_bitmap = p_lamp_image->SetBitmap(lamp_image);

				  // Picture ��Ʈ���� ������ ����ϴ� �̹����� �־��ٸ� �����Ѵ�.
				  if (h_old_bitmap != NULL) ::DeleteObject(h_old_bitmap);

				  // Picture ��Ʈ�ѿ� �̹����� �����ϱ� ���ؼ� �����ߴ� �̹����� Picture ��Ʈ���� ����ϱ�
				  // ������ lamp_image ��ü�� ����Ǹ鼭 �������� �ʵ��� ������ �����Ѵ�.
				  // �� �ڵ带 ������� �ʾƵ� �Ǵ� ��ó�� �������� �ش� Picture ��Ʈ���� �������ٰ�
				  // �ٽ� ���̰� �Ǵ� ��� �׸��� �׷����� �ʴ´�. ���� �� ����ؾ� �մϴ�.
				  lamp_image.Detach();
				
			  }
			  Invalidate();
	}break;
	}
}