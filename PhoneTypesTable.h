#pragma once
#include <atldbcli.h>
#include "BaseTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesTable


/// <summary>���� �� ������ � ������� PHONE_TYPES</summary>
class CPhoneTypesTable : public CBaseTable<PHONE_TYPES, CPhoneTypesAccessor>
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CPhoneTypesTable();
	virtual ~CPhoneTypesTable();

	
// Methods
// ----------------


// Overrides
// ----------------
public:
	///<summary> ������������ ��������� �� ������� ����</summary>
	///<returns> ����� ����� �� ��������� PHONE_TYPES </returns>
	CString GetTableName() override;
	/// <summary> ������������ ��������� �� ������� ����</summary>
	///<param name="recPhoneType"> ���������� �� ���������� ���������</param>
	///<returns> ����� UpdateCounter-� �� ����� �� ��������� PHONE_TYPES </returns>
	long& GetRecordUpdateCounter(PHONE_TYPES& recPhoneType) override;


// Members
// ----------------
};