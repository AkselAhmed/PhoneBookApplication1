#pragma once
#include "PhoneTypesTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesData

///<summary> Клас за данните от таблица PHONE_TYPES</summary>
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
	///<summary> Функция за избор на всички типове телефони</summary>
	///<param name="oPhoneTypesArray"> Масива в който ще запазим телефонните типове</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL SelectAllData(CPhoneTypesArray& oPhoneTypesArray);
	///<summary> Функция за избор на телефонен тип от базата</summary>
	///<param name="recPhoneType"> Запазваме избрания телефонен тип</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL SelectDataWithID(const long lID, PHONE_TYPES& recPhoneType);
	///<summary> Функция за редакция на телефонен тип от базата</summary>
	///<param name="recPhoneType"> Новия телефонен тип с който ще редактираме</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL UpdateData(PHONE_TYPES& recPhoneType);
	///<summary> Функция за добавяне на телефонен тип от базата</summary>
	///<param name="recPhoneType"> Новия телефонен тип</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL InsertData(PHONE_TYPES& recPhoneType);
	///<summary> Функция за изтриване на телефонен тип от базата</summary>
	///<param name="lID"> ИД на телефонен тип който ще изтрием</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL DeleteData(const long lID);


// Overrides
// ----------------


// Members
// ----------------
};