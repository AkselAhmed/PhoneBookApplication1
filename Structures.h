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

///<summary> ��������� �� ������� CITIES </summary>
struct CITIES
{
	/// <summary>���� ���������� �� ID</summary>
	long lID;

	/// <summary>���� ���������� �� UpdateCounter</summary>
	long lUpdateCounter;
	/// <summary>���� ���������� �� ����� �� �����</summary>
	TCHAR szCityName[CITY_NAME_LENGTH + 1];

	/// <summary>���� ���������� �� ��������</summary>
	TCHAR szDistrict[DISTRICT_LENGTH + 1];

	/// <summary> ����������� �� ����������� ����� �������� ���� ������������</summary>
	CITIES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};
/// <summary> ����� �� ��������� , ��������� ����������� ������� ��</summary>
typedef CAutoFreeMemoryArray<CITIES*> CCitiesArray;

///<summary> ��������� �� ������� PHONE_TYPES </summary>
struct PHONE_TYPES
{
	/// <summary>���� ���������� �� ID</summary>
	long lID;
	/// <summary>���� ���������� �� UpdateCounter</summary>
	long lUpdateCounter;
	/// <summary>���� ���������� �� ��� �������</summary>
	TCHAR szType[TYPE_LENGTH + 1];

	/// <summary> ����������� �� ����������� ����� �������� ���� ������������</summary>
	PHONE_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};
/// <summary> ����� �� �������� ��������, ��������� ����������� ������� ��</summary>
typedef CAutoFreeMemoryArray<PHONE_TYPES*> CPhoneTypesArray;

///<summary> ��������� �� ������� PERSONS </summary>
struct PERSONS
{
	/// <summary>���� ���������� �� ID</summary>
	long lID;
	/// <summary>���� ���������� �� UpdateCounter</summary>
	long lUpdateCounter;
	/// <summary>���� ���������� �� ������� ���</summary>
	TCHAR szFirstName[FIRST_NAME_LENGTH + 1];

	/// <summary>���� ���������� �� ������� ���</summary>
	TCHAR szSecondName[SECOND_NAME_LENGTH + 1];

	/// <summary>���� ���������� �� ������� ���</summary>
	TCHAR szThirdName[THIRD_NAME_LENGTH + 1];

	/// <summary>���� ���������� �� ���</summary>
	TCHAR szEgn[EGN_LENGTH];

	/// <summary>���� ���������� �� ID �� ������� CITIES</summary>
	long lCityID;
	/// <summary>���� ���������� �� �����</summary>
	TCHAR szAddress[ADDRESS_LENGTH + 1];

	/// <summary> ����������� �� ����������� ����� �������� ���� ������������</summary>
	PERSONS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};
/// <summary> ����� �� ������, ��������� ����������� ������� ��</summary>
typedef CAutoFreeMemoryArray<PERSONS*> CPersonsArray;

///<summary> ��������� �� ������� PHONE_NUMBERS </summary>
struct PHONE_NUMBERS
{
	/// <summary>���� ���������� �� ID</summary>
	long lID;
	/// <summary>���� ���������� �� UpdateCounter</summary>
	long lUpdateCounter;
	/// <summary>���� ���������� �� ID �� ������� PERSONS</summary>
	long lPersonID;
	/// <summary>���� ���������� �� ID �� ������� PHONE_TYPES</summary>
	long lPhoneTypeID;
	/// <summary>���� ���������� �� ��������� �����</summary>
	TCHAR szPhone[PHONE_LENGTH + 1];

	/// <summary> ����������� �� ����������� ����� �������� ���� ������������</summary>
	PHONE_NUMBERS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};
/// <summary> ����� �� ����������� ������, ��������� ����������� ������� ��</summary>
typedef CAutoFreeMemoryArray<PHONE_NUMBERS*> CPhoneNumbersArray;