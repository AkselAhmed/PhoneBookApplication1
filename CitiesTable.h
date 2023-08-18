#pragma once
#include <atldbcli.h>
#include "BaseTable.h"


//////////////////////////////
// CCitiesTable


/// <summary>Клас за работа с таблица CITIES</summary>
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
	///<summary> Пренаписваме функцията от базовия клас</summary>
	///<returns> Връща името на таблицата CITIES </returns>
	CString GetTableName() override;
	/// <summary> Пренаписваме функцията от базовия клас</summary>
	///<param name="recCity"> Референция на подадената структура</param>
	///<returns> Връща UpdateCounter-а на обект от структура CITIES </returns>
	long& GetRecordUpdateCounter(CITIES& recCity) override;


// Members
// ----------------
};