
// polygonClippingDlg.h : 头文件
//

#pragma once


// CpolygonClippingDlg 对话框
class CpolygonClippingDlg : public CDialogEx
{
// 构造
public:
	CpolygonClippingDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_POLYGONCLIPPING_DIALOG };

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
	afx_msg void OnBnClickedButton1();//多边形
	afx_msg void OnBnClickedButton2();//裁剪框
	afx_msg void OnBnClickedButton3();//裁剪
	bool flag1 = false;//绘制多边形
	bool flag2 = false;//绘制裁剪线框
	bool flag3 = false;//裁剪
	bool draw_aFlag = false;//多边形前面的点是否单击响应
	bool last_aFlag = false;//封闭多边形
	bool draw_bFlag = false;//裁剪框的绘制是否单击响应
	bool swapFlag = false;//标志是否有交换两点
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CArray <CPoint, CPoint&> aArray;//存储类型CPoint,访问类型CPoint
	CArray <CPoint, CPoint&> bArray; //存储左裁剪结果
	CArray <CPoint, CPoint&> cArray;
	CArray <CPoint, CPoint&> dArray;
	CArray <CPoint, CPoint&> eArray;
	CPoint edge1, edge2;//鼠标点击画裁剪框的端点
	CPoint intersectP;
	void drawPolygonA(CDC *pDc);
	void drawPolygonE(CDC *pDc, CArray <CPoint, CPoint&> Array);
	void drawCuttingFrame(CDC *pDc);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	void intersectPointx(CPoint p1, CPoint p2, int edgex);//x,左右边界
	void intersectPointy(CPoint p1, CPoint p2, int edgey);//y,上下边界
	void xySwap(CPoint &p1, CPoint &p2);
	afx_msg void OnBnClickedButton4();//显示裁剪所得

};
