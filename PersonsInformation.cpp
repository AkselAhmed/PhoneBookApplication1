#include "pch.h"
#include "PersonsInformation.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsInformation

// Constructor / Destructor
// ----------------

CPersonInformation::CPersonInformation()
{
}

CPersonInformation::~CPersonInformation()
{
}


// Methods
// ----------------
PERSONS& CPersonInformation::GetPerson()
{
	return m_recPerson;
}

CPhoneNumbersArray& CPersonInformation::GetPhoneNumbers()
{
	return m_oPhoneNumbersArray;
}


// Overrides
// ----------------
