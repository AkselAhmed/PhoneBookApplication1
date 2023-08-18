#include "pch.h"
#include "CitiesTable.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesTable


// Constructor / Destructor
// ----------------

CCitiesTable::CCitiesTable()
{
}
CCitiesTable::~CCitiesTable()
{
}


// Methods
// ----------------


// Overrides
// ----------------

CString CCitiesTable::GetTableName()
{
	return _T("CITIES");
}

long & CCitiesTable::GetRecordUpdateCounter(CITIES& recCity)
{
	return recCity.lUpdateCounter;
}
