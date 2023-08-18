#pragma once
#include "BaseAccessor.h"

#define PERSONS_ID_COLUMN 1
#define PERSONS_UPDATE_COUNTER_COLUMN 2
#define PERSONS_FIRST_NAME_COLUMN 3
#define PERSONS_SECOND_NAME_COLUMN 4
#define PERSONS_THIRD_NAME_COLUMN 5
#define PERSONS_EGN_COLUMN 6
#define PERSONS_CITY_ID_COLUMN 7
#define PERSONS_ADDRESS_COLUMN 8

/////////////////////////////////////////////////////////////////////////////
// CPersonsAccessor

///<summary> Клас Accessor за структура PERSONS</summary>
class CPersonsAccessor : public CBaseAccessor<PERSONS>
{
// Macros
// ----------------
protected:
	BEGIN_ACCESSOR_MAP(CPersonsAccessor, 2)
		BEGIN_ACCESSOR(ACCESSOR_ID, true)
			COLUMN_ENTRY(PERSONS_ID_COLUMN, m_recPerson.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ACCESSOR_WITHOUT_ID, true)
			COLUMN_ENTRY(PERSONS_UPDATE_COUNTER_COLUMN, m_recPerson.lUpdateCounter)
			COLUMN_ENTRY(PERSONS_FIRST_NAME_COLUMN, m_recPerson.szFirstName)
			COLUMN_ENTRY(PERSONS_SECOND_NAME_COLUMN, m_recPerson.szSecondName)
			COLUMN_ENTRY(PERSONS_THIRD_NAME_COLUMN, m_recPerson.szThirdName)
			COLUMN_ENTRY(PERSONS_EGN_COLUMN, m_recPerson.szEgn)
			COLUMN_ENTRY(PERSONS_CITY_ID_COLUMN, m_recPerson.lCityID)
			COLUMN_ENTRY(PERSONS_ADDRESS_COLUMN, m_recPerson.szAddress)
		END_ACCESSOR()
	END_ACCESSOR_MAP()


// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CPersonsAccessor()
	{
	}
	virtual ~CPersonsAccessor()
	{
	}


// Methods
// ----------------


// Overrides
// ----------------
public:
	///<summary> Функция която дава достъп до UpdateCounter-a на член променливата на аксесора</summary>
	///<returns> Връща референция на UpdateCounter-a на член променливата на аксесора</returns>
	long& GetAccessorUpdateCounter() override
	{
		return m_recPerson.lUpdateCounter;
	}

	///<summary> Функция която дава достъп до член променливата на аксесора</summary>
	///<returns> Връща референция на член променливата на аксесора</returns>
	PERSONS& GetAccessor() override
	{
		return m_recPerson;
	}


// Members
// ----------------
protected:
	///<summary> Член променлива от тип структура PERSONS</summary>
	PERSONS m_recPerson;
};