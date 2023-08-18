#include "pch.h"
#include "framework.h"

#ifndef SHARED_HANDLERS
#include "PhoneBook.h"
#endif

#include "PhoneNumbersData.h"
#include "CitiesData.h"
#include "PersonsDocument.h"
#include "PersonsData.h"
#include "PhoneTypesData.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CPersonsDocument


//Macros
// --------------
IMPLEMENT_DYNCREATE(CPersonsDocument, CDocument)

BEGIN_MESSAGE_MAP(CPersonsDocument, CDocument)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CPersonsDocument::CPersonsDocument()
{
}

CPersonsDocument::~CPersonsDocument()
{
}


// Methods
// ----------------

BOOL CPersonsDocument::PrepareDocumentData()
{
	CPersonsData oPersonsData;
	// Зареждаме всички хора от базата в масива m_oPersonsArray
	if (!oPersonsData.SelectAllPeopleData(m_oPersonsArray))
		return FALSE;

	CCitiesData oCitiesData;
	// Зареждаме всички градове от базата в масива m_oCitiesArray
	if (!oCitiesData.SelectAllCities(m_oCitiesArray))
		return FALSE;

	CPhoneTypesData oPhoneTypesData;
	// Зареждаме всички типове телефони от базата в масива m_oPhoneTypesArray
	if (!oPhoneTypesData.SelectAllData(m_oPhoneTypesArray))
		return FALSE;

	return TRUE;
}

BOOL CPersonsDocument::SelectAllPersons(CPersonsArray& oPersonsArray)
{
	CPersonsData oPersonsData;
	// Зареждаме всички хора от базата в масива oPersonsArray
	if (!oPersonsData.SelectAllPeopleData(oPersonsArray))
		return FALSE;

	return TRUE;
}

BOOL CPersonsDocument::SelectDataWithID(const long lID, CPersonInformation& oPersonInformation)
{
	CPersonsData oPersonData;

	// Избираме човека и телефонните му номера с даденото ID от базата данни
	if (!oPersonData.SelectPersonAndNumbersWithID(lID, oPersonInformation))
		return FALSE;

	return TRUE;
}

BOOL CPersonsDocument::UpdateData(CPersonInformation& recPersons)
{
	CPersonsData oPersonData;
	// Редактираме човека и телефонните му номера в базата данни
	if (!oPersonData.UpdatePersonAndNumbers(recPersons))
		return FALSE;

	// Създаваме обект указател от PERSONS
	PERSONS* pUpdatePerson = nullptr;

	// Изцикляме масива  за  да намерим човека , който искаме да редактираме
	for (INT_PTR nIndex = 0; nIndex < m_oPersonsArray.GetSize(); nIndex++)
	{
		pUpdatePerson = m_oPersonsArray.GetAt(nIndex);
		if (pUpdatePerson == nullptr)
			return FALSE;

		if (pUpdatePerson->lID == recPersons.GetPerson().lID)
		{
			// Записваме новия човек 
			*pUpdatePerson = recPersons.GetPerson();

			// Прекъсваме цикъла
			break;
		}
	}

	// Викаме UpdateAllViews на всички View-та 
	UpdateAllViews(NULL, OnUpdateHintUpdate, (CObject*)pUpdatePerson);

	return TRUE;
}

BOOL CPersonsDocument::InsertData(CPersonInformation& recPersons)
{
	CPersonsData oPersonData;

	// Добавяме човека и телефонните му номера в базата данни
	if (!oPersonData.InsertPersonAndNumbers(recPersons))
		return FALSE;

	// Заделяме памет за новия човек
	PERSONS* pNewPerson = new PERSONS();
	*pNewPerson = recPersons.GetPerson();

	// Добавяме човека в масива ни
	m_oPersonsArray.Add(pNewPerson);

	// Викаме UpdateAllViews на всички View-та
	UpdateAllViews(NULL, OnUpdateHintInsert, (CObject*)pNewPerson);

	return TRUE;
}

BOOL CPersonsDocument::DeleteData(const long lPersonID)
{
	CPersonsData oPersonData;

	// Изтриваме човека от базата данни
	if (!oPersonData.DeletePersonAndNumbers(lPersonID))
		return FALSE;

	PERSONS recDeletePerson;

	// Изцикляме  масива  за да намерим човека , който искаме да изтрием
	for (INT_PTR nIndex = 0; nIndex < m_oPersonsArray.GetSize(); nIndex++)
	{
		PERSONS* pPerson = m_oPersonsArray.GetAt(nIndex);
		if (pPerson == nullptr)
			return FALSE;

		if (pPerson->lID == lPersonID)
		{
			recDeletePerson = *pPerson;

			// Изтриваме човека от масива
			m_oPersonsArray.Delete(nIndex);

			// Прекъсваме цикъла
			break;
		}
	}

	// Викаме UpdateAllViews на всички View-та
	UpdateAllViews(NULL, OnUpdateHintDelete, (CObject*)&recDeletePerson);

	return TRUE;
}

const CPersonsArray& CPersonsDocument::GetDocArray() const
{
	return m_oPersonsArray;
}

const CCitiesArray& CPersonsDocument::GetDocCitiesArray() const
{
	return m_oCitiesArray;
}

const CPhoneTypesArray& CPersonsDocument::GetDocPhoneTypesArray() const
{
	return m_oPhoneTypesArray;
}


// Overrides
// ----------------

BOOL CPersonsDocument::OnNewDocument()
{
	if (!__super::OnNewDocument())
		return FALSE;

	// Зареждаме всички данни 
	if (!PrepareDocumentData())
		return FALSE;

	return TRUE;
}


