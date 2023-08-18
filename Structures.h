#pragma once
#include "pch.h"
#include "framework.h"
#include "AutoFreeMemoryArray.h"

#define CITY_NAME_LENGTH 32
#define DISTRICT_LENGTH 32 
#define TYPE_LENGTH 32
#define FIRST_NAME_LENGTH 32
#define SECOND_NAME_LENGTH 32
#define THIRD_NAME_LENGTH 32
#define EGN_LENGTH 16
#define ADDRESS_LENGTH 256
#define PHONE_LENGTH 16

///<summary> Структура за таблица CITIES </summary>
struct CITIES
{
	/// <summary>Член променлива за ID</summary>
	long lID;

	/// <summary>Член променлива за UpdateCounter</summary>
	long lUpdateCounter;
	/// <summary>Член променлива за името на града</summary>
	TCHAR szCityName[CITY_NAME_LENGTH + 1];

	/// <summary>Член променлива за областта</summary>
	TCHAR szDistrict[DISTRICT_LENGTH + 1];

	/// <summary> Подразбиращ се конструктор който занулява член променливите</summary>
	CITIES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};
/// <summary> Масив за градовете , зачистващ автоматично паметта си</summary>
typedef CAutoFreeMemoryArray<CITIES*> CCitiesArray;

///<summary> Структура за таблица PHONE_TYPES </summary>
struct PHONE_TYPES
{
	/// <summary>Член променлива за ID</summary>
	long lID;
	/// <summary>Член променлива за UpdateCounter</summary>
	long lUpdateCounter;
	/// <summary>Член променлива за тип телефон</summary>
	TCHAR szType[TYPE_LENGTH + 1];

	/// <summary> Подразбиращ се конструктор който занулява член променливите</summary>
	PHONE_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};
/// <summary> Масив за типовете телефони, зачистващ автоматично паметта си</summary>
typedef CAutoFreeMemoryArray<PHONE_TYPES*> CPhoneTypesArray;

///<summary> Структура за таблица PERSONS </summary>
struct PERSONS
{
	/// <summary>Член променлива за ID</summary>
	long lID;
	/// <summary>Член променлива за UpdateCounter</summary>
	long lUpdateCounter;
	/// <summary>Член променлива за първото име</summary>
	TCHAR szFirstName[FIRST_NAME_LENGTH + 1];

	/// <summary>Член променлива за второто име</summary>
	TCHAR szSecondName[SECOND_NAME_LENGTH + 1];

	/// <summary>Член променлива за третото име</summary>
	TCHAR szThirdName[THIRD_NAME_LENGTH + 1];

	/// <summary>Член променлива за ЕГН</summary>
	TCHAR szEgn[EGN_LENGTH];

	/// <summary>Член променлива за ID от таблица CITIES</summary>
	long lCityID;
	/// <summary>Член променлива за адрес</summary>
	TCHAR szAddress[ADDRESS_LENGTH + 1];

	/// <summary> Подразбиращ се конструктор който занулява член променливите</summary>
	PERSONS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};
/// <summary> Масив за хората, зачистващ автоматично паметта си</summary>
typedef CAutoFreeMemoryArray<PERSONS*> CPersonsArray;

///<summary> Структура за таблица PHONE_NUMBERS </summary>
struct PHONE_NUMBERS
{
	/// <summary>Член променлива за ID</summary>
	long lID;
	/// <summary>Член променлива за UpdateCounter</summary>
	long lUpdateCounter;
	/// <summary>Член променлива за ID от таблица PERSONS</summary>
	long lPersonID;
	/// <summary>Член променлива за ID от таблица PHONE_TYPES</summary>
	long lPhoneTypeID;
	/// <summary>Член променлива за телефонен номер</summary>
	TCHAR szPhone[PHONE_LENGTH + 1];

	/// <summary> Подразбиращ се конструктор който занулява член променливите</summary>
	PHONE_NUMBERS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};
/// <summary> Масив за телефонните номера, зачистващ автоматично паметта си</summary>
typedef CAutoFreeMemoryArray<PHONE_NUMBERS*> CPhoneNumbersArray;