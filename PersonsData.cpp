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

	// Зареждаме хората от базата данни в масива oPersonsArray
	if (!oPersonTable.SelectAll(oPersonsArray))
		return FALSE;

	return TRUE;
}

BOOL CPersonsData::SelectPersonAndNumbersWithID(const long lID, CPersonInformation& recPerson)
{
	CPersonsTable oPersonTable;

	// Избираме човек по lID от базата данни и го присвояваме на recPerson
	if (!oPersonTable.SelectWhereID(lID, recPerson.GetPerson()))
		return FALSE;

	// Пълним масива с телефонни номера на човека
	if (!FillPersonNumbers(recPerson))
		return FALSE;

	return TRUE;
}

BOOL CPersonsData::UpdatePersonAndNumbers(CPersonInformation& recPerson)
{
	// Отваряме сесия и транзакция
	CSession oSession;
	if (!StartCustomSessionAndTransaction(oSession))
		return FALSE;

	// Подаваме собствена сесия
	CPersonsTable oPersonTable(&oSession);

	// Променяме запис от базата данни по ИД с новите данни recPerson
	if (!oPersonTable.UpdateWhereID(recPerson.GetPerson()))
	{
		oSession.Abort();
		oSession.Close();

		return FALSE;
	}

	// Подаваме собствена сесия
	CPhoneNumbersTable oPhoneNumbersTable(&oSession);
	
	// Запълваме масива с всичките стари телефонни номера
	CPhoneNumbersArray oPhoneNumbersArray;
	if (!oPhoneNumbersTable.SelectAll(oPhoneNumbersArray))
	{
		oSession.Abort();
		oSession.Close();

		return FALSE;
	}

	// Обхождаме масива с обновените телефонни номера
	for (INT_PTR nIndex = 0; nIndex < recPerson.GetPhoneNumbers().GetCount(); nIndex++)
	{
		PHONE_NUMBERS* pPhoneNumber = recPerson.GetPhoneNumbers().GetAt(nIndex);
		if (pPhoneNumber == nullptr)
			return FALSE;

		// Ако ИД-то е 0 , телефона е нов и го вкарваме в базата данни
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

		// Обхождаме стария масив с телефонни номера
		for (INT_PTR nUpdateIndex = 0; nUpdateIndex < oPhoneNumbersArray.GetCount(); nUpdateIndex++)
		{
			PHONE_NUMBERS* pUpdatePhone = oPhoneNumbersArray.GetAt(nUpdateIndex);
			if (pUpdatePhone == nullptr)
			{
				oSession.Abort();
				oSession.Close();

				return FALSE;
			}

			// Ако ИД-то не съвпада прескачаме елемента
			if (pPhoneNumber->lID != pUpdatePhone->lID)
			{
				continue;
			}

			// Сравняваме новия и стария телефон за разлики
			if (ArePhoneNumbersEqual(*pPhoneNumber, *pUpdatePhone))
			{
				break;
			}

			// Ако има промени , обновяваме в базата данни
			if (!oPhoneNumbersTable.UpdateWhereID(*pPhoneNumber))
			{
				oSession.Abort();
				oSession.Close();

				return FALSE;
			}

			break;
		}
	}

	// Обхождаме стария масив с телефонни номера
	for (INT_PTR nArrayIndex = 0; nArrayIndex < oPhoneNumbersArray.GetCount(); nArrayIndex++)
	{
		PHONE_NUMBERS* pOldNumber = oPhoneNumbersArray.GetAt(nArrayIndex);
		if (pOldNumber == nullptr)
		{
			oSession.Abort();
			oSession.Close();

			return FALSE;
		}

		// Обхождаме новия масив с телефонни номера
		for (INT_PTR nDeleteIndex = 0; nDeleteIndex < recPerson.GetPhoneNumbers().GetCount(); nDeleteIndex++)
		{
			PHONE_NUMBERS* pNewNumber = recPerson.GetPhoneNumbers().GetAt(nDeleteIndex);
			if (pNewNumber == nullptr)
			{
				oSession.Abort();
				oSession.Close();

				return FALSE;
			}

			// Ако ИД-тата на човека не съвпадат , прескачаме
			if (pOldNumber->lPersonID != pNewNumber->lPersonID)
			{
				break;
			}

			// Ако намерим съвпадение , не трябва да се трие телефонния номер
			if (pOldNumber->lID == pNewNumber->lID)
			{
				break;
			}
			
			// Ако стигнем края на масива и не сме намерили телефона  го трием
			if (nDeleteIndex == recPerson.GetPhoneNumbers().GetCount() - 1)
			{
				// Трием телефонния номер от базата
				if (!oPhoneNumbersTable.DeleteWhereID(pOldNumber->lID))
				{
					oSession.Abort();
					oSession.Close();

					return FALSE;
				}
			}
		}		
	}

	// Изпълняваме транзакцията и затваряме сесията
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
	// Отваряме сесия и транзакция
	CSession oSession;
	if (!StartCustomSessionAndTransaction(oSession))
		return FALSE;

	// Подаваме собствена сесия
	CPersonsTable oPersonTable(&oSession);
	CPhoneNumbersTable oPhoneNumbersTable(&oSession);

	// Добавяме новия човек в базата данни
	if (!oPersonTable.Insert(recPerson.GetPerson()))
	{
		oSession.Abort();
		oSession.Close();

		return FALSE;
	}

	// Обхождаме новия масив с телефонните номера
	for (INT_PTR nIndex = 0; nIndex < recPerson.GetPhoneNumbers().GetCount(); nIndex++)
	{
		PHONE_NUMBERS* pPhoneNumber = recPerson.GetPhoneNumbers().GetAt(nIndex);
		if (pPhoneNumber == nullptr)
		{
			oSession.Abort();
			oSession.Close();

			return FALSE;
		}

		// Задаваме стойност на lPersonID равна на ID-то на новодобавения човек
		pPhoneNumber->lPersonID = recPerson.GetPerson().lID;

		// Добавяме телефонния номер в базата
		if (!oPhoneNumbersTable.Insert(*pPhoneNumber))
		{
			oSession.Abort();
			oSession.Close();

			return FALSE;
		}
	}

	// Изпълняваме транзакцията и затваряме сесията
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
	// Отваряме сесия и транзакция
	CSession oSession;
	if (!StartCustomSessionAndTransaction(oSession))
		return FALSE;

	// Подаваме собствена сесия
	CPersonsTable oPersonTable(&oSession);
	CPhoneNumbersTable oPhoneNumbersTable(&oSession);

	// Пълним масива с всички телефонни номера
	CPhoneNumbersArray oPhoneNumbersArray;
	if (!oPhoneNumbersTable.SelectAll(oPhoneNumbersArray))
		return FALSE;

	// Обхождаме масива
	for (INT_PTR nIndex = 0; nIndex < oPhoneNumbersArray.GetCount(); nIndex++)
	{
		PHONE_NUMBERS* pPhoneNumber = oPhoneNumbersArray.GetAt(nIndex);

		// Ако телефонния номер не е на човека който изтриваме , прескачаме
		if (pPhoneNumber->lPersonID != lID)
		{
			continue;
		}

		// Изтриваме телефонния номер от базата
		if (!oPhoneNumbersTable.DeleteWhereID(pPhoneNumber->lID))
		{
			oSession.Abort();
			oSession.Close();

			return FALSE;
		}
	}

	// Изтриваме човека от базата данни с ИД = lID
	if (!oPersonTable.DeleteWhereID(lID))
	{
		oSession.Abort();
		oSession.Close();

		return FALSE;
	}

	// Изпълняваме транзакцията и затваряме сесията
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
	// Напълваме масива с всички телефонни номера
	CPhoneNumbersArray oPhoneNumbersArray;
	CPhoneNumbersData oPhoneNumbersData;
	if (!oPhoneNumbersData.SelectAllData(oPhoneNumbersArray))
		return FALSE;

	for (INT_PTR nIndex = 0; nIndex < oPhoneNumbersArray.GetCount(); nIndex++)
	{
		PHONE_NUMBERS* pPhoneNumber = oPhoneNumbersArray.GetAt(nIndex);
		if (pPhoneNumber == nullptr)
			return FALSE;

		// Ако телефонния номер е на подадения човек (oPersonInformation) , го записваме в масива му
		if (oPersonInformation.GetPerson().lID == pPhoneNumber->lPersonID)
		{
			// Заделяме нова памет
			PHONE_NUMBERS* pNewPhoneNumber = new PHONE_NUMBERS();

			// Присвояваме стойността
			*pNewPhoneNumber = *pPhoneNumber;

			// Записваме новия указател в масива с телефонни номера
			oPersonInformation.GetPhoneNumbers().Add(pNewPhoneNumber);
		}
	}

	return TRUE;
}

BOOL CPersonsData::ArePhoneNumbersEqual(const PHONE_NUMBERS& recPhoneLeft, const PHONE_NUMBERS& recPhoneRight)
{
	// Проверка дали подадените телефонни номера са идентични
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
	// Вземам инстанция от singleton класа за да отворим сесията
	CDataBaseConnection* pDataBaseConnection = CDataBaseConnection::GetInstance();
	HRESULT hResult = oSession.Open(pDataBaseConnection->GetDataSource());
	if (FAILED(hResult))
	{
		CString strMessage;
		strMessage.Format(_T("Unable to open session. Error: %d"), hResult);
		AfxMessageBox(strMessage);

		return FALSE;
	}

	// Отваряме транзакция
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


