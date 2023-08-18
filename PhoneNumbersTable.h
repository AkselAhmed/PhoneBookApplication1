#pragma once
#include <atldbcli.h>
#include "BaseTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersTable


/// <summary>Клас за работа с таблица PHONE_NUMBERS</summary>
class CPhoneNumbersTable : public CBaseTable<PHONE_NUMBERS, CPhoneNumbersAccessor>
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	/// <summary> Подразбиращ се конструктор който може да приема външна сесия</summary>
	CPhoneNumbersTable(CSession* pSession = NULL);
	~CPhoneNumbersTable();


// Methods
// ----------------


// Overrides
// ----------------
public:
	///<summary> Пренаписваме функцията от базовия клас</summary>
	///<returns> Връща името на таблицата PHONE_NUMBERS</returns>
	CString GetTableName() override;

	/// <summary> Пренаписваме функцията от базовия клас</summary>
	///<param name="recPhoneNumber"> Референция на подадената структура</param>
	///<returns> Връща UpdateCounter-а на обект от структура PHONE_NUMBERS </returns>
	long& GetRecordUpdateCounter(PHONE_NUMBERS& recPhoneNumber) override;


// Members
// ----------------
};