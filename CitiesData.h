#pragma once
#include "CitiesTable.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesData

///<summary> ���� �� ������� �� ������� CITIES</summary>
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
	///<summary> ������� �� ����� �� ������ �������� �� ������� CITIES</summary>
	///<param name="oCitiesArray">����� � ����� ��������� ���������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL SelectAllCities(CCitiesArray& oCitiesArray);
	///<summary> ������� �� ����� �� ���� �� ID �� ������� CITIES</summary>
	///<param name="lID"> ID �� ����� �� ������� �����</param>
	///<param name="recCity"> ��� �� ������� �������� ����(������������ � �a�����)</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL SelectCityWithID(const long lID, CITIES& recCity);
	///<summary> ������� �� ���������� �� ���� �� ������� CITIES</summary>
	///<param name="recCity"> ����� ���� , � ����� �� �� ������� ���������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL UpdateCity(CITIES& recCity);
	///<summary> ������� �� �������� �� ���� � ������� CITIES</summary>
	///<param name="recCity"> ����� ����� �� �������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL InsertCity(CITIES& recCity);
	///<summary> ������� �� ��������� �� ���� �� ������� CITIES �� ID</summary>
	///<param name="lID"> ID �� ����� �� ������� ����</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL DeleteCity(const long lID);

	
// Overrides
// ----------------


// Members
// ----------------
};