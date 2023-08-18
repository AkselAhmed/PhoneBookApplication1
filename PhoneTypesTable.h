#pragma once
#include <atldbcli.h>
#include "BaseTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesTable


/// <summary>Клас за работа с таблица PHONE_TYPES</summary>
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
	///<summary> Пренаписваме функцията от базовия клас</summary>
	///<returns> Връща името на таблицата PHONE_TYPES </returns>
	CString GetTableName() override;
	/// <summary> Пренаписваме функцията от базовия клас</summary>
	///<param name="recPhoneType"> Референция на подадената структура</param>
	///<returns> Връща UpdateCounter-а на обект от структура PHONE_TYPES </returns>
	long& GetRecordUpdateCounter(PHONE_TYPES& recPhoneType) override;


// Members
// ----------------
};