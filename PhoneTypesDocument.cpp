#include "pch.h"
#include "framework.h"

#ifndef SHARED_HANDLERS
#include "PhoneBook.h"
#endif

#include "PhoneTypesDocument.h"
#include "PhoneTypesData.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDocument


//Macros
// --------------
IMPLEMENT_DYNCREATE(CPhoneTypesDocument, CDocument)

BEGIN_MESSAGE_MAP(CPhoneTypesDocument, CDocument)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CPhoneTypesDocument::CPhoneTypesDocument()
{
}

CPhoneTypesDocument::~CPhoneTypesDocument()
{
}


// Methods
// ----------------

BOOL CPhoneTypesDocument::PrepareDocumentData()
{
	CPhoneTypesData oPhoneTypesData;

	// Зареждаме всички телефонни типове от базата в масива m_oPhoneTypesArray
	if (!oPhoneTypesData.SelectAllData(m_oPhoneTypesArray))
		return FALSE;

	return TRUE;
}

BOOL CPhoneTypesDocument::SelectDataWithID(const long lID, PHONE_TYPES& recPhoneType)
{
	CPhoneTypesData oPhoneTypesData;

	// Избираме телефонния тип с даденото ID от базата данни
	if (!oPhoneTypesData.SelectDataWithID(lID, recPhoneType))
		return FALSE;

	return TRUE;
}

BOOL CPhoneTypesDocument::UpdateData(PHONE_TYPES& recPhoneType)
{
	CPhoneTypesData oPhoneTypesData;

	// Редактираме телефонния тип в базата данни
	if (!oPhoneTypesData.UpdateData(recPhoneType))
		return FALSE;

	PHONE_TYPES* pUpdateType = nullptr;

	// Изцикляме масива  за  да намерим телефонния тип , който искаме да редактираме
	for (INT_PTR nIndex = 0; nIndex < m_oPhoneTypesArray.GetSize(); nIndex++)
	{
		pUpdateType = m_oPhoneTypesArray.GetAt(nIndex);
		if (pUpdateType == nullptr)
			return FALSE;

		if (pUpdateType->lID == recPhoneType.lID)
		{
			// Записваме променения телефонен тип  в масива
			*pUpdateType = recPhoneType;

			break;
		}
	}

	// Викаме UpdateAllViews на всички View-та 
	UpdateAllViews(NULL, OnUpdateHintUpdate, (CObject*)pUpdateType);

	return TRUE;
}

BOOL CPhoneTypesDocument::InsertData(PHONE_TYPES& recPhoneType)
{
	CPhoneTypesData oPhoneTypesData;

	// Добавяме телефонния тип в базата данни
	if (!oPhoneTypesData.InsertData(recPhoneType))
		return FALSE;

	PHONE_TYPES* pNewPhoneType = new PHONE_TYPES(recPhoneType);

	// Добавяме телефонния тип в масива ни
	m_oPhoneTypesArray.Add(pNewPhoneType);

	// Викаме UpdateAllViews на всички View-та
	UpdateAllViews(NULL, OnUpdateHintInsert, (CObject*)pNewPhoneType);

	return TRUE;
}

BOOL CPhoneTypesDocument::DeleteData(const long lID)
{
	CPhoneTypesData oPhoneTypesData;

	// Изтриваме телефонния тип от базата данни
	if (!oPhoneTypesData.DeleteData(lID))
		return FALSE;

	PHONE_TYPES recPhoneType;

	// Изцикляме  масива  за да намерим телефонния тип , който искаме да изтрием
	for (INT_PTR nIndex = 0; nIndex < m_oPhoneTypesArray.GetSize(); nIndex++)
	{
		PHONE_TYPES* pPhoneType = m_oPhoneTypesArray.GetAt(nIndex);
		if (pPhoneType == nullptr)
			return FALSE;

		if (pPhoneType->lID == lID)
		{
			recPhoneType = *pPhoneType;

			m_oPhoneTypesArray.Delete(nIndex);

			// Прекъсваме цикъла
			break;
		}
	}

	// Викаме UpdateAllViews на всички View-та
	LPARAM lHint = OnUpdateHintDelete;
	UpdateAllViews(NULL, lHint, (CObject*)&recPhoneType);

	return TRUE;
}

const CPhoneTypesArray& CPhoneTypesDocument::GetDocArray() const
{
	return m_oPhoneTypesArray;
}


// Overrides
// ----------------

BOOL CPhoneTypesDocument::OnNewDocument()
{
	if (!__super::OnNewDocument())
		return FALSE;

	// Зареждаме всички данни 
	if (!PrepareDocumentData())
		return FALSE;

	return TRUE;
}