#pragma once

#include "BaseAccessor.h"

#define PHONE_NUMBERS_ID_COLUMN 1
#define PHONE_NUMBERS_UPDATE_COUNTER_COLUMN 2
#define PHONE_NUMBERS_PERSON_ID_COLUMN 3
#define PHONE_NUMBERS_PHONE_TYPE_ID_COLUMN 4
#define PHONE_NUMBERS_PHONE_COLUMN 5

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersAccessor

///<summary> ���� Accessor �� ��������� PHONE_NUMBERS</summary>
class CPhoneNumbersAccessor : public CBaseAccessor<PHONE_NUMBERS>
{
// Macros
// ----------------
protected:
	BEGIN_ACCESSOR_MAP(CPhoneNumbersAccessor, 2)
		BEGIN_ACCESSOR(ACCESSOR_ID, true)
			COLUMN_ENTRY(PHONE_NUMBERS_ID_COLUMN, m_recPhoneNumber.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ACCESSOR_WITHOUT_ID, true)
			COLUMN_ENTRY(PHONE_NUMBERS_UPDATE_COUNTER_COLUMN, m_recPhoneNumber.lUpdateCounter)
			COLUMN_ENTRY(PHONE_NUMBERS_PERSON_ID_COLUMN, m_recPhoneNumber.lPersonID)
			COLUMN_ENTRY(PHONE_NUMBERS_PHONE_TYPE_ID_COLUMN, m_recPhoneNumber.lPhoneTypeID)
			COLUMN_ENTRY(PHONE_NUMBERS_PHONE_COLUMN, m_recPhoneNumber.szPhone)
		END_ACCESSOR()
	END_ACCESSOR_MAP()


// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CPhoneNumbersAccessor()
	{
	}
	virtual ~CPhoneNumbersAccessor()
	{
	}


// Methods
// ----------------


// Overrides
// ----------------
public:
	///<summary> ������� ����� ���� ������ �� ���� ������������ �� ��������</summary>
	/// <returns> ����� ���������� �� ���� ������������</returns>
	PHONE_NUMBERS& GetAccessor() override
	{
		return m_recPhoneNumber;
	}

	///<summary> ������� �� ������ �� UpdateCounter-� �� ���� ������������</summary>
	/// <returns> ����� ���������� �� UpdateCounter-� �� ���� ������������ </returns>
	long& GetAccessorUpdateCounter() override
	{
		return m_recPhoneNumber.lUpdateCounter;
	}


// Members
// ----------------
private:
	///<summary> ���� ���������� �� ��� ��������� PHONE_NUMBERS</summary>
	PHONE_NUMBERS m_recPhoneNumber;
};