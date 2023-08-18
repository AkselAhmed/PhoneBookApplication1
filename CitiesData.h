#pragma once
#include "CitiesTable.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesData

///<summary> Клас за данните от таблица CITIES</summary>
class CCitiesData 
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CCitiesData();
	virtual ~CCitiesData();


// Methods
// ----------------
public:
	///<summary> Функция за избор на всички елементи от таблица CITIES</summary>
	///<param name="oCitiesArray">Масив в който запазваме градовете</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL SelectAllCities(CCitiesArray& oCitiesArray);
	///<summary> Функция за избор на град по ID от таблица CITIES</summary>
	///<param name="lID"> ID по което ще изберем града</param>
	///<param name="recCity"> Тук ще запазим избрания град(първоначално е зaнулен)</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL SelectCityWithID(const long lID, CITIES& recCity);
	///<summary> Функция за обновяване на град от таблица CITIES</summary>
	///<param name="recCity"> Новия град , с който ще се промени таблицата</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL UpdateCity(CITIES& recCity);
	///<summary> Функция за добавяне на град в таблица CITIES</summary>
	///<param name="recCity"> Града който ще вмъкнем</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL InsertCity(CITIES& recCity);
	///<summary> Функция за изтриване на град от таблица CITIES по ID</summary>
	///<param name="lID"> ID по което ще изтрием град</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL DeleteCity(const long lID);

	
// Overrides
// ----------------


// Members
// ----------------
};