#include "pch.h"
#include "PhoneNumbersData.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersData


// Constructor / Destructor
// ----------------
CPhoneNumbersData::CPhoneNumbersData()
{
}

CPhoneNumbersData::~CPhoneNumbersData()
{
}


// Methods
// ----------------
BOOL CPhoneNumbersData::SelectAllData(CPhoneNumbersArray& oPhoneNumbersArray)
{
	CPhoneNumbersTable oPhoneNumbersTable;

	// Зареждаме всички телефонни номера от базата данни в масива oPhoneNumbersArray
	if (!oPhoneNumbersTable.SelectAll(oPhoneNumbersArray))
		return FALSE;

	return TRUE;
}

BOOL CPhoneNumbersData::SelectDataWithID(const long lID, PHONE_NUMBERS& recPhoneNumber)
{
	CPhoneNumbersTable oPhoneNumbersTable;

	// Избираме телефонния номер от базата данни с ИД = lID и го присвояваме на recPhoneNumber
	if (!oPhoneNumbersTable.SelectWhereID(lID, recPhoneNumber))
		return FALSE;

	return TRUE;
}

BOOL CPhoneNumbersData::UpdateData(PHONE_NUMBERS& recPhoneNumber)
{
	CPhoneNumbersTable oPhoneNumbersTable;

	// Редактираме телефонния номер от базата данни с новия recPhoneNumber
	if (!oPhoneNumbersTable.UpdateWhereID(recPhoneNumber))
		return FALSE;

	return TRUE;
}

BOOL CPhoneNumbersData::InsertData(PHONE_NUMBERS& recPhoneNumber)
{
	CPhoneNumbersTable oPhoneNumbersTable;

	// Добавяме нов телефонен номер в базата данни
	if (!oPhoneNumbersTable.Insert(recPhoneNumber))
		return FALSE;

	return TRUE;
}

BOOL CPhoneNumbersData::DeleteData(const long lID)
{
	CPhoneNumbersTable oPhoneNumbersTable;

	// Изтриваме телефонен номер от базата данни
	if (!oPhoneNumbersTable.DeleteWhereID(lID))
		return FALSE;

	return TRUE;
}


// Overrides
// ----------------


