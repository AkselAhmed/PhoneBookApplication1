#pragma once
#include <atldbcli.h>
#include "BaseTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsTable

/// <summary>Клас за работа с таблица PERSONS</summary>
class CPersonsTable : public CBaseTable<PERSONS, CPersonsAccessor>
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	/// <summary> Подразбиращ се конструктор който може да приема външна сесия</summary>
	CPersonsTable(CSession* pSession = NULL);
	~CPersonsTable();


// Methods
// ----------------


// Overrides
// ----------------
public:
	///<summary> Пренаписваме функцията от базовия клас</summary>
	///<returns> Връща името на таблицата PERSONS </returns>
	CString GetTableName() override;

	/// <summary> Пренаписваме функцията от базовия клас</summary>
	///<param name="recPerson"> Референция на подадената структура</param>
	///<returns> Връща UpdateCounter-а на обект от структура PERSONS </returns>
	long& GetRecordUpdateCounter(PERSONS& recPerson) override;


// Members
// ----------------
};