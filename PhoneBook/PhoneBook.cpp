// PhoneBook.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include <afxdialogex.h>
#include "PhoneBook.h"
#include "MainFrm.h"

#include "PhoneBookDoc.h"
#include "PhoneBookView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


BEGIN_MESSAGE_MAP(CPhoneBookApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CPhoneBookApp::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


CPhoneBookApp::CPhoneBookApp()
{
	SetAppID(_T("PhoneBook.Application"));
}


CPhoneBookApp theApp;


BOOL CPhoneBookApp::InitInstance()
{
	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	SetRegistryKey(_T("Portfolio\\PhoneBook"));
	LoadStdProfileSettings(4);  

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPhoneBookDoc),
		RUNTIME_CLASS(CMainFrame),
		RUNTIME_CLASS(CPhoneBookView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

int CPhoneBookApp::ExitInstance()
{
	return CWinAppEx::ExitInstance();
}



void CPhoneBookApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
