#include "pch.h"
#include "PhoneTypesTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesTable


// Constructor / Destructor
// ----------------

CPhoneTypesTable::CPhoneTypesTable()
{
}
CPhoneTypesTable::~CPhoneTypesTable()
{
}


// Methods
// ----------------


// Overrides
// ----------------
CString CPhoneTypesTable::GetTableName()
{
	return _T("PHONE_TYPES");
}

long& CPhoneTypesTable::GetRecordUpdateCounter(PHONE_TYPES& recPhoneType)
{
	return recPhoneType.lUpdateCounter;
}
