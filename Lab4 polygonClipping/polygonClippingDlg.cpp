
// polygonClippingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "polygonClipping.h"
#include "polygonClippingDlg.h"
#include "afxdialogex.h"

#include "afxtempl.h"//CArray
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CpolygonClippingDlg 对话框



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


// CpolygonClippingDlg 消息处理程序

BOOL CpolygonClippingDlg::OnInitDialog()
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CpolygonClippingDlg::OnPaint()
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
		CWnd *pWin = GetDlgItem(IDC_STATIC);//获取该控件的指针
		CDC *pDc = pWin->GetDC();//获取该控件的画布		
		if (flag1){ drawPolygonA(pDc); }
		if (flag2){ drawCuttingFrame(pDc); }
		if (flag3){ drawPolygonA(pDc); }
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CpolygonClippingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//多边形
void CpolygonClippingDlg::OnBnClickedButton1()
{
	flag1 = true;
	flag2 = false;
}
//裁剪框
void CpolygonClippingDlg::OnBnClickedButton2()
{
	flag2 = true;
	flag1 = false;
}
//裁剪算法。核心算法。
void CpolygonClippingDlg::OnBnClickedButton3()
{
	flag1 = false;
	flag2 = false;
	//左裁剪
	int size = aArray.GetSize();
	CPoint p1, p2;//前一个点和当前点
	int edge = edge1.x;
	for (int i = 0; i < size; i++)
	{
		if (i == 0)//遇到零就是令最后一个点为当前点的前一个点
		{
			p1 = aArray.GetAt(size -1);
			p2 = aArray.GetAt(0);
		}
		else{
			//前一个点和当前点
			 p1 = aArray.GetAt(i - 1);
			 p2 = aArray.GetAt(i);
		}
		if ((p1.x<=edge&&p2.x>=edge) || (p1.x>=edge&&p2.x<=edge))//如果有交点
		{
			intersectPointx(p1, p2, edge);//求与左边界交点，保存在intersectP中
			bArray.Add(intersectP);//交点加入数组
		}
		if (p2.x >= edge)//如果第二个点在线框内侧，保留第二个点
		{
			bArray.Add(p2);//内侧的第二个点加入数组
		}
	}
	//右裁剪
	 size = bArray.GetSize();
	 edge = edge2.x;
	for (int i = 0; i < size; i++)
	{
		if (i == 0)//遇到零就是令最后一个点为当前点的前一个点
		{
			p1 = bArray.GetAt(size - 1);
			p2 = bArray.GetAt(0);
		}
		else{
			//前一个点和当前点
			p1 = bArray.GetAt(i - 1);
			p2 = bArray.GetAt(i);
		}
		if ((p1.x<=edge&&p2.x>=edge) || (p1.x>=edge&&p2.x<=edge))//如果有交点
		{
			intersectPointx(p1, p2, edge);//求与左边界交点，保存在intersectP中
			cArray.Add(intersectP);
		}
		if (p2.x <= edge)//如果第二个点在线框内侧，保留第二个点，加入数组
		{
			cArray.Add(p2);
		}
	}
	//下裁剪
	size = cArray.GetSize();
	edge = edge2.y;
	for (int i = 0; i < size; i++)
	{
		if (i == 0)//遇到零就是令最后一个点为当前点的前一个点
		{
			p1 = cArray.GetAt(size - 1);
			p2 = cArray.GetAt(0);
		}
		else{
			//前一个点和当前点
			p1 = cArray.GetAt(i - 1);
			p2 = cArray.GetAt(i);
		}

		if ((p1.y<=edge&&p2.y>=edge) || (p1.y>=edge&&p2.y<=edge))//如果有交点
		{
			intersectPointy(p1, p2, edge);//求与左边界交点，保存在intersectP中
			dArray.Add(intersectP);
		}
		if (p2.y <= edge)//如果第二个点在线框内侧，保留第二个点，加入数组
		{
			dArray.Add(p2);
		}
	}
	//上裁剪
	size = dArray.GetSize();
	edge = edge1.y;
	for (int i = 0; i < size; i++)
	{
		if (i == 0)//遇到零就是令最后一个点为当前点的前一个点
		{
			p1 = dArray.GetAt(size - 1);
			p2 = dArray.GetAt(0);
		}
		else{
			//前一个点和当前点
			p1 = dArray.GetAt(i - 1);
			p2 = dArray.GetAt(i);
		}

		if ((p1.y <= edge&&p2.y >= edge) || (p1.y >= edge&&p2.y <= edge))//如果有交点
		{
			intersectPointy(p1, p2, edge);//求与左边界交点，保存在intersectP中
			eArray.Add(intersectP);
		}
		if (p2.y >= edge)//如果第二个点在线框内侧，保留第二个点，加入数组
		{
			eArray.Add(p2);
		}
	}
	flag3 = true;//所有裁剪完成，输出点
}

//单击画多边形
void CpolygonClippingDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rectP;//获取控件的大小
	GetDlgItem(IDC_STATIC)->GetWindowRect(&rectP);//获取控件相对于屏幕的位置
	ScreenToClient(rectP);//转化为对话框上的相对位置
	if ((point.x >= rectP.left && point.x <= rectP.right) && (point.y >= rectP.top && point.y <= rectP.bottom))
	{
		point.x = point.x - rectP.left;
		point.y = point.y - rectP.top;
	}
	if (flag1)//绘制多边形
	{		
		aArray.Add(point);
		draw_aFlag = false;//如果是第一个点点下时不画线
		last_aFlag = false;
		if (aArray.GetSize() > 1)//从第二个点开始连线
		{
			draw_aFlag = true;
			last_aFlag = false;
		}
	}
	if (flag2)
	{
		edge1 = point;
		edge2 = point;//初始化
		draw_bFlag = false;
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CpolygonClippingDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect rectP;//获取控件的大小
	GetDlgItem(IDC_STATIC)->GetWindowRect(&rectP);//获取控件相对于屏幕的位置
	ScreenToClient(rectP);//转化为对话框上的相对位置
	if ((point.x >= rectP.left && point.x <= rectP.right) && (point.y >= rectP.top && point.y <= rectP.bottom))
	{
		point.x = point.x - rectP.left;
		point.y = point.y - rectP.top;
	}
	if (flag2)
	{
		edge2 = point;
		if (edge1.x > edge2.x)//保证裁剪线框是从左上角到右下角
		{
			xySwap(edge1, edge2);
		}
		draw_bFlag = true;
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}
void CpolygonClippingDlg::OnRButtonDown(UINT nFlags, CPoint point){
	if (flag1)//绘制多边形
	{
		CRect rectP;//获取控件的大小
		GetDlgItem(IDC_STATIC)->GetWindowRect(&rectP);//获取控件相对于屏幕的位置
		ScreenToClient(rectP);//转化为对话框上的相对位置

		if (aArray.GetSize() > 2)//可构成多边形
		{
			if ((point.x >= rectP.left && point.x <= rectP.right) && (point.y >= rectP.top && point.y <= rectP.bottom))
			{//保证在控件内
				point.x = point.x - rectP.left;
				point.y = point.y - rectP.top;
				//aArray.Add(point);
				draw_aFlag = false;
				last_aFlag = true;//点下时封闭多边形
			}
		}
	}
	CDialogEx::OnRButtonDown(nFlags, point);
}
//绘制完一个多边形后不能再绘制了
void CpolygonClippingDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	flag1 = false;
	CDialogEx::OnRButtonUp(nFlags, point);
}
//画多边形
void CpolygonClippingDlg::drawPolygonA(CDC *pDc)
{
	if (flag1)
	{
		CPen myPen;
		myPen.CreatePen(PS_SOLID, 2, RGB(155, 222, 199));//清新绿
		CPen *Oldpen = pDc->SelectObject(&myPen);
		if (draw_aFlag)//画线
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
	if (flag3)//输出最终裁剪所得多边形
	{
		CPen myPen;
		myPen.CreatePen(PS_SOLID, 2, RGB(227, 119, 168));//粉紫色
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
//画裁剪框
void CpolygonClippingDlg::drawCuttingFrame(CDC *pDc)
{
	CPen myPen;
	myPen.CreatePen(PS_SOLID, 2, RGB(99, 167, 255));//清新蓝
	int nSavedDC = pDc->SaveDC();
	pDc->SelectObject(&myPen);
	(CBrush*)pDc->SelectStockObject(NULL_BRUSH);//空心的笔
	if (flag2)//点击画框按钮
	{
		if (draw_bFlag)//画裁剪框的鼠标抬起
		{
			pDc->Rectangle(edge1.x, edge1.y, edge2.x, edge2.y);
		}
	}
}

//求边与左右边界交点
void CpolygonClippingDlg::intersectPointx(CPoint p1, CPoint p2,int edgex )
{
	if (p1.x<p2.x||p1.x>p2.x)//不与边界平行
	{
		int x = edgex;
		double  k = (p2.y - p1.y)*1.0 / (p2.x - p1.x);
		double y = k *(x - p1.x) + p1.y;
		intersectP.x = x;
		intersectP.y = y;
	}
}
//求边与上下边界交点
void CpolygonClippingDlg::intersectPointy(CPoint p1, CPoint p2, int edgey)
{
	if (p1.y<p2.y||p1.y>p2.y)//不与边界平行
	{
		int y = edgey;
		double k, x;
		if (p1.x<p2.x || p1.x>p2.x)//斜率存在
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
	pStatic->GetDC()->FillSolidRect(rect.left, rect.top, rect.Width(), rect.Height(), RGB(255, 255, 255));//背景色置白色
}


