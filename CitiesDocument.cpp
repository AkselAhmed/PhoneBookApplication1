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

	// ��������� ������ ����� �� ������ � ������ m_oCitiesArray
	if (!oCitiesData.SelectAllCities(m_oCitiesArray))
		return FALSE;

	return TRUE;
}

BOOL CCitiesDocument::SelectDataWithID(const long lID, CITIES& recCity)
{
	CCitiesData oCitiesData;

	// �������� ����� � �������� ID �� ������ �����
	if (!oCitiesData.SelectCityWithID(lID, recCity))
		return FALSE;

	return TRUE;
}

BOOL CCitiesDocument::UpdateData(CITIES& recCity)
{
	CCitiesData oCitiesData;

	// ����������� ����� � ������ �����
	if (!oCitiesData.UpdateCity(recCity))
		return FALSE;

	// ��������� ������  ��  �� ������� ����� , ����� ������ �� �����������
	for (INT_PTR nIndex = 0; nIndex < m_oCitiesArray.GetSize(); nIndex++)
	{
		CITIES* pUpdateCity = m_oCitiesArray.GetAt(nIndex);
		if (pUpdateCity == nullptr)
			return FALSE;

		if (pUpdateCity->lID == recCity.lID)
		{
			// ��������� ����� ���� � ������
			*pUpdateCity = recCity;

			// ���������� ������
			break;
		}
	}
	
	// ������ UpdateAllViews �� ������ View-�� � ��������� �� �������� � CObject ����-��� ������������ ����
	UpdateAllViews(NULL, OnUpdateHintUpdate, (CObject*)&recCity);

	return TRUE;
}

BOOL CCitiesDocument::InsertData(CITIES& recCity)
{
	CCitiesData oCitiesData;

	// �������� ����� � ������ �����
	if (!oCitiesData.InsertCity(recCity))
		return FALSE;

	// �������� ����� �� ��� ���� � �� �����������
	CITIES* pNewCity = new CITIES();
	*pNewCity = recCity;

	// �������� ����� � ������ ��
	m_oCitiesArray.Add(pNewCity);

	// ������ UpdateAllViews �� ������ View-�� � ��������� �� �������� � CObject ����-��� ��������� ����
	UpdateAllViews(NULL, OnUpdateHintInsert, (CObject*)pNewCity);

	return TRUE;
}

BOOL CCitiesDocument::DeleteData(const long lID)
{
	CCitiesData oCitiesData;

	// ��������� ����� �� ������ �����
	if (!oCitiesData.DeleteCity(lID))
		return FALSE;

	CITIES recDeleteCity;

	// ���������  ������  �� �� ������� ����� , ����� ������ �� �������
	for (INT_PTR nIndex = 0; nIndex < m_oCitiesArray.GetSize(); nIndex++)
	{
		CITIES* pCity= m_oCitiesArray.GetAt(nIndex);
		if (pCity == nullptr)
			return FALSE;

		if (pCity->lID == lID)
		{
			recDeleteCity = *pCity;

			// ��������� ����� �� ������
			m_oCitiesArray.Delete(nIndex);

			// ���������� ������
			break;
		}
	}

	// ������ UpdateAllViews �� ������ View-�� � ��������� �� ��������� � CObject ����-��� �������� ����
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

	// ��������� ������ �����
	if (!PrepareDocumentData())
		return FALSE;

	return TRUE;
}