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

	// ��������� ����������� ������ �� ������ ����� � ������ oPhoneTypesArray
	if (!oPhoneTypeTable.SelectAll(oPhoneTypesArray))
		return FALSE;

	return TRUE;
}

BOOL CPhoneTypesData::SelectDataWithID(const long lID, PHONE_TYPES& recPhoneType)
{
	CPhoneTypesTable oPhoneTypeTable;

	// �������� �� ������ ����� ��������� ��� � �� ����������� �� recPhoneType
	if (!oPhoneTypeTable.SelectWhereID(lID, recPhoneType))
		return FALSE;

	return TRUE;
}

BOOL CPhoneTypesData::UpdateData(PHONE_TYPES& recPhoneType)
{
	CPhoneTypesTable oPhoneTypeTable;

	// �������� � ������ ����� ��� ��������� ���
	if (!oPhoneTypeTable.UpdateWhereID(recPhoneType))
		return FALSE;

	return TRUE;
}

BOOL CPhoneTypesData::InsertData(PHONE_TYPES& recPhoneType)
{
	CPhoneTypesTable oPhoneTypeTable;

	// ����������� � ������ ���������� ���
	if (!oPhoneTypeTable.Insert(recPhoneType))
		return FALSE;

	return TRUE;
}

BOOL CPhoneTypesData::DeleteData(const long lID)
{
	CPhoneTypesTable oPhoneTypeTable;

	// ��������� �� ������ ��������� ��� � �� = lID
	if (!oPhoneTypeTable.DeleteWhereID(lID))
		return FALSE;

	return TRUE;
}


// Overrides
// ----------------


