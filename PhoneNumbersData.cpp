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

	// ��������� ������ ��������� ������ �� ������ ����� � ������ oPhoneNumbersArray
	if (!oPhoneNumbersTable.SelectAll(oPhoneNumbersArray))
		return FALSE;

	return TRUE;
}

BOOL CPhoneNumbersData::SelectDataWithID(const long lID, PHONE_NUMBERS& recPhoneNumber)
{
	CPhoneNumbersTable oPhoneNumbersTable;

	// �������� ���������� ����� �� ������ ����� � �� = lID � �� ����������� �� recPhoneNumber
	if (!oPhoneNumbersTable.SelectWhereID(lID, recPhoneNumber))
		return FALSE;

	return TRUE;
}

BOOL CPhoneNumbersData::UpdateData(PHONE_NUMBERS& recPhoneNumber)
{
	CPhoneNumbersTable oPhoneNumbersTable;

	// ����������� ���������� ����� �� ������ ����� � ����� recPhoneNumber
	if (!oPhoneNumbersTable.UpdateWhereID(recPhoneNumber))
		return FALSE;

	return TRUE;
}

BOOL CPhoneNumbersData::InsertData(PHONE_NUMBERS& recPhoneNumber)
{
	CPhoneNumbersTable oPhoneNumbersTable;

	// �������� ��� ��������� ����� � ������ �����
	if (!oPhoneNumbersTable.Insert(recPhoneNumber))
		return FALSE;

	return TRUE;
}

BOOL CPhoneNumbersData::DeleteData(const long lID)
{
	CPhoneNumbersTable oPhoneNumbersTable;

	// ��������� ��������� ����� �� ������ �����
	if (!oPhoneNumbersTable.DeleteWhereID(lID))
		return FALSE;

	return TRUE;
}


// Overrides
// ----------------


