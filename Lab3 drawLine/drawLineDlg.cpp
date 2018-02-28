
// drawLineDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "drawLine.h"
#include "drawLineDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define GRIDNUM 100 //������
#define GRIDLEN 10//���񳤶�


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	//int m_algorithm;//��ʶ��갴���İ�ť
	//CRect m_Rect;//��Բ��Ӿ�������
	
// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CdrawLineDlg �Ի���



CdrawLineDlg::CdrawLineDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CdrawLineDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	//��ʼ��
	//m_algorithm = 0;
	//m_Rect = CRect(20, 20, 200, 100);
}

void CdrawLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CdrawLineDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CdrawLineDlg::OnBnClickedButton1)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON2, &CdrawLineDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CdrawLineDlg::OnBnClickedButton3)
	ON_WM_LBUTTONUP()
//	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CdrawLineDlg ��Ϣ�������

BOOL CdrawLineDlg::OnInitDialog()
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

void CdrawLineDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void CdrawLineDlg::OnPaint()
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
		CDC MemDC; //������ʾ�豸����
		CBitmap MemBitmap;//����λͼ����
		CRect rect;
		CWnd *pWin;
		CDC *pDc;
		pWin = GetDlgItem(IDC_STATIC);//��ȡ�ÿؼ���ָ��
		pWin->GetClientRect(rect);//�ѿؼ��ĳ����������Ϣ������rect��
		int width = rect.Width();//��ȡ��͸�
		int height = rect.Height();
		CString str;
		pDc = pWin->GetDC();//��ȡ�ÿؼ��Ļ���
		 
		//˫���弼��
		MemDC.CreateCompatibleDC(NULL); //��ʱ�����ܻ�ͼ����Ϊû�еط���
		//��������Ļ��ʾ���ݵ�λͼ��λͼ�Ĵ�С�����ô��ڵĴ�С
		MemBitmap.CreateCompatibleBitmap(pDc, width, height); //��λͼѡ�뵽�ڴ���ʾ�豸�С�
		CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);//���ñ���ɫ��λͼ����ɾ�
		MemDC.FillSolidRect(0, 0, width, height, RGB(255,255,255));//����ɫ�ð�ɫ
		// ��ͼ
		x1 = (int)(p1.x / GRIDLEN)*GRIDLEN;
		y1 = (int)(p1.y / GRIDLEN)*GRIDLEN;
		x2 = (int)(p2.x / GRIDLEN)*GRIDLEN;
		y2 = (int)(p2.y / GRIDLEN)*GRIDLEN;
		m = (y2 - y1)*1.0 / (x2 - x1);//!����ת��
		drawGrid(&MemDC);//����
		if (m_algorithm == 1)
		{
			ddaLine(&MemDC);
		}
		if (m_algorithm == 2)
		{
			bresenhamLine(&MemDC);
		}	
		//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ
		pDc->BitBlt(0, 0, width, height, &MemDC, 0, 0, SRCCOPY);//rect.left

		//��ͼ��ɺ������
		MemDC.SelectObject(pOldBit);//��ǰ���pOldBitѡ����.��ɾ��MemBitmap֮ǰҪ�ȴ��豸���Ƴ���
		MemBitmap.DeleteObject();
		MemDC.DeleteDC();
		CBrush brRed(RGB(128, 0, 0));
		CBrush brGreen(RGB(0, 128, 0));
		CBrush brBlue(RGB(0, 0, 128));
		//pDc->FillRect(rect, &myBrush);	
	}
}
//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CdrawLineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//������
void CdrawLineDlg::drawGrid(CDC *pDc)
{
	CPen myPen;
	myPen.CreatePen(PS_SOLID, 0.1, RGB(122, 122, 122));
	CPen *Oldpen = pDc->SelectObject(&myPen);
	int i;
	int n = (GRIDNUM - 1)* GRIDLEN;
	for (i = 0; i <= n; i = i + GRIDLEN)
	{
		pDc->MoveTo(0, i);
		pDc->LineTo(n, i);
		pDc->MoveTo(i, 0);
		pDc->LineTo(i, n);
	}
}
void CdrawLineDlg::OnBnClickedButton1()
{
	m_algorithm =1;//dda
}
void CdrawLineDlg::OnBnClickedButton2()
{
	m_algorithm = 2;//bresenham
}
void CdrawLineDlg::OnBnClickedButton3()
{
	m_algorithm = 3;//�е㻭Բ
}
//�����Ӧ����
void CdrawLineDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rectP;//��ȡ�ؼ��Ĵ�С
	GetDlgItem(IDC_STATIC)->GetWindowRect(&rectP);//��ȡ�ؼ��������Ļ��λ��
	ScreenToClient(rectP);//ת��Ϊ�Ի����ϵ����λ��
	if ((point.x >= rectP.left && point.x <= rectP.right) && (point.y >= rectP.top && point.y <= rectP.bottom))
	{
		point.x =point.x- rectP.left;
		point.y =point.y- rectP.top;
		p1 = point;
		flag = false;//����ʱ������
	}
	else{//�ؼ��⣬������Ӧ
		flag = false;
	}
	reverse = false; xnot = false;//ÿһ�ζ��Ƿ�Գ���Ҫ����
	CDialogEx::OnLButtonDown(nFlags, point);
}
void CdrawLineDlg::OnLButtonUp(UINT nFlags, CPoint point)         
{
	CRect rectP;//��ȡ�ؼ��Ĵ�С
	GetDlgItem(IDC_STATIC)->GetWindowRect(&rectP);//��ȡ�ؼ��������Ļ��λ��
	ScreenToClient(rectP);//ת��Ϊ�Ի����ϵ����λ��
	//��֤��ͼ�ڿؼ���
	if ((point.x >= rectP.left && point.x <= rectP.right) && (point.y >= rectP.top && point.y <= rectP.bottom))
	{
		//ת��������ڿؼ������꣬�ڿؼ��ϻ�ͼ
		point.x = point.x - rectP.left;
		point.y = point.y - rectP.top;
		p2 = point;
		flag = true;
	}
	else{//�ؼ��⣬������Ӧ
		flag = false;
	}
	//UpdateWindow();
	CDialogEx::OnLButtonUp(nFlags, point);
}

//������������
void CdrawLineDlg::xySwap(int &x, int &y)
{
	int mid;
	mid = x;
	x = y;
	y = mid;
}
//dda��ֱ��
void CdrawLineDlg::ddaLine(CDC *pDc)
{
	if (m_algorithm == 1)
	{
		if (flag){
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(192, 250, 233));//����ɫ
			if (x1 == x2){//б�ʲ�����
				if (y1 > y2)
				{
					xySwap(x1, x2);
					xySwap(y1, y2);
				}
				for (int y = y1; y <= y2; y = y + GRIDLEN)
				{
					CRect rect(x1, y, x1 + GRIDLEN, y + GRIDLEN);
					//CRect rect(pt1, pt2);
					pDc->FillRect(&rect, &myBrush);
				}
			}
			else{//б�ʴ���
				if (m <0){//��б��С���㣬����y��Գ�
					x1 = -x1;
					x2 = -x2;
					m = -m;
					xnot = true;
				}
				if (m > 1){//��б�ʴ���һ������y = x�Գ�
					xySwap(x1, y1);
					xySwap(x2, y2);
					m = 1 / m;
					reverse = true;
				}
				if (x1 > x2){ //��֤x1<x2
					xySwap(x1, x2);
					xySwap(y1, y2);
				}
				if (m >= 0 && m <= 1){
					double y_initial = (y1 / GRIDLEN) *1.0;//������pt.y,����Ѿ�����xy�Ͳ���
					int x, y = y1;
					for (x = x1; x <= x2; x = x + GRIDLEN){
						if (reverse){//m>1
							xySwap(x, y);
						}
						if (xnot){  //m<0
							x = -x;
						}
						CRect rect(x, y, x + GRIDLEN, y + GRIDLEN);
						pDc->FillRect(&rect, &myBrush);
						if (xnot){  //m<0
							x = -x;
						}
						if (reverse){//m>1;������Ӧ�û���ȥ;
							xySwap(x, y);
						}
						//�ı�y��ֵ
						y_initial += m;
						y = (int)(y_initial + 0.5) *GRIDLEN;
						//dc.SetPixel(int(x), int(y + 0.5), RGB(255, 0, 0));
					}//for
				}//if m=[0,1]
			}//else б�ʴ��ڵ����	
		}
	}//if m_algerithm button		
}//DDA
//bresenham��ֱ��
void CdrawLineDlg::bresenhamLine(CDC *pDc)
{
	if (m_algorithm == 2)
	{
		if (flag)
		{
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(227, 119, 168));//����ɫ

			if (x1 == x2){//б�ʲ�����
				if (y1 > y2)
				{
					xySwap(x1, x2);
					xySwap(y1, y2);
				}
				for (int y = y1; y <= y2; y = y + GRIDLEN)
				{
					CRect rect(x1, y, x1 + GRIDLEN, y + GRIDLEN);
					//CRect rect(pt1, pt2);
					pDc->FillRect(&rect, &myBrush);
				}
			}
			else{//б�ʴ���
				if (m <0){//��б��С���㣬����y��Գ�
					x1 = -x1;
					x2 = -x2;
					m = -m;
					xnot = true;
				}
				if (m > 1){//��б�ʴ���һ������y = x�Գ�
					xySwap(x1, y1);
					xySwap(x2, y2);
					m = 1 / m;
					reverse = true;
				}
				if (x1 > x2){ //��֤x1<x2
					xySwap(x1, x2);
					xySwap(y1, y2);
				}

				if (m >= 0 && m <= 1){
					int dy = y2 - y1, dx = x2 - x1;
					int p = dy * 2 - dx;
					int x, y = y1;
					for (x = x1; x <= x2; x += GRIDLEN){
						if (reverse){//m>1
							xySwap(x, y);
						}
						if (xnot){  //m<0
							x = -x;
						}
						CRect rect(x, y, x + GRIDLEN, y + GRIDLEN);
						pDc->FillRect(&rect, &myBrush);
						if (xnot){  //m<0
							x = -x;
						}
						if (reverse){//m>1;������Ӧ�û���ȥ;
							xySwap(x, y);
						}
						//�ı�y��ֵ
						if (p > 0){
							y = y + GRIDLEN;
							p = p + dy * 2 - dx * 2;
						}
						else
						{
							p = p + dy * 2;
						}
						//dc.SetPixel(int(x), int(y + 0.5), RGB(255, 0, 0));
					}//for
				}//if m=[0,1]
			}//else б�ʴ��ڵ����
		}//flag	
	}//if_algorithm
}//bresenham