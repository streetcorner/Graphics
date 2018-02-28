
// drawLineDlg.h : 头文件
//

#pragma once


// CdrawLineDlg 对话框
class CdrawLineDlg : public CDialogEx
{
	// 构造
public:
	CdrawLineDlg(CWnd* pParent = NULL);	// 标准构造函数

	// 对话框数据
	enum { IDD = IDD_DRAWLINE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	int m_algorithm = 0;//标识鼠标按的哪按钮; //1，dda;2,bresenham;3,中点画圆
	afx_msg void OnBnClickedButton1();//DDA
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	void drawGrid(CDC *pDc);//网格背景
	CPoint p1, p2;//鼠标点击画线的端点
	bool flag = false;//鼠标画线的标志
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	int x1, y1, x2, y2;//单击点所在像素的左上角点坐标
	double m;
	void ddaLine(CDC *pDc);
	void bresenhamLine(CDC *pDc);
	void xySwap(int &x, int &y);
	bool reverse = false,xnot = false;//关于y=x对称，关于y轴对称
	
};
