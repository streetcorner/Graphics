
// drawLineDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "drawLine.h"
#include "drawLineDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define GRIDNUM 100 //网格数
#define GRIDLEN 10//网格长度


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	//int m_algorithm;//标识鼠标按的哪按钮
	//CRect m_Rect;//椭圆外接矩形坐标
	
// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CdrawLineDlg 对话框



CdrawLineDlg::CdrawLineDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CdrawLineDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	//初始化
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


// CdrawLineDlg 消息处理程序

BOOL CdrawLineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。


void CdrawLineDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDC MemDC; //定义显示设备对象
		CBitmap MemBitmap;//定义位图对象　
		CRect rect;
		CWnd *pWin;
		CDC *pDc;
		pWin = GetDlgItem(IDC_STATIC);//获取该控件的指针
		pWin->GetClientRect(rect);//把控件的长宽、坐标等信息保存在rect里
		int width = rect.Width();//获取宽和高
		int height = rect.Height();
		CString str;
		pDc = pWin->GetDC();//获取该控件的画布
		 
		//双缓冲技术
		MemDC.CreateCompatibleDC(NULL); //这时还不能绘图，因为没有地方画
		//建立与屏幕显示兼容的位图，位图的大小这里用窗口的大小
		MemBitmap.CreateCompatibleBitmap(pDc, width, height); //将位图选入到内存显示设备中　
		CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);//先用背景色将位图清除干净
		MemDC.FillSolidRect(0, 0, width, height, RGB(255,255,255));//背景色置白色
		// 画图
		x1 = (int)(p1.x / GRIDLEN)*GRIDLEN;
		y1 = (int)(p1.y / GRIDLEN)*GRIDLEN;
		x2 = (int)(p2.x / GRIDLEN)*GRIDLEN;
		y2 = (int)(p2.y / GRIDLEN)*GRIDLEN;
		m = (y2 - y1)*1.0 / (x2 - x1);//!类型转换
		drawGrid(&MemDC);//网格
		if (m_algorithm == 1)
		{
			ddaLine(&MemDC);
		}
		if (m_algorithm == 2)
		{
			bresenhamLine(&MemDC);
		}	
		//将内存中的图拷贝到屏幕上进行显示
		pDc->BitBlt(0, 0, width, height, &MemDC, 0, 0, SRCCOPY);//rect.left

		//绘图完成后的清理
		MemDC.SelectObject(pOldBit);//把前面的pOldBit选回来.在删除MemBitmap之前要先从设备中移除它
		MemBitmap.DeleteObject();
		MemDC.DeleteDC();
		CBrush brRed(RGB(128, 0, 0));
		CBrush brGreen(RGB(0, 128, 0));
		CBrush brBlue(RGB(0, 0, 128));
		//pDc->FillRect(rect, &myBrush);	
	}
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CdrawLineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//画网格
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
	m_algorithm = 3;//中点画圆
}
//鼠标响应函数
void CdrawLineDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CRect rectP;//获取控件的大小
	GetDlgItem(IDC_STATIC)->GetWindowRect(&rectP);//获取控件相对于屏幕的位置
	ScreenToClient(rectP);//转化为对话框上的相对位置
	if ((point.x >= rectP.left && point.x <= rectP.right) && (point.y >= rectP.top && point.y <= rectP.bottom))
	{
		point.x =point.x- rectP.left;
		point.y =point.y- rectP.top;
		p1 = point;
		flag = false;//点下时不画线
	}
	else{//控件外，不做响应
		flag = false;
	}
	reverse = false; xnot = false;//每一次都是否对称需要重置
	CDialogEx::OnLButtonDown(nFlags, point);
}
void CdrawLineDlg::OnLButtonUp(UINT nFlags, CPoint point)         
{
	CRect rectP;//获取控件的大小
	GetDlgItem(IDC_STATIC)->GetWindowRect(&rectP);//获取控件相对于屏幕的位置
	ScreenToClient(rectP);//转化为对话框上的相对位置
	//保证画图在控件内
	if ((point.x >= rectP.left && point.x <= rectP.right) && (point.y >= rectP.top && point.y <= rectP.bottom))
	{
		//转化成相对于控件的坐标，在控件上绘图
		point.x = point.x - rectP.left;
		point.y = point.y - rectP.top;
		p2 = point;
		flag = true;
	}
	else{//控件外，不做响应
		flag = false;
	}
	//UpdateWindow();
	CDialogEx::OnLButtonUp(nFlags, point);
}

//交换两点坐标
void CdrawLineDlg::xySwap(int &x, int &y)
{
	int mid;
	mid = x;
	x = y;
	y = mid;
}
//dda画直线
void CdrawLineDlg::ddaLine(CDC *pDc)
{
	if (m_algorithm == 1)
	{
		if (flag){
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(192, 250, 233));//蓝绿色
			if (x1 == x2){//斜率不存在
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
			else{//斜率存在
				if (m <0){//若斜率小于零，关于y轴对称
					x1 = -x1;
					x2 = -x2;
					m = -m;
					xnot = true;
				}
				if (m > 1){//若斜率大于一，关于y = x对称
					xySwap(x1, y1);
					xySwap(x2, y2);
					m = 1 / m;
					reverse = true;
				}
				if (x1 > x2){ //保证x1<x2
					xySwap(x1, x2);
					xySwap(y1, y2);
				}
				if (m >= 0 && m <= 1){
					double y_initial = (y1 / GRIDLEN) *1.0;//不能用pt.y,如果已经交换xy就不对
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
						if (reverse){//m>1;换完了应该换回去;
							xySwap(x, y);
						}
						//改变y的值
						y_initial += m;
						y = (int)(y_initial + 0.5) *GRIDLEN;
						//dc.SetPixel(int(x), int(y + 0.5), RGB(255, 0, 0));
					}//for
				}//if m=[0,1]
			}//else 斜率存在的情况	
		}
	}//if m_algerithm button		
}//DDA
//bresenham画直线
void CdrawLineDlg::bresenhamLine(CDC *pDc)
{
	if (m_algorithm == 2)
	{
		if (flag)
		{
			CBrush myBrush;
			myBrush.CreateSolidBrush(RGB(227, 119, 168));//粉紫色

			if (x1 == x2){//斜率不存在
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
			else{//斜率存在
				if (m <0){//若斜率小于零，关于y轴对称
					x1 = -x1;
					x2 = -x2;
					m = -m;
					xnot = true;
				}
				if (m > 1){//若斜率大于一，关于y = x对称
					xySwap(x1, y1);
					xySwap(x2, y2);
					m = 1 / m;
					reverse = true;
				}
				if (x1 > x2){ //保证x1<x2
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
						if (reverse){//m>1;换完了应该换回去;
							xySwap(x, y);
						}
						//改变y的值
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
			}//else 斜率存在的情况
		}//flag	
	}//if_algorithm
}//bresenham