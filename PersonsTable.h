#pragma once
#include <atldbcli.h>
#include "BaseTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsTable

/// <summary>���� �� ������ � ������� PERSONS</summary>
class CPersonsTable : public CBaseTable<PERSONS, CPersonsAccessor>
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	/// <summary> ����������� �� ����������� ����� ���� �� ������ ������ �����</summary>
	CPersonsTable(CSession* pSession = NULL);
	~CPersonsTable();


// Methods
// ----------------


// Overrides
// ----------------
public:
	///<summary> ������������ ��������� �� ������� ����</summary>
	///<returns> ����� ����� �� ��������� PERSONS </returns>
	CString GetTableName() override;

	/// <summary> ������������ ��������� �� ������� ����</summary>
	///<param name="recPerson"> ���������� �� ���������� ���������</param>
	///<returns> ����� UpdateCounter-� �� ����� �� ��������� PERSONS </returns>
	long& GetRecordUpdateCounter(PERSONS& recPerson) override;


// Members
// ----------------
};