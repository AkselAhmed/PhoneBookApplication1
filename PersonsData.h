#pragma once
#include "PersonsTable.h"
#include "PhoneNumbersTable.h"
#include "PersonsInformation.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsData

///<summary> ���� �� ������� �� ������� PERSONS</summary>
class CPersonsData
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CPersonsData();
	virtual ~CPersonsData();


// Methods
// ----------------
public:
	///<summary> ������� �� ����� �� ������ �������� �� ������� PERSONS</summary>
	///<param name="oPersonsArray">����� � ����� ��������� ������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL SelectAllPeopleData(CPersonsArray& oPersonsArray);
	///<summary> ������� �� ����� �� ����� � ����������� �� ������</summary>
	///<param name="lID"> ID �� ����� �� ������� �����</param>
	///<param name="recPerson"> ���������� ������ �� ������� ������ � ����������� �� ������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL SelectPersonAndNumbersWithID(const long lID, CPersonInformation& recPerson);
	///<summary> ������� �� ���������� �� ����� � ����������� �� ������</summary>
	///<param name="recPerson"> ����� �������� ������� �� ������ � ����������� �� ������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL UpdatePersonAndNumbers(CPersonInformation& recPerson);
	///<summary> ������� �� �������� �� ����� � ����������� �� ������</summary>
	///<param name="recPerson"> ����� �������� ������� �� ������ � ����������� �� ������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL InsertPersonAndNumbers(CPersonInformation& recPerson);
	///<summary> ������� �� ��������� �� ����� � ����������� �� ������</summary>
	///<param name="lID"> ID �� ����� �� ������� ������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL DeletePersonAndNumbers(const long lID);

	///<summary> ������� �� ��������� �� ����������� ������ �� �����</summary>
	///<param name="recPerson"> ����� �������� ������� �� ������ � ����������� �� ������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL FillPersonNumbers(CPersonInformation& oPersonInformation);

	///<summary> ������� ����� �������� 2 ��������� ���� �� ���������</summary>
	///<param name="recPhoneLeft"> ������ ��������� ����� </param>
	///<param name="recPhoneRight"> ������ ��������� �����</param>
	///<returns> ����� TRUE ��� �� ��������� � FALSE ��� �� �� </returns>
	BOOL ArePhoneNumbersEqual(const PHONE_NUMBERS& recPhoneLeft, const PHONE_NUMBERS& recPhoneRight);

	///<summary> ������� ����� ������ ����� � ����������</summary>
	///<param name="oSession"> ���������� �� �����</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL StartCustomSessionAndTransaction(CSession& oSession);


// Overrides
// ----------------


// Members
// ----------------
};