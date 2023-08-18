#include "pch.h"
#include "PersonsData.h"
#include "PhoneNumbersData.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsData


// Constructor / Destructor
// ----------------
CPersonsData::CPersonsData()
{
}

CPersonsData::~CPersonsData()
{
}


// Methods
// ----------------
BOOL CPersonsData::SelectAllPeopleData(CPersonsArray& oPersonsArray)
{
	CPersonsTable oPersonTable;

	// ��������� ������ �� ������ ����� � ������ oPersonsArray
	if (!oPersonTable.SelectAll(oPersonsArray))
		return FALSE;

	return TRUE;
}

BOOL CPersonsData::SelectPersonAndNumbersWithID(const long lID, CPersonInformation& recPerson)
{
	CPersonsTable oPersonTable;

	// �������� ����� �� lID �� ������ ����� � �� ����������� �� recPerson
	if (!oPersonTable.SelectWhereID(lID, recPerson.GetPerson()))
		return FALSE;

	// ������ ������ � ��������� ������ �� ������
	if (!FillPersonNumbers(recPerson))
		return FALSE;

	return TRUE;
}

BOOL CPersonsData::UpdatePersonAndNumbers(CPersonInformation& recPerson)
{
	// �������� ����� � ����������
	CSession oSession;
	if (!StartCustomSessionAndTransaction(oSession))
		return FALSE;

	// �������� ��������� �����
	CPersonsTable oPersonTable(&oSession);

	// ��������� ����� �� ������ ����� �� �� � ������ ����� recPerson
	if (!oPersonTable.UpdateWhereID(recPerson.GetPerson()))
	{
		oSession.Abort();
		oSession.Close();

		return FALSE;
	}

	// �������� ��������� �����
	CPhoneNumbersTable oPhoneNumbersTable(&oSession);
	
	// ��������� ������ � �������� ����� ��������� ������
	CPhoneNumbersArray oPhoneNumbersArray;
	if (!oPhoneNumbersTable.SelectAll(oPhoneNumbersArray))
	{
		oSession.Abort();
		oSession.Close();

		return FALSE;
	}

	// ��������� ������ � ���������� ��������� ������
	for (INT_PTR nIndex = 0; nIndex < recPerson.GetPhoneNumbers().GetCount(); nIndex++)
	{
		PHONE_NUMBERS* pPhoneNumber = recPerson.GetPhoneNumbers().GetAt(nIndex);
		if (pPhoneNumber == nullptr)
			return FALSE;

		// ��� ��-�� � 0 , �������� � ��� � �� �������� � ������ �����
		if (pPhoneNumber->lID == 0)
		{
			if (!oPhoneNumbersTable.Insert(*pPhoneNumber))
			{
				oSession.Abort();
				oSession.Close();

				return FALSE;
			}

			continue;
		}

		// ��������� ������ ����� � ��������� ������
		for (INT_PTR nUpdateIndex = 0; nUpdateIndex < oPhoneNumbersArray.GetCount(); nUpdateIndex++)
		{
			PHONE_NUMBERS* pUpdatePhone = oPhoneNumbersArray.GetAt(nUpdateIndex);
			if (pUpdatePhone == nullptr)
			{
				oSession.Abort();
				oSession.Close();

				return FALSE;
			}

			// ��� ��-�� �� ������� ���������� ��������
			if (pPhoneNumber->lID != pUpdatePhone->lID)
			{
				continue;
			}

			// ���������� ����� � ������ ������� �� �������
			if (ArePhoneNumbersEqual(*pPhoneNumber, *pUpdatePhone))
			{
				break;
			}

			// ��� ��� ������� , ���������� � ������ �����
			if (!oPhoneNumbersTable.UpdateWhereID(*pPhoneNumber))
			{
				oSession.Abort();
				oSession.Close();

				return FALSE;
			}

			break;
		}
	}

	// ��������� ������ ����� � ��������� ������
	for (INT_PTR nArrayIndex = 0; nArrayIndex < oPhoneNumbersArray.GetCount(); nArrayIndex++)
	{
		PHONE_NUMBERS* pOldNumber = oPhoneNumbersArray.GetAt(nArrayIndex);
		if (pOldNumber == nullptr)
		{
			oSession.Abort();
			oSession.Close();

			return FALSE;
		}

		// ��������� ����� ����� � ��������� ������
		for (INT_PTR nDeleteIndex = 0; nDeleteIndex < recPerson.GetPhoneNumbers().GetCount(); nDeleteIndex++)
		{
			PHONE_NUMBERS* pNewNumber = recPerson.GetPhoneNumbers().GetAt(nDeleteIndex);
			if (pNewNumber == nullptr)
			{
				oSession.Abort();
				oSession.Close();

				return FALSE;
			}

			// ��� ��-���� �� ������ �� �������� , ����������
			if (pOldNumber->lPersonID != pNewNumber->lPersonID)
			{
				break;
			}

			// ��� ������� ���������� , �� ������ �� �� ���� ���������� �����
			if (pOldNumber->lID == pNewNumber->lID)
			{
				break;
			}
			
			// ��� ������� ���� �� ������ � �� ��� �������� ��������  �� �����
			if (nDeleteIndex == recPerson.GetPhoneNumbers().GetCount() - 1)
			{
				// ����� ���������� ����� �� ������
				if (!oPhoneNumbersTable.DeleteWhereID(pOldNumber->lID))
				{
					oSession.Abort();
					oSession.Close();

					return FALSE;
				}
			}
		}		
	}

	// ����������� ������������ � ��������� �������
	HRESULT hResult = oSession.Commit();
	if (hResult != S_OK)
	{
		oSession.Abort();
		oSession.Close();

		return FALSE;
	}
	oSession.Close();

	return TRUE;
}

BOOL CPersonsData::InsertPersonAndNumbers(CPersonInformation& recPerson)
{
	// �������� ����� � ����������
	CSession oSession;
	if (!StartCustomSessionAndTransaction(oSession))
		return FALSE;

	// �������� ��������� �����
	CPersonsTable oPersonTable(&oSession);
	CPhoneNumbersTable oPhoneNumbersTable(&oSession);

	// �������� ����� ����� � ������ �����
	if (!oPersonTable.Insert(recPerson.GetPerson()))
	{
		oSession.Abort();
		oSession.Close();

		return FALSE;
	}

	// ��������� ����� ����� � ����������� ������
	for (INT_PTR nIndex = 0; nIndex < recPerson.GetPhoneNumbers().GetCount(); nIndex++)
	{
		PHONE_NUMBERS* pPhoneNumber = recPerson.GetPhoneNumbers().GetAt(nIndex);
		if (pPhoneNumber == nullptr)
		{
			oSession.Abort();
			oSession.Close();

			return FALSE;
		}

		// �������� �������� �� lPersonID ����� �� ID-�� �� ������������� �����
		pPhoneNumber->lPersonID = recPerson.GetPerson().lID;

		// �������� ���������� ����� � ������
		if (!oPhoneNumbersTable.Insert(*pPhoneNumber))
		{
			oSession.Abort();
			oSession.Close();

			return FALSE;
		}
	}

	// ����������� ������������ � ��������� �������
	HRESULT hResult = oSession.Commit();
	if (hResult != S_OK)
	{
		oSession.Abort();
		oSession.Close();

		return FALSE;
	}

	oSession.Close();

	return TRUE;
}

BOOL CPersonsData::DeletePersonAndNumbers(const long lID)
{
	// �������� ����� � ����������
	CSession oSession;
	if (!StartCustomSessionAndTransaction(oSession))
		return FALSE;

	// �������� ��������� �����
	CPersonsTable oPersonTable(&oSession);
	CPhoneNumbersTable oPhoneNumbersTable(&oSession);

	// ������ ������ � ������ ��������� ������
	CPhoneNumbersArray oPhoneNumbersArray;
	if (!oPhoneNumbersTable.SelectAll(oPhoneNumbersArray))
		return FALSE;

	// ��������� ������
	for (INT_PTR nIndex = 0; nIndex < oPhoneNumbersArray.GetCount(); nIndex++)
	{
		PHONE_NUMBERS* pPhoneNumber = oPhoneNumbersArray.GetAt(nIndex);

		// ��� ���������� ����� �� � �� ������ ����� ��������� , ����������
		if (pPhoneNumber->lPersonID != lID)
		{
			continue;
		}

		// ��������� ���������� ����� �� ������
		if (!oPhoneNumbersTable.DeleteWhereID(pPhoneNumber->lID))
		{
			oSession.Abort();
			oSession.Close();

			return FALSE;
		}
	}

	// ��������� ������ �� ������ ����� � �� = lID
	if (!oPersonTable.DeleteWhereID(lID))
	{
		oSession.Abort();
		oSession.Close();

		return FALSE;
	}

	// ����������� ������������ � ��������� �������
	HRESULT hResult = oSession.Commit();
	if (hResult != S_OK)
	{
		oSession.Abort();
		oSession.Close();

		return FALSE;
	}
	oSession.Close();

	return TRUE;
}

BOOL CPersonsData::FillPersonNumbers(CPersonInformation& oPersonInformation)
{
	// ��������� ������ � ������ ��������� ������
	CPhoneNumbersArray oPhoneNumbersArray;
	CPhoneNumbersData oPhoneNumbersData;
	if (!oPhoneNumbersData.SelectAllData(oPhoneNumbersArray))
		return FALSE;

	for (INT_PTR nIndex = 0; nIndex < oPhoneNumbersArray.GetCount(); nIndex++)
	{
		PHONE_NUMBERS* pPhoneNumber = oPhoneNumbersArray.GetAt(nIndex);
		if (pPhoneNumber == nullptr)
			return FALSE;

		// ��� ���������� ����� � �� ��������� ����� (oPersonInformation) , �� ��������� � ������ ��
		if (oPersonInformation.GetPerson().lID == pPhoneNumber->lPersonID)
		{
			// �������� ���� �����
			PHONE_NUMBERS* pNewPhoneNumber = new PHONE_NUMBERS();

			// ����������� ����������
			*pNewPhoneNumber = *pPhoneNumber;

			// ��������� ����� �������� � ������ � ��������� ������
			oPersonInformation.GetPhoneNumbers().Add(pNewPhoneNumber);
		}
	}

	return TRUE;
}

BOOL CPersonsData::ArePhoneNumbersEqual(const PHONE_NUMBERS& recPhoneLeft, const PHONE_NUMBERS& recPhoneRight)
{
	// �������� ���� ���������� ��������� ������ �� ���������
	if (recPhoneLeft.lID != recPhoneRight.lID)
		return FALSE;

	if (recPhoneLeft.lUpdateCounter != recPhoneRight.lUpdateCounter)
		return FALSE;

	if (recPhoneLeft.lPersonID != recPhoneRight.lPersonID)
		return FALSE;

	if (recPhoneLeft.lPhoneTypeID != recPhoneRight.lPhoneTypeID)
		return FALSE;

	if (wcscmp(recPhoneLeft.szPhone, recPhoneRight.szPhone) != 0)
		return FALSE;

	return TRUE;
}

BOOL CPersonsData::StartCustomSessionAndTransaction(CSession& oSession)
{
	// ������ ��������� �� singleton ����� �� �� ������� �������
	CDataBaseConnection* pDataBaseConnection = CDataBaseConnection::GetInstance();
	HRESULT hResult = oSession.Open(pDataBaseConnection->GetDataSource());
	if (FAILED(hResult))
	{
		CString strMessage;
		strMessage.Format(_T("Unable to open session. Error: %d"), hResult);
		AfxMessageBox(strMessage);

		return FALSE;
	}

	// �������� ����������
	hResult = oSession.StartTransaction();
	if (FAILED(hResult))
	{
		CString strMessage;
		strMessage.Format(_T("Error starting a transaction."));
		AfxMessageBox(strMessage);

		oSession.Close();

		return FALSE;
	}

	return TRUE;
}


// Overrides
// ----------------


