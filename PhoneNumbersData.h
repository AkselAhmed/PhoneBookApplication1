#pragma once
#include "PhoneNumbersTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersData

///<summary> ���� �� ������� �� ������� PHONE_NUMBERS</summary>
class CPhoneNumbersData
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CPhoneNumbersData();
	virtual ~CPhoneNumbersData();


// Methods
// ----------------
public:
	///<summary> ������� �� ����� �� ������ �������� �� ������� PHONE_NUMBERS</summary>
	///<param name="oPhoneNumbersArray">����� � ����� ��������� ����������� ������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL SelectAllData(CPhoneNumbersArray& oPhoneNumbersArray);
	///<summary> ������� �� ����� �� ��������� �����</summary>
	///<param name="lID"> ID �� ����� �� ������� ������</param>
	///<param name="recPerson"> ���������� ������ �� ������� ���������� �����</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL SelectDataWithID(const long lID, PHONE_NUMBERS& recPhoneNumber);
	///<summary> ������� �� ���������� �� ��������� �����</summary>
	///<param name="recPhoneNumber"> ������� ����� ��������� �����</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL UpdateData(PHONE_NUMBERS& recPhoneNumber);
	///<summary> ������� �� �������� �� ��������� �����</summary>
	///<param name="recPhoneNumber"> ������� ����� ��������� �����</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL InsertData(PHONE_NUMBERS& recPhoneNumber);
	///<summary> ������� �� ��������� �� ��������� �����</summary>
	///<param name="lID"> �� �� �������� ����� �� �� ������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL DeleteData(const long lID);


// Overrides
// ----------------


// Members
// ----------------
};