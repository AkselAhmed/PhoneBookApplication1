#include "pch.h"
#include "PhoneNumbersTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersTable


// Constructor / Destructor
// ----------------

CPhoneNumbersTable::CPhoneNumbersTable(CSession* pSession) : CBaseTable(pSession)
{
}
CPhoneNumbersTable::~CPhoneNumbersTable()
{
}


// Methods
// ----------------


// Overrides
// ----------------
CString CPhoneNumbersTable::GetTableName()
{
	return _T("PHONE_NUMBERS");
}

long& CPhoneNumbersTable::GetRecordUpdateCounter(PHONE_NUMBERS& recPhoneNumber)
{
	return recPhoneNumber.lUpdateCounter;
}
