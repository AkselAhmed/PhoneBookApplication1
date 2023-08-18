#pragma once
#include "Structures.h"

#define ACCESSOR_ID 0
#define ACCESSOR_WITHOUT_ID 1

/////////////////////////////////////////////////////////////////////////////
// CBaseAccessor

///<summary> Базов темплейтен клас за аксесорите</summary> 
///<param name="RecordType"> Тип на структурата</param>
template<typename RecordType>
class CBaseAccessor
{
// Macros
// ----------------


// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CBaseAccessor()
	{
	}
	virtual ~CBaseAccessor()
	{
	}

// Methods
// ----------------
public:
	///<summary> Функция която дава достъп до член променливата на аксесора</summary>
	///<returns> Връща референция на член променливата</returns>
	virtual RecordType& GetAccessor() = 0;
	///<summary> Функция която дава достъп до UpdateCounter-а на член променливата на аксесора</summary>
	///<returns> Връща референция на UpdateCounter-а на член променливата</returns>
	virtual long& GetAccessorUpdateCounter() = 0;


// Overrides
// ----------------


// Members
// ----------------
protected:
	///<summary> Член променлива от тип RecordType</summary>
	RecordType m_recRecord;
};
