#pragma once
#include "BaseAccessor.h"

#define PHONE_TYPES_ID_COLUMN 1
#define PHONE_TYPES_UPDATE_COUNTER_COLUMN 2
#define PHONE_TYPES_TYPE_COLUMN 3

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesAccessor

///<summary> Клас Accessor за структура PHONE_TYPES</summary>
class CPhoneTypesAccessor : public CBaseAccessor<PHONE_TYPES>
{
// Macros
// ----------------
protected:
	BEGIN_ACCESSOR_MAP(CPhoneTypesAccessor, 2)
		BEGIN_ACCESSOR(ACCESSOR_ID, true)
			COLUMN_ENTRY(PHONE_TYPES_ID_COLUMN, m_recPhoneType.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ACCESSOR_WITHOUT_ID, true)
			COLUMN_ENTRY(PHONE_TYPES_UPDATE_COUNTER_COLUMN, m_recPhoneType.lUpdateCounter)
			COLUMN_ENTRY(PHONE_TYPES_TYPE_COLUMN, m_recPhoneType.szType)
		END_ACCESSOR()
	END_ACCESSOR_MAP()


// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CPhoneTypesAccessor()
	{
	}
	virtual ~CPhoneTypesAccessor()
	{
	}


// Methods
// ----------------


// Overrides
// ----------------
public:
	///<summary> Функция която дава достъп до член променливата на аксесора</summary>
	/// <returns> Връща референция на член променливата</returns>
	PHONE_TYPES& GetAccessor() override
	{
		return m_recPhoneType;
	}

	///<summary> Функция за достъп до UpdateCounter-а на член променливата</summary>
	/// <returns> Връща референция на UpdateCounter-а на член променливата </returns>
	long& GetAccessorUpdateCounter() override
	{
		return m_recPhoneType.lUpdateCounter;
	}


// Members
// ----------------
private:
	///<summary> Член променлива от тип структура PHONE_TYPES</summary>
	PHONE_TYPES m_recPhoneType;
};