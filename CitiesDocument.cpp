#include "pch.h"
#include "framework.h"

#ifndef SHARED_HANDLERS
#include "PhoneBook.h"
#endif

#include "CitiesDocument.h"
#include "CitiesData.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CCitiesDocument


//Macros
// --------------
IMPLEMENT_DYNCREATE(CCitiesDocument, CDocument)

BEGIN_MESSAGE_MAP(CCitiesDocument, CDocument)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CCitiesDocument::CCitiesDocument()
{
}

CCitiesDocument::~CCitiesDocument()
{
}


// Methods
// ----------------

BOOL CCitiesDocument::PrepareDocumentData()
{
	CCitiesData oCitiesData;

	// Зареждаме всички данни от базата в масива m_oCitiesArray
	if (!oCitiesData.SelectAllCities(m_oCitiesArray))
		return FALSE;

	return TRUE;
}

BOOL CCitiesDocument::SelectDataWithID(const long lID, CITIES& recCity)
{
	CCitiesData oCitiesData;

	// Избираме града с даденото ID от базата данни
	if (!oCitiesData.SelectCityWithID(lID, recCity))
		return FALSE;

	return TRUE;
}

BOOL CCitiesDocument::UpdateData(CITIES& recCity)
{
	CCitiesData oCitiesData;

	// Редактираме града в базата данни
	if (!oCitiesData.UpdateCity(recCity))
		return FALSE;

	// Изцикляме масива  за  да намерим града , който искаме да редактираме
	for (INT_PTR nIndex = 0; nIndex < m_oCitiesArray.GetSize(); nIndex++)
	{
		CITIES* pUpdateCity = m_oCitiesArray.GetAt(nIndex);
		if (pUpdateCity == nullptr)
			return FALSE;

		if (pUpdateCity->lID == recCity.lID)
		{
			// Записваме новия град в масива
			*pUpdateCity = recCity;

			// Прекъсваме цикъла
			break;
		}
	}
	
	// Викаме UpdateAllViews на всички View-та с подсказка за редакция и CObject каст-нат редактирания град
	UpdateAllViews(NULL, OnUpdateHintUpdate, (CObject*)&recCity);

	return TRUE;
}

BOOL CCitiesDocument::InsertData(CITIES& recCity)
{
	CCitiesData oCitiesData;

	// Добавяме града в базата данни
	if (!oCitiesData.InsertCity(recCity))
		return FALSE;

	// Заделяме памет за нов град и го присвояваме
	CITIES* pNewCity = new CITIES();
	*pNewCity = recCity;

	// Добавяме града в масива ни
	m_oCitiesArray.Add(pNewCity);

	// Викаме UpdateAllViews на всички View-та с подсказка за вмъкване и CObject каст-нат вмъкнатия град
	UpdateAllViews(NULL, OnUpdateHintInsert, (CObject*)pNewCity);

	return TRUE;
}

BOOL CCitiesDocument::DeleteData(const long lID)
{
	CCitiesData oCitiesData;

	// Изтриваме града от базата данни
	if (!oCitiesData.DeleteCity(lID))
		return FALSE;

	CITIES recDeleteCity;

	// Изцикляме  масива  за да намерим града , който искаме да изтрием
	for (INT_PTR nIndex = 0; nIndex < m_oCitiesArray.GetSize(); nIndex++)
	{
		CITIES* pCity= m_oCitiesArray.GetAt(nIndex);
		if (pCity == nullptr)
			return FALSE;

		if (pCity->lID == lID)
		{
			recDeleteCity = *pCity;

			// Изтриваме града от масива
			m_oCitiesArray.Delete(nIndex);

			// Прекъсваме цикъла
			break;
		}
	}

	// Викаме UpdateAllViews на всички View-та с подсказка за изтриване и CObject каст-нат изтрития град
	UpdateAllViews(NULL, OnUpdateHintDelete, (CObject*)&recDeleteCity);

	return TRUE;
}

const CCitiesArray& CCitiesDocument::GetCitiesArray() const
{
	return m_oCitiesArray;
}


// Overrides
// ----------------

BOOL CCitiesDocument::OnNewDocument()
{
	if (!__super::OnNewDocument())
		return FALSE;

	// Зареждаме всички данни
	if (!PrepareDocumentData())
		return FALSE;

	return TRUE;
}