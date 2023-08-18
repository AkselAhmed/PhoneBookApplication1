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
	// ��������� ������ ���� �� ������ � ������ m_oPersonsArray
	if (!oPersonsData.SelectAllPeopleData(m_oPersonsArray))
		return FALSE;

	CCitiesData oCitiesData;
	// ��������� ������ ������� �� ������ � ������ m_oCitiesArray
	if (!oCitiesData.SelectAllCities(m_oCitiesArray))
		return FALSE;

	CPhoneTypesData oPhoneTypesData;
	// ��������� ������ ������ �������� �� ������ � ������ m_oPhoneTypesArray
	if (!oPhoneTypesData.SelectAllData(m_oPhoneTypesArray))
		return FALSE;

	return TRUE;
}

BOOL CPersonsDocument::SelectAllPersons(CPersonsArray& oPersonsArray)
{
	CPersonsData oPersonsData;
	// ��������� ������ ���� �� ������ � ������ oPersonsArray
	if (!oPersonsData.SelectAllPeopleData(oPersonsArray))
		return FALSE;

	return TRUE;
}

BOOL CPersonsDocument::SelectDataWithID(const long lID, CPersonInformation& oPersonInformation)
{
	CPersonsData oPersonData;

	// �������� ������ � ����������� �� ������ � �������� ID �� ������ �����
	if (!oPersonData.SelectPersonAndNumbersWithID(lID, oPersonInformation))
		return FALSE;

	return TRUE;
}

BOOL CPersonsDocument::UpdateData(CPersonInformation& recPersons)
{
	CPersonsData oPersonData;
	// ����������� ������ � ����������� �� ������ � ������ �����
	if (!oPersonData.UpdatePersonAndNumbers(recPersons))
		return FALSE;

	// ��������� ����� �������� �� PERSONS
	PERSONS* pUpdatePerson = nullptr;

	// ��������� ������  ��  �� ������� ������ , ����� ������ �� �����������
	for (INT_PTR nIndex = 0; nIndex < m_oPersonsArray.GetSize(); nIndex++)
	{
		pUpdatePerson = m_oPersonsArray.GetAt(nIndex);
		if (pUpdatePerson == nullptr)
			return FALSE;

		if (pUpdatePerson->lID == recPersons.GetPerson().lID)
		{
			// ��������� ����� ����� 
			*pUpdatePerson = recPersons.GetPerson();

			// ���������� ������
			break;
		}
	}

	// ������ UpdateAllViews �� ������ View-�� 
	UpdateAllViews(NULL, OnUpdateHintUpdate, (CObject*)pUpdatePerson);

	return TRUE;
}

BOOL CPersonsDocument::InsertData(CPersonInformation& recPersons)
{
	CPersonsData oPersonData;

	// �������� ������ � ����������� �� ������ � ������ �����
	if (!oPersonData.InsertPersonAndNumbers(recPersons))
		return FALSE;

	// �������� ����� �� ����� �����
	PERSONS* pNewPerson = new PERSONS();
	*pNewPerson = recPersons.GetPerson();

	// �������� ������ � ������ ��
	m_oPersonsArray.Add(pNewPerson);

	// ������ UpdateAllViews �� ������ View-��
	UpdateAllViews(NULL, OnUpdateHintInsert, (CObject*)pNewPerson);

	return TRUE;
}

BOOL CPersonsDocument::DeleteData(const long lPersonID)
{
	CPersonsData oPersonData;

	// ��������� ������ �� ������ �����
	if (!oPersonData.DeletePersonAndNumbers(lPersonID))
		return FALSE;

	PERSONS recDeletePerson;

	// ���������  ������  �� �� ������� ������ , ����� ������ �� �������
	for (INT_PTR nIndex = 0; nIndex < m_oPersonsArray.GetSize(); nIndex++)
	{
		PERSONS* pPerson = m_oPersonsArray.GetAt(nIndex);
		if (pPerson == nullptr)
			return FALSE;

		if (pPerson->lID == lPersonID)
		{
			recDeletePerson = *pPerson;

			// ��������� ������ �� ������
			m_oPersonsArray.Delete(nIndex);

			// ���������� ������
			break;
		}
	}

	// ������ UpdateAllViews �� ������ View-��
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

	// ��������� ������ ����� 
	if (!PrepareDocumentData())
		return FALSE;

	return TRUE;
}


