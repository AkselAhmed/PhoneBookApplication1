#include "pch.h"
#include "CitiesData.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesData

// Constructor / Destructor
// ----------------
CCitiesData::CCitiesData()
{
}

CCitiesData::~CCitiesData()
{
}


// Methods
// ----------------
BOOL CCitiesData::SelectAllCities(CCitiesArray& oCitiesArray)
{
	CCitiesTable oCityTable;

	// ��������� ����� �� ��������� � �� ��������� � oCitiesArray
	if (!oCityTable.SelectAll(oCitiesArray))
		return FALSE;

	return TRUE;
}

BOOL CCitiesData::SelectCityWithID(const long lID, CITIES& recCity)
{
	CCitiesTable oCityTable;

	// ��������� ����� �� ����� � �� ��������� � recCity
	if (!oCityTable.SelectWhereID(lID,recCity))
		return FALSE;

	return TRUE;
}

BOOL CCitiesData::UpdateCity(CITIES& recCity)
{
	CCitiesTable oCityTable;

	// ���������� ������� � ���� �� recCity
	if (!oCityTable.UpdateWhereID(recCity))
		return FALSE;

	return TRUE;
}

BOOL CCitiesData::InsertCity(CITIES& recCity)
{
	CCitiesTable oCityTable;

	// �������� ��� ���� recCity
	if (!oCityTable.Insert(recCity))
		return FALSE;

	return TRUE;
}

BOOL CCitiesData::DeleteCity(const long lID)
{
	CCitiesTable oCityTable;

	// ��������� ���� �� ID(lID)
	if (!oCityTable.DeleteWhereID(lID))
		return FALSE;

	return TRUE;
}


// Overrides
// ----------------