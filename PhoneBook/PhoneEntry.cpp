// PhoneEntry.cpp : implementation of CPhoneEntry
//
#include "stdafx.h"
#include "PhoneEntry.h"

IMPLEMENT_SERIAL(CPhoneEntry, CObject, 1)

CPhoneEntry::CPhoneEntry()
{
}

CPhoneEntry::CPhoneEntry(const CString& strName, const CString& strSex, const CString& strPhone)
	: m_strName(strName), m_strSex(strSex), m_strPhone(strPhone)
{
}

CPhoneEntry::~CPhoneEntry()
{
}

void CPhoneEntry::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_strName << m_strSex << m_strPhone;
	}
	else
	{
		ar >> m_strName >> m_strSex >> m_strPhone;
	}
}
