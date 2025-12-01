
#pragma once

#include "PhoneEntry.h"

class CPhoneBookDoc : public CDocument
{
protected:
	CPhoneBookDoc();
	DECLARE_DYNCREATE(CPhoneBookDoc)

public:
	CTypedPtrList<CObList, CPhoneEntry*> m_listEntries;

public:
	int GetEntryCount() const { return (int)m_listEntries.GetCount(); }
	CPhoneEntry* GetEntryAt(int nIndex) const;

	void AddEntry(CPhoneEntry* pEntry);
	void DeleteEntry(int nIndex);
	void ReplaceEntry(int nIndex, const CString& strName, const CString& strSex, const CString& strPhone);

public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

public:
	virtual ~CPhoneBookDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void DeleteAllEntries();

protected:
	DECLARE_MESSAGE_MAP()
};
