#pragma once
#include <atldbcli.h>
#include "BaseTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersTable


/// <summary>���� �� ������ � ������� PHONE_NUMBERS</summary>
class CPhoneNumbersTable : public CBaseTable<PHONE_NUMBERS, CPhoneNumbersAccessor>
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	/// <summary> ����������� �� ����������� ����� ���� �� ������ ������ �����</summary>
	CPhoneNumbersTable(CSession* pSession = NULL);
	~CPhoneNumbersTable();


// Methods
// ----------------


// Overrides
// ----------------
public:
	///<summary> ������������ ��������� �� ������� ����</summary>
	///<returns> ����� ����� �� ��������� PHONE_NUMBERS</returns>
	CString GetTableName() override;

	/// <summary> ������������ ��������� �� ������� ����</summary>
	///<param name="recPhoneNumber"> ���������� �� ���������� ���������</param>
	///<returns> ����� UpdateCounter-� �� ����� �� ��������� PHONE_NUMBERS </returns>
	long& GetRecordUpdateCounter(PHONE_NUMBERS& recPhoneNumber) override;


// Members
// ----------------
};