#pragma once

#include <afxcview.h>
#include "PhoneEntry.h"

class CPhoneBookView : public CListView
{
protected:
	CPhoneBookView();
	DECLARE_DYNCREATE(CPhoneBookView)

public:
	CPhoneBookDoc* GetDocument() const;

public:
	void RefreshList();
	int GetSelectedIndex() const;


public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);


public:
	virtual ~CPhoneBookView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg void OnEntryAdd();
	afx_msg void OnEntryEdit();
	afx_msg void OnEntryDelete();
	afx_msg void OnUpdateEntryEditOrDelete(CCmdUI* pCmdUI);
	afx_msg void OnLvnItemActivate(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PhoneBookView.cpp
inline CPhoneBookDoc* CPhoneBookView::GetDocument() const
   { return reinterpret_cast<CPhoneBookDoc*>(m_pDocument); }
#endif
