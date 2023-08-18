#pragma once
#include "Structures.h"
#include "CitiesData.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsInformation

///<summary> ����������� ���� �� ����� � �������� ��������� ������</summary>
class CPersonInformation
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CPersonInformation();
	virtual ~CPersonInformation();


// Methods
// ----------------
public:
	///<summary> ������� ����� ���� ������ �� ������� �� ������</summary>
	///<returns> ����� ���������� �� ���� ������������ �� ������ </returns>
	PERSONS& GetPerson();
	///<summary> ������� ����� ���� ������ �� ������ �� ����������� ������ �� �����</summary>
	///<returns> ����� ���������� �� ������ �� ����������� �� ������</returns>
	CPhoneNumbersArray& GetPhoneNumbers();


// Overrides
// ----------------


// Members
// ----------------
private:
	///<summary> ���� ���������� �� ������� �� ������</summary>
	PERSONS m_recPerson;
	///<summary> ���� ���������� �� ����������� ������ �� ������</summary>
	CPhoneNumbersArray m_oPhoneNumbersArray;
};