#pragma once
#include "PersonsTable.h"
#include "PhoneNumbersTable.h"
#include "PersonsInformation.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsData

///<summary> Клас за данните от таблица PERSONS</summary>
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
	///<summary> Функция за избор на всички елементи от таблица PERSONS</summary>
	///<param name="oPersonsArray">Масив в който запазваме хората</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL SelectAllPeopleData(CPersonsArray& oPersonsArray);
	///<summary> Функция за избор на човек и телефонните му номера</summary>
	///<param name="lID"> ID по което ще изберем града</param>
	///<param name="recPerson"> Променлива където ще запишем човека и телефонните му номера</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL SelectPersonAndNumbersWithID(const long lID, CPersonInformation& recPerson);
	///<summary> Функция за обновяване на човек и телефонните му номера</summary>
	///<param name="recPerson"> Обект съдържащ данните за човека и телефонните му номера</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL UpdatePersonAndNumbers(CPersonInformation& recPerson);
	///<summary> Функция за добавяне на човек и телефонните му номера</summary>
	///<param name="recPerson"> Обект съдържащ данните за човека и телефонните му номера</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL InsertPersonAndNumbers(CPersonInformation& recPerson);
	///<summary> Функция за изтриване на човек и телефонните му номера</summary>
	///<param name="lID"> ID по което ще изтрием човека</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL DeletePersonAndNumbers(const long lID);

	///<summary> Функция за запълване на телефонните номера на човек</summary>
	///<param name="recPerson"> Обект съдържащ данните за човека и телефонните му номера</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL FillPersonNumbers(CPersonInformation& oPersonInformation);

	///<summary> Функция която сравнява 2 структури дали са идентични</summary>
	///<param name="recPhoneLeft"> Първия телефонен номер </param>
	///<param name="recPhoneRight"> Втория телефонен номер</param>
	///<returns> Връща TRUE ако са идентични и FALSE ако не са </returns>
	BOOL ArePhoneNumbersEqual(const PHONE_NUMBERS& recPhoneLeft, const PHONE_NUMBERS& recPhoneRight);

	///<summary> Функция която отваря сесия и транзакция</summary>
	///<param name="oSession"> Референция на сесия</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL StartCustomSessionAndTransaction(CSession& oSession);


// Overrides
// ----------------


// Members
// ----------------
};