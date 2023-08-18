#pragma once
#include "PhoneTypesTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesData

///<summary> ���� �� ������� �� ������� PHONE_TYPES</summary>
class CPhoneTypesData
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CPhoneTypesData();
	virtual ~CPhoneTypesData();


// Methods
// ----------------
public:
	///<summary> ������� �� ����� �� ������ ������ ��������</summary>
	///<param name="oPhoneTypesArray"> ������ � ����� �� ������� ����������� ������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL SelectAllData(CPhoneTypesArray& oPhoneTypesArray);
	///<summary> ������� �� ����� �� ��������� ��� �� ������</summary>
	///<param name="recPhoneType"> ��������� �������� ��������� ���</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL SelectDataWithID(const long lID, PHONE_TYPES& recPhoneType);
	///<summary> ������� �� �������� �� ��������� ��� �� ������</summary>
	///<param name="recPhoneType"> ����� ��������� ��� � ����� �� �����������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL UpdateData(PHONE_TYPES& recPhoneType);
	///<summary> ������� �� �������� �� ��������� ��� �� ������</summary>
	///<param name="recPhoneType"> ����� ��������� ���</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL InsertData(PHONE_TYPES& recPhoneType);
	///<summary> ������� �� ��������� �� ��������� ��� �� ������</summary>
	///<param name="lID"> �� �� ��������� ��� ����� �� �������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL DeleteData(const long lID);


// Overrides
// ----------------


// Members
// ----------------
};