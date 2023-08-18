#include "pch.h"
#include "PersonsTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsTable


// Constructor / Destructor
// ----------------
CPersonsTable::CPersonsTable(CSession* pSession) : CBaseTable(pSession)
{
}
CPersonsTable::~CPersonsTable()
{
}


// Methods
// ----------------


// Overrides
// ----------------
CString CPersonsTable::GetTableName()
{
	return _T("PERSONS");
}

long& CPersonsTable::GetRecordUpdateCounter(PERSONS& recPerson)
{
	return recPerson.lUpdateCounter;
}
