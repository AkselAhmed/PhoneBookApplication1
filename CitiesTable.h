#pragma once
#include <atldbcli.h>
#include "BaseTable.h"


//////////////////////////////
// CCitiesTable


/// <summary>���� �� ������ � ������� CITIES</summary>
class CCitiesTable : public CBaseTable<CITIES, CCitiesAccessor>  
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CCitiesTable();
	virtual ~CCitiesTable();


// Methods
// ----------------


// Overrides
// ----------------
public:
	///<summary> ������������ ��������� �� ������� ����</summary>
	///<returns> ����� ����� �� ��������� CITIES </returns>
	CString GetTableName() override;
	/// <summary> ������������ ��������� �� ������� ����</summary>
	///<param name="recCity"> ���������� �� ���������� ���������</param>
	///<returns> ����� UpdateCounter-� �� ����� �� ��������� CITIES </returns>
	long& GetRecordUpdateCounter(CITIES& recCity) override;


// Members
// ----------------
};