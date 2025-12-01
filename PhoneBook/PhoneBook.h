#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"

class CPhoneBookApp : public CWinAppEx
{
public:
	CPhoneBookApp();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPhoneBookApp theApp;
