
// polygonClippingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "polygonClipping.h"
#include "polygonClippingDlg.h"
#include "afxdialogex.h"

#include "afxtempl.h"//CArray
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CpolygonClippingDlg �Ի���



CpolygonClippingDlg::CpolygonClippingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CpolygonClippingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CpolygonClippingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CpolygonClippingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CpolygonClippingDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CpolygonClippingDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CpolygonClippingDlg::OnBnClickedButton3)
	ON_WM_LBUTTONDOWN()
//	ON_WM_NCRBUTTONDOWN()
ON_WM_RBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_RBUTTONUP()
ON_BN_CLICKED(IDC_BUTTON4, &CpolygonClippingDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CpolygonClippingDlg ��Ϣ�������

BOOL CpolygonClippingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CpolygonClippingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CpolygonClippingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}

	else
	{		
		CWnd *pWin = GetDlgItem(IDC_STATIC);//��ȡ�ÿؼ���ָ��
		CDC *pDc = pWin->GetDC();//��ȡ�ÿؼ��Ļ���		
		if (flag1){ drawPolygonA(pDc); }
		if (flag2){ drawCuttingFrame(pDc); }
		if (flag3){ drawPolygonA(pDc); }
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CpolygonClippingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//�����
void CpolygonClippingDlg::OnBnClickedButton1()
{
	flag1 = true;
	flag2 = false;
}
//�ü���
void CpolygonClippingDlg::OnBnClickedButton2()
{
	flag2 = true;
	flag1 = false;
}
//�ü��㷨�������㷨��
void CpolygonClippingDlg::OnBnClickedButton3()
{
	flag1 = false;
	flag2 = false;
	//��ü�
	int size = aArray.GetSize();
	CPoint p1, p2;//ǰһ����͵�ǰ��
	int edge = edge1.x;
	for (int i = 0; i < size; i++)
	{
		if (i == 0)//��������������һ����Ϊ��ǰ���ǰһ����
		{
			p1 = aArray.GetAt(size -1);
			p2 = aArray.GetAt(0);
		}
		else{
			//ǰһ����͵�ǰ��
			 p1 = aArray.GetAt(i - 1);
			 p2 = aArray.GetAt(i);
		}
		if ((p1.x<=edge&&p2.x>=edge) || (p1.x>=edge&&p2.x<=edge))//����н���
		{
			intersectPointx(p1, p2, edge);//������߽罻�㣬������intersectP��
			bArray.Add(intersectP);//�����������
		}
		if (p2.x >= edge)//����ڶ��������߿��ڲ࣬�����ڶ�����
		{
			bArray.Add(p2);//�ڲ�ĵڶ������������
		}
	}
	//�Ҳü�
	 size = bArray.GetSize();
	 edge = edge2.x;
	for (int i = 0; i < size; i++)
	{
		if (i == 0)//��������������һ����Ϊ��ǰ���ǰһ����
		{
			p1 = bArray.GetAt(size - 1);
			p2 = bArray.GetAt(0);
		}
		else{
			//ǰһ����͵�ǰ��
			p1 = bArray.GetAt(i - 1);
			p2 = bArray.GetAt(i);
		}
		if ((p1.x<=edge&&p2.x>=edge) || (p1.x>=edge&&p2.x<=edge))//����н���
		{
			intersectPointx(p1, p2, edge);//������߽罻�㣬������intersectP��
			cArray.Add(intersectP);
		}
		if (p2.x <= edge)//����ڶ��������߿��ڲ࣬�����ڶ����㣬��������
		{
			cArray.Add(p2);
		}
	}
	//�²ü�
	size = cArray.GetSize();
	edge = edge2.y;
	for (int i = 0; i < size; i++)
	{
		if (i == 0)//��������������һ����Ϊ��ǰ���ǰһ����
		{
			p1 = cArray.GetAt(size - 1);
			p2 = cArray.GetAt(0);
		}
		else{
			//ǰһ����͵�ǰ��
			p1 = cArray.GetAt(i - 1);
			p2 = cArray.GetAt(i);
		}

		if ((p1.y<=edge&&p2.y>=edge) || (p1.y>=edge&&p2.y<=edge))//����н���
		{
			intersectPointy(p1, p2, edge);//������߽罻�㣬������intersectP��
			dArray.Add(intersectP);
		}
		if (p2.y <= edge)//����ڶ��������߿��ڲ࣬�����ڶ����㣬��������
		{
			dArray.Add(p2);
		}
	}
	//�ϲü�
	size = dArray.GetSize();
	edge = edge1.y;
	for (int i = 0; i < size; i++)
	{
		if (i == 0)//��������������һ����Ϊ��ǰ���ǰһ����
		{
			p1 = dArray.GetAt(size - 1);
			p2 = dArray.GetAt(0);
		}
		else{
			//ǰһ����͵�ǰ��
			p1 = dArray.GetAt(i - 1);
			p2 = dArray.GetAt(i);
		}

		if ((p1.y <= edge&&p2.y >= edge) || (p1.y >= edge&&p2.y <= edge))//����н���
		{
			intersectPointy(p1, p2, edge);//������߽罻�㣬������intersectP��
			eArray.Add(intersectP);
		}
		if (p2.y >= edge)//����ڶ��������߿��ڲ࣬�����ڶ����㣬��������
		{
			eArray.Add(p2);
		}
	}
	flag3 = true;//���вü���ɣ������
}

//�����������
void CpolygonClippingDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rectP;//��ȡ�ؼ��Ĵ�С
	GetDlgItem(IDC_STATIC)->GetWindowRect(&rectP);//��ȡ�ؼ��������Ļ��λ��
	ScreenToClient(rectP);//ת��Ϊ�Ի����ϵ����λ��
	if ((point.x >= rectP.left && point.x <= rectP.right) && (point.y >= rectP.top && point.y <= rectP.bottom))
	{
		point.x = point.x - rectP.left;
		point.y = point.y - rectP.top;
	}
	if (flag1)//���ƶ����
	{		
		aArray.Add(point);
		draw_aFlag = false;//����ǵ�һ�������ʱ������
		last_aFlag = false;
		if (aArray.GetSize() > 1)//�ӵڶ����㿪ʼ����
		{
			draw_aFlag = true;
			last_aFlag = false;
		}
	}
	if (flag2)
	{
		edge1 = point;
		edge2 = point;//��ʼ��
		draw_bFlag = false;
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CpolygonClippingDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect rectP;//��ȡ�ؼ��Ĵ�С
	GetDlgItem(IDC_STATIC)->GetWindowRect(&rectP);//��ȡ�ؼ��������Ļ��λ��
	ScreenToClient(rectP);//ת��Ϊ�Ի����ϵ����λ��
	if ((point.x >= rectP.left && point.x <= rectP.right) && (point.y >= rectP.top && point.y <= rectP.bottom))
	{
		point.x = point.x - rectP.left;
		point.y = point.y - rectP.top;
	}
	if (flag2)
	{
		edge2 = point;
		if (edge1.x > edge2.x)//��֤�ü��߿��Ǵ����Ͻǵ����½�
		{
			xySwap(edge1, edge2);
		}
		draw_bFlag = true;
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}
void CpolygonClippingDlg::OnRButtonDown(UINT nFlags, CPoint point){
	if (flag1)//���ƶ����
	{
		CRect rectP;//��ȡ�ؼ��Ĵ�С
		GetDlgItem(IDC_STATIC)->GetWindowRect(&rectP);//��ȡ�ؼ��������Ļ��λ��
		ScreenToClient(rectP);//ת��Ϊ�Ի����ϵ����λ��

		if (aArray.GetSize() > 2)//�ɹ��ɶ����
		{
			if ((point.x >= rectP.left && point.x <= rectP.right) && (point.y >= rectP.top && point.y <= rectP.bottom))
			{//��֤�ڿؼ���
				point.x = point.x - rectP.left;
				point.y = point.y - rectP.top;
				//aArray.Add(point);
				draw_aFlag = false;
				last_aFlag = true;//����ʱ��ն����
			}
		}
	}
	CDialogEx::OnRButtonDown(nFlags, point);
}
//������һ������κ����ٻ�����
void CpolygonClippingDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	flag1 = false;
	CDialogEx::OnRButtonUp(nFlags, point);
}
//�������
void CpolygonClippingDlg::drawPolygonA(CDC *pDc)
{
	if (flag1)
	{
		CPen myPen;
		myPen.CreatePen(PS_SOLID, 2, RGB(155, 222, 199));//������
		CPen *Oldpen = pDc->SelectObject(&myPen);
		if (draw_aFlag)//����
		{
			int size = aArray.GetSize();
			pDc->MoveTo(aArray.GetAt(size - 2));
			pDc->LineTo(aArray.GetAt(size - 1));
		}
		else if (last_aFlag)
		{
			int size = aArray.GetSize();
			pDc->MoveTo(aArray.GetAt(size - 2));
			pDc->LineTo(aArray.GetAt(size - 1));
			pDc->MoveTo(aArray.GetAt(size - 1));
			pDc->LineTo(aArray.GetAt(0));
		}
	}
	if (flag3)//������ղü����ö����
	{
		CPen myPen;
		myPen.CreatePen(PS_SOLID, 2, RGB(227, 119, 168));//����ɫ
		CPen *Oldpen = pDc->SelectObject(&myPen);
		int size = eArray.GetSize();
		for (int i = 0; i < size; i++)
		{
			if (i == size - 1)
			{
				pDc->MoveTo(eArray.GetAt(i));
				pDc->LineTo(eArray.GetAt(0));
			}
			else
			{
				pDc->MoveTo(eArray.GetAt(i));
				pDc->LineTo(eArray.GetAt(i + 1));
			}
		}
	}
}
//���ü���
void CpolygonClippingDlg::drawCuttingFrame(CDC *pDc)
{
	CPen myPen;
	myPen.CreatePen(PS_SOLID, 2, RGB(99, 167, 255));//������
	int nSavedDC = pDc->SaveDC();
	pDc->SelectObject(&myPen);
	(CBrush*)pDc->SelectStockObject(NULL_BRUSH);//���ĵı�
	if (flag2)//�������ť
	{
		if (draw_bFlag)//���ü�������̧��
		{
			pDc->Rectangle(edge1.x, edge1.y, edge2.x, edge2.y);
		}
	}
}

//��������ұ߽罻��
void CpolygonClippingDlg::intersectPointx(CPoint p1, CPoint p2,int edgex )
{
	if (p1.x<p2.x||p1.x>p2.x)//����߽�ƽ��
	{
		int x = edgex;
		double  k = (p2.y - p1.y)*1.0 / (p2.x - p1.x);
		double y = k *(x - p1.x) + p1.y;
		intersectP.x = x;
		intersectP.y = y;
	}
}
//��������±߽罻��
void CpolygonClippingDlg::intersectPointy(CPoint p1, CPoint p2, int edgey)
{
	if (p1.y<p2.y||p1.y>p2.y)//����߽�ƽ��
	{
		int y = edgey;
		double k, x;
		if (p1.x<p2.x || p1.x>p2.x)//б�ʴ���
		{
			k = (p2.y - p1.y)*1.0 / (p2.x - p1.x);
			x = (y - p1.y) / k + p1.x;
		}	
		intersectP.x = x;
		intersectP.y = y;
	}
}


void CpolygonClippingDlg::xySwap(CPoint &p1, CPoint &p2)
{
		int midx,midy;
		midx = p2.x;
		midy = p2.y;
		p2.x = p1.x;
		p2.y = p1.y;
		p1.x = midx;
		p2.y = midy;
}


void CpolygonClippingDlg::OnBnClickedButton4()
{
	//>GetDC()->FillSolidRect(lRect.left, lRect.top, lRect.Width(), lRect.Height(), RGB(240, 240, 240));
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_STATIC);
	CRect rect;
	pStatic->GetClientRect(&rect);
	pStatic->GetDC()->FillSolidRect(rect.left, rect.top, rect.Width(), rect.Height(), RGB(255, 255, 255));//����ɫ�ð�ɫ
}


