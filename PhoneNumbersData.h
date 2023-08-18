#pragma once
#include "PhoneNumbersTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersData

///<summary> Клас за данните от таблица PHONE_NUMBERS</summary>
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
	///<summary> Функция за избор на всички елементи от таблица PHONE_NUMBERS</summary>
	///<param name="oPhoneNumbersArray">Масив в който запазваме телефонните номера</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL SelectAllData(CPhoneNumbersArray& oPhoneNumbersArray);
	///<summary> Функция за избор на телефонен номер</summary>
	///<param name="lID"> ID по което ще изберем номера</param>
	///<param name="recPerson"> Променлива където ще запишем телефонния номер</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL SelectDataWithID(const long lID, PHONE_NUMBERS& recPhoneNumber);
	///<summary> Функция за обновяване на телефонен номер</summary>
	///<param name="recPhoneNumber"> Съдържа новия телефонен номер</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL UpdateData(PHONE_NUMBERS& recPhoneNumber);
	///<summary> Функция за добавяне на телефонен номер</summary>
	///<param name="recPhoneNumber"> Съдържа новия телефонен номер</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL InsertData(PHONE_NUMBERS& recPhoneNumber);
	///<summary> Функция за изтриване на телефонен номер</summary>
	///<param name="lID"> ИД на телефона който ще се изтрие</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL DeleteData(const long lID);


// Overrides
// ----------------


// Members
// ----------------
};