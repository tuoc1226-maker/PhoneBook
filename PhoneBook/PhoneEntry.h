#pragma once

class CPhoneEntry : public CObject
{
	DECLARE_SERIAL(CPhoneEntry)

public:
	CPhoneEntry();
	CPhoneEntry(const CString& strName, const CString& strSex, const CString& strPhone);
	virtual ~CPhoneEntry();


	virtual void Serialize(CArchive& ar);

	CString m_strName;
	CString m_strSex;
	CString m_strPhone;
};
