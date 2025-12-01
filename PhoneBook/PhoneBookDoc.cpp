// PhoneBookDoc.cpp : implementation of the CPhoneBookDoc class
//
#include "stdafx.h"
#include "PhoneBook.h"
#include "PhoneBookDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CPhoneBookDoc, CDocument)

BEGIN_MESSAGE_MAP(CPhoneBookDoc, CDocument)
END_MESSAGE_MAP()

CPhoneBookDoc::CPhoneBookDoc()
{
}

CPhoneBookDoc::~CPhoneBookDoc()
{
	DeleteAllEntries();
}

BOOL CPhoneBookDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	DeleteAllEntries();
	return TRUE;
}

void CPhoneBookDoc::DeleteAllEntries()
{
	while (!m_listEntries.IsEmpty())
		delete m_listEntries.RemoveHead();
}

CPhoneEntry* CPhoneBookDoc::GetEntryAt(int nIndex) const
{
	POSITION pos = m_listEntries.FindIndex(nIndex);
	if (pos == NULL)
		return NULL;
	return m_listEntries.GetAt(pos);
}

void CPhoneBookDoc::AddEntry(CPhoneEntry* pEntry)
{
	m_listEntries.AddTail(pEntry);
	SetModifiedFlag(TRUE);
	UpdateAllViews(NULL);
}

void CPhoneBookDoc::DeleteEntry(int nIndex)
{
	POSITION pos = m_listEntries.FindIndex(nIndex);
	if (pos == NULL)
		return;
	CPhoneEntry* pEntry = m_listEntries.GetAt(pos);
	m_listEntries.RemoveAt(pos);
	delete pEntry;
	SetModifiedFlag(TRUE);
	UpdateAllViews(NULL);
}

void CPhoneBookDoc::ReplaceEntry(int nIndex, const CString& strName, const CString& strSex, const CString& strPhone)
{
	CPhoneEntry* pEntry = GetEntryAt(nIndex);
	if (pEntry == NULL)
		return;
	pEntry->m_strName = strName;
	pEntry->m_strSex = strSex;
	pEntry->m_strPhone = strPhone;
	SetModifiedFlag(TRUE);
	UpdateAllViews(NULL);
}

void CPhoneBookDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << (DWORD)m_listEntries.GetCount();
		for (POSITION pos = m_listEntries.GetHeadPosition(); pos != NULL; )
		{
			CPhoneEntry* pEntry = m_listEntries.GetNext(pos);
			pEntry->Serialize(ar);
		}
	}
	else
	{
		DeleteAllEntries();

		DWORD dwCount = 0;
		ar >> dwCount;
		for (DWORD i = 0; i < dwCount; i++)
		{
			CPhoneEntry* pEntry = new CPhoneEntry();
			pEntry->Serialize(ar);
			m_listEntries.AddTail(pEntry);
		}
	}
}

#ifdef _DEBUG
void CPhoneBookDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPhoneBookDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG
