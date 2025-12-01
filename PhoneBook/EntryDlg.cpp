// EntryDlg.cpp : implementation of CEntryDlg
//
#include "stdafx.h"
#include "PhoneBook.h"
#include "EntryDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CEntryDlg::CEntryDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ENTRYDLG, pParent)
	, m_strName(_T(""))
	, m_strSex(_T(""))
	, m_strPhone(_T(""))
	, m_strCaption(_T("Entry"))
{
}

CEntryDlg::~CEntryDlg()
{
}

void CEntryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_strPhone);
	DDX_Control(pDX, IDC_COMBO_SEX, m_ctrlSex);

	if (!pDX->m_bSaveAndValidate)
	{

	}
}

BOOL CEntryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(m_strCaption);

	m_ctrlSex.AddString(_T("Male"));
	m_ctrlSex.AddString(_T("Female"));

	if (m_strSex.IsEmpty())
		m_ctrlSex.SetCurSel(0);
	else
		m_ctrlSex.SelectString(-1, m_strSex);

	return TRUE;
}

void CEntryDlg::OnOK()
{
	UpdateData(TRUE); // pull name/phone from edit controls

	int nSel = m_ctrlSex.GetCurSel();
	if (nSel != CB_ERR)
		m_ctrlSex.GetLBText(nSel, m_strSex);

	m_strName.Trim();
	m_strPhone.Trim();

	if (m_strName.IsEmpty())
	{
		AfxMessageBox(_T("Please enter a name."));
		GetDlgItem(IDC_EDIT_NAME)->SetFocus();
		return;
	}

	CDialogEx::OnOK();
}

BEGIN_MESSAGE_MAP(CEntryDlg, CDialogEx)
END_MESSAGE_MAP()
