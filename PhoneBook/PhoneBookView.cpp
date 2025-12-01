// PhoneBookView.cpp : implementation of the CPhoneBookView class
//
#include "stdafx.h"
#include "PhoneBook.h"
#include "PhoneBookDoc.h"
#include "PhoneBookView.h"
#include "EntryDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CPhoneBookView, CListView)

BEGIN_MESSAGE_MAP(CPhoneBookView, CListView)
	ON_COMMAND(ID_ENTRY_ADD, &CPhoneBookView::OnEntryAdd)
	ON_COMMAND(ID_ENTRY_EDIT, &CPhoneBookView::OnEntryEdit)
	ON_COMMAND(ID_ENTRY_DELETE, &CPhoneBookView::OnEntryDelete)
	ON_UPDATE_COMMAND_UI(ID_ENTRY_EDIT, &CPhoneBookView::OnUpdateEntryEditOrDelete)
	ON_UPDATE_COMMAND_UI(ID_ENTRY_DELETE, &CPhoneBookView::OnUpdateEntryEditOrDelete)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CPhoneBookView::OnLvnItemActivate)
END_MESSAGE_MAP()

CPhoneBookView::CPhoneBookView()
{
}

CPhoneBookView::~CPhoneBookView()
{
}

BOOL CPhoneBookView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}

void CPhoneBookView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CListCtrl& list = GetListCtrl();
	list.SetExtendedStyle(list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	list.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 180);
	list.InsertColumn(1, _T("Sex"), LVCFMT_LEFT, 80);
	list.InsertColumn(2, _T("Phone Number"), LVCFMT_LEFT, 150);

	RefreshList();
}

void CPhoneBookView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	RefreshList();
}

void CPhoneBookView::RefreshList()
{
	CPhoneBookDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CListCtrl& list = GetListCtrl();
	list.DeleteAllItems();

	int nCount = pDoc->GetEntryCount();
	for (int i = 0; i < nCount; i++)
	{
		CPhoneEntry* pEntry = pDoc->GetEntryAt(i);
		int nItem = list.InsertItem(i, pEntry->m_strName);
		list.SetItemText(nItem, 1, pEntry->m_strSex);
		list.SetItemText(nItem, 2, pEntry->m_strPhone);
	}
}

int CPhoneBookView::GetSelectedIndex() const
{
	const CListCtrl& list = const_cast<CPhoneBookView*>(this)->GetListCtrl();
	POSITION pos = list.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return -1;
	return list.GetNextSelectedItem(pos);
}

void CPhoneBookView::OnEntryAdd()
{
	CEntryDlg dlg;
	dlg.m_strCaption = _T("Add Entry");
	if (dlg.DoModal() == IDOK)
	{
		CPhoneEntry* pEntry = new CPhoneEntry(dlg.m_strName, dlg.m_strSex, dlg.m_strPhone);
		GetDocument()->AddEntry(pEntry);
	}
}

void CPhoneBookView::OnEntryEdit()
{
	int nIndex = GetSelectedIndex();
	if (nIndex < 0)
		return;

	CPhoneEntry* pEntry = GetDocument()->GetEntryAt(nIndex);
	if (pEntry == NULL)
		return;

	CEntryDlg dlg;
	dlg.m_strCaption = _T("Edit Entry");
	dlg.m_strName = pEntry->m_strName;
	dlg.m_strSex = pEntry->m_strSex;
	dlg.m_strPhone = pEntry->m_strPhone;

	if (dlg.DoModal() == IDOK)
	{
		GetDocument()->ReplaceEntry(nIndex, dlg.m_strName, dlg.m_strSex, dlg.m_strPhone);
	}
}

void CPhoneBookView::OnEntryDelete()
{
	int nIndex = GetSelectedIndex();
	if (nIndex < 0)
		return;

	if (AfxMessageBox(_T("Delete the selected entry?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		GetDocument()->DeleteEntry(nIndex);
	}
}

void CPhoneBookView::OnUpdateEntryEditOrDelete(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetSelectedIndex() >= 0);
}

void CPhoneBookView::OnLvnItemActivate(NMHDR* pNMHDR, LRESULT* pResult)
{
	OnEntryEdit();
	*pResult = 0;
}

void CPhoneBookView::OnDraw(CDC* /*pDC*/)
{

}

#ifdef _DEBUG
void CPhoneBookView::AssertValid() const
{
	CListView::AssertValid();
}

void CPhoneBookView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CPhoneBookDoc* CPhoneBookView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhoneBookDoc)));
	return (CPhoneBookDoc*)m_pDocument;
}
#endif //_DEBUG
