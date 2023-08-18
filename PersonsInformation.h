#pragma once
#include "Structures.h"
#include "CitiesData.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsInformation

///<summary> Транспортен клас за човек и неговите телефонни номера</summary>
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
	///<summary> Функция която дава достъп до данните за човека</summary>
	///<returns> Връща референция на член променливата за човека </returns>
	PERSONS& GetPerson();
	///<summary> Функция която дава достъп до масива за телефонните номера на човек</summary>
	///<returns> Връща референция на масива за телефонните му номера</returns>
	CPhoneNumbersArray& GetPhoneNumbers();


// Overrides
// ----------------


// Members
// ----------------
private:
	///<summary> Член променлива за данните на човека</summary>
	PERSONS m_recPerson;
	///<summary> Член променлива за телефонните номера на човека</summary>
	CPhoneNumbersArray m_oPhoneNumbersArray;
};