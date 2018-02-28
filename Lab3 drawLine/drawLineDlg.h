
// drawLineDlg.h : ͷ�ļ�
//

#pragma once


// CdrawLineDlg �Ի���
class CdrawLineDlg : public CDialogEx
{
	// ����
public:
	CdrawLineDlg(CWnd* pParent = NULL);	// ��׼���캯��

	// �Ի�������
	enum { IDD = IDD_DRAWLINE_DIALOG };

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
	int m_algorithm = 0;//��ʶ��갴���İ�ť; //1��dda;2,bresenham;3,�е㻭Բ
	afx_msg void OnBnClickedButton1();//DDA
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	void drawGrid(CDC *pDc);//���񱳾�
	CPoint p1, p2;//��������ߵĶ˵�
	bool flag = false;//��껭�ߵı�־
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	int x1, y1, x2, y2;//�������������ص����Ͻǵ�����
	double m;
	void ddaLine(CDC *pDc);
	void bresenhamLine(CDC *pDc);
	void xySwap(int &x, int &y);
	bool reverse = false,xnot = false;//����y=x�Գƣ�����y��Գ�
	
};
