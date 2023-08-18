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

	// ��������� ������ ��������� ������ �� ������ � ������ m_oPhoneTypesArray
	if (!oPhoneTypesData.SelectAllData(m_oPhoneTypesArray))
		return FALSE;

	return TRUE;
}

BOOL CPhoneTypesDocument::SelectDataWithID(const long lID, PHONE_TYPES& recPhoneType)
{
	CPhoneTypesData oPhoneTypesData;

	// �������� ���������� ��� � �������� ID �� ������ �����
	if (!oPhoneTypesData.SelectDataWithID(lID, recPhoneType))
		return FALSE;

	return TRUE;
}

BOOL CPhoneTypesDocument::UpdateData(PHONE_TYPES& recPhoneType)
{
	CPhoneTypesData oPhoneTypesData;

	// ����������� ���������� ��� � ������ �����
	if (!oPhoneTypesData.UpdateData(recPhoneType))
		return FALSE;

	PHONE_TYPES* pUpdateType = nullptr;

	// ��������� ������  ��  �� ������� ���������� ��� , ����� ������ �� �����������
	for (INT_PTR nIndex = 0; nIndex < m_oPhoneTypesArray.GetSize(); nIndex++)
	{
		pUpdateType = m_oPhoneTypesArray.GetAt(nIndex);
		if (pUpdateType == nullptr)
			return FALSE;

		if (pUpdateType->lID == recPhoneType.lID)
		{
			// ��������� ���������� ��������� ���  � ������
			*pUpdateType = recPhoneType;

			break;
		}
	}

	// ������ UpdateAllViews �� ������ View-�� 
	UpdateAllViews(NULL, OnUpdateHintUpdate, (CObject*)pUpdateType);

	return TRUE;
}

BOOL CPhoneTypesDocument::InsertData(PHONE_TYPES& recPhoneType)
{
	CPhoneTypesData oPhoneTypesData;

	// �������� ���������� ��� � ������ �����
	if (!oPhoneTypesData.InsertData(recPhoneType))
		return FALSE;

	PHONE_TYPES* pNewPhoneType = new PHONE_TYPES(recPhoneType);

	// �������� ���������� ��� � ������ ��
	m_oPhoneTypesArray.Add(pNewPhoneType);

	// ������ UpdateAllViews �� ������ View-��
	UpdateAllViews(NULL, OnUpdateHintInsert, (CObject*)pNewPhoneType);

	return TRUE;
}

BOOL CPhoneTypesDocument::DeleteData(const long lID)
{
	CPhoneTypesData oPhoneTypesData;

	// ��������� ���������� ��� �� ������ �����
	if (!oPhoneTypesData.DeleteData(lID))
		return FALSE;

	PHONE_TYPES recPhoneType;

	// ���������  ������  �� �� ������� ���������� ��� , ����� ������ �� �������
	for (INT_PTR nIndex = 0; nIndex < m_oPhoneTypesArray.GetSize(); nIndex++)
	{
		PHONE_TYPES* pPhoneType = m_oPhoneTypesArray.GetAt(nIndex);
		if (pPhoneType == nullptr)
			return FALSE;

		if (pPhoneType->lID == lID)
		{
			recPhoneType = *pPhoneType;

			m_oPhoneTypesArray.Delete(nIndex);

			// ���������� ������
			break;
		}
	}

	// ������ UpdateAllViews �� ������ View-��
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

	// ��������� ������ ����� 
	if (!PrepareDocumentData())
		return FALSE;

	return TRUE;
}