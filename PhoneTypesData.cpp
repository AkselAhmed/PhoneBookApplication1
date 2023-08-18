#include "pch.h"
#include "PhoneTypesData.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesData


// Constructor / Destructor
// ----------------
CPhoneTypesData::CPhoneTypesData()
{
}

CPhoneTypesData::~CPhoneTypesData()
{
}


// Methods
// ----------------
BOOL CPhoneTypesData::SelectAllData(CPhoneTypesArray& oPhoneTypesArray)
{
	CPhoneTypesTable oPhoneTypeTable;

	// Зареждаме телефонните типове от базата данни в масива oPhoneTypesArray
	if (!oPhoneTypeTable.SelectAll(oPhoneTypesArray))
		return FALSE;

	return TRUE;
}

BOOL CPhoneTypesData::SelectDataWithID(const long lID, PHONE_TYPES& recPhoneType)
{
	CPhoneTypesTable oPhoneTypeTable;

	// Избираме от базата данни телефонен тип и го присвояваме на recPhoneType
	if (!oPhoneTypeTable.SelectWhereID(lID, recPhoneType))
		return FALSE;

	return TRUE;
}

BOOL CPhoneTypesData::UpdateData(PHONE_TYPES& recPhoneType)
{
	CPhoneTypesTable oPhoneTypeTable;

	// Вмъкваме в базата данни нов телефонен тип
	if (!oPhoneTypeTable.UpdateWhereID(recPhoneType))
		return FALSE;

	return TRUE;
}

BOOL CPhoneTypesData::InsertData(PHONE_TYPES& recPhoneType)
{
	CPhoneTypesTable oPhoneTypeTable;

	// Редактираме в базата телефонния тип
	if (!oPhoneTypeTable.Insert(recPhoneType))
		return FALSE;

	return TRUE;
}

BOOL CPhoneTypesData::DeleteData(const long lID)
{
	CPhoneTypesTable oPhoneTypeTable;

	// Изтриваме от базата телефонен тип с ИД = lID
	if (!oPhoneTypeTable.DeleteWhereID(lID))
		return FALSE;

	return TRUE;
}


// Overrides
// ----------------


