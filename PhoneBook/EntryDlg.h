#pragma once
#include <afxdialogex.h>
#include "resource.h"

class CEntryDlg : public CDialogEx
{
public:
	CEntryDlg(CWnd* pParent = nullptr);
	virtual ~CEntryDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ENTRYDLG };
#endif

	CString m_strName;
	CString m_strSex;
	CString m_strPhone;
	CString m_strCaption;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	CComboBox m_ctrlSex;

	DECLARE_MESSAGE_MAP()
};
