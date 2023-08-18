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

	// Зареждаме данни за градовете и ги записваме в oCitiesArray
	if (!oCityTable.SelectAll(oCitiesArray))
		return FALSE;

	return TRUE;
}

BOOL CCitiesData::SelectCityWithID(const long lID, CITIES& recCity)
{
	CCitiesTable oCityTable;

	// Зареждаме данни за града и ги записваме в recCity
	if (!oCityTable.SelectWhereID(lID,recCity))
		return FALSE;

	return TRUE;
}

BOOL CCitiesData::UpdateCity(CITIES& recCity)
{
	CCitiesTable oCityTable;

	// Обновяваме данните с тези на recCity
	if (!oCityTable.UpdateWhereID(recCity))
		return FALSE;

	return TRUE;
}

BOOL CCitiesData::InsertCity(CITIES& recCity)
{
	CCitiesTable oCityTable;

	// Вмъкваме нов град recCity
	if (!oCityTable.Insert(recCity))
		return FALSE;

	return TRUE;
}

BOOL CCitiesData::DeleteCity(const long lID)
{
	CCitiesTable oCityTable;

	// Изтриваме град по ID(lID)
	if (!oCityTable.DeleteWhereID(lID))
		return FALSE;

	return TRUE;
}


// Overrides
// ----------------