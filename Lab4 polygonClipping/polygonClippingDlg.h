
// polygonClippingDlg.h : ͷ�ļ�
//

#pragma once


// CpolygonClippingDlg �Ի���
class CpolygonClippingDlg : public CDialogEx
{
// ����
public:
	CpolygonClippingDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_POLYGONCLIPPING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();//�����
	afx_msg void OnBnClickedButton2();//�ü���
	afx_msg void OnBnClickedButton3();//�ü�
	bool flag1 = false;//���ƶ����
	bool flag2 = false;//���Ʋü��߿�
	bool flag3 = false;//�ü�
	bool draw_aFlag = false;//�����ǰ��ĵ��Ƿ񵥻���Ӧ
	bool last_aFlag = false;//��ն����
	bool draw_bFlag = false;//�ü���Ļ����Ƿ񵥻���Ӧ
	bool swapFlag = false;//��־�Ƿ��н�������
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CArray <CPoint, CPoint&> aArray;//�洢����CPoint,��������CPoint
	CArray <CPoint, CPoint&> bArray; //�洢��ü����
	CArray <CPoint, CPoint&> cArray;
	CArray <CPoint, CPoint&> dArray;
	CArray <CPoint, CPoint&> eArray;
	CPoint edge1, edge2;//��������ü���Ķ˵�
	CPoint intersectP;
	void drawPolygonA(CDC *pDc);
	void drawPolygonE(CDC *pDc, CArray <CPoint, CPoint&> Array);
	void drawCuttingFrame(CDC *pDc);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	void intersectPointx(CPoint p1, CPoint p2, int edgex);//x,���ұ߽�
	void intersectPointy(CPoint p1, CPoint p2, int edgey);//y,���±߽�
	void xySwap(CPoint &p1, CPoint &p2);
	afx_msg void OnBnClickedButton4();//��ʾ�ü�����

};
