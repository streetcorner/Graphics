
// polygonClipping.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CpolygonClippingApp: 
// �йش����ʵ�֣������ polygonClipping.cpp
//

class CpolygonClippingApp : public CWinApp
{
public:
	CpolygonClippingApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CpolygonClippingApp theApp;