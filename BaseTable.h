#pragma once
#include <atldbcli.h>
#include "Structures.h"
#include "CitiesAccessor.h"
#include "PersonsAccessor.h"
#include "PhoneNumbersAccessor.h"
#include "PhoneTypesAccessor.h"
#include "DataBaseConnection.h"
#include "TransactionExits.h"


/////////////////////////////////////////////////////////////////////////////
// CBaseTable

/// <summary>Базов темплейтен клас за всички таблични класове</summary>
///<param name="RecordType"> Тип на структурата</param>
///<param name="AccessorType"> Аксесора който ще използваме</param>
template<typename RecordType , typename AccessorType>
class CBaseTable : public CCommand<CAccessor<AccessorType>>
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	// Подразбиращ се конструктор , който може да приема външна сесия
	CBaseTable(CSession* pSession = NULL)
	{
		// Ако е подадена външна сесия я присвояваме и вдигаме флага m_bCustomSession
		if (pSession != NULL)
		{
			m_pSession = pSession;
			m_bCustomSession = TRUE;
		}

		// Ако не е подадена външна сесия си я създаваме и сваляме флага m_bCustomSession
		else 
		{
			m_pSession = new CSession();
			m_bCustomSession = FALSE;
		}
		
	}

	virtual ~CBaseTable()
	{
		// Зачистваме заделената памет за сесията
		if (m_pSession != NULL && !m_bCustomSession)
			delete m_pSession;
	}


// Methods
// ----------------
protected:
	///<summary> Инициализация  на oAlterDBPropSet за да може да прави промени по базата</summary>
	void InitializeDBPropSet(CDBPropSet& oAlterDBPropSet)
	{
		oAlterDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
		oAlterDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
		oAlterDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
		oAlterDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	}

public:
	/// <summary>Отваряне на сесия</summary>
	/// <param name="bTransactionFlag">Булев флаг за транзакция</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL EstablishSessionConnection(const BOOL bTransactionFlag = FALSE)
	{
		// Проверка дали сесията е външна , ако е не създаваме наша
		if (m_bCustomSession == FALSE)
		{
			// Викаме инстанцията за DataSource , за да я използваме за сесията
			CDataBaseConnection* pDataBaseConnection = CDataBaseConnection::GetInstance();
			HRESULT hResult = m_pSession->Open(pDataBaseConnection->GetDataSource());
			if (FAILED(hResult))
			{
				CString strMessage;
				strMessage.Format(_T("Unable to open session. Error: %d"), hResult);
				AfxMessageBox(strMessage);

				return FALSE;
			}

			// Ако е подаден флаг за транзакция , отваряме една
			if (bTransactionFlag == TRUE)
			{
				if (!BeginTransaction())
				{
					m_pSession->Close();

					return FALSE;
				}
			}
		}

		return TRUE;
	}

	/// <summary>Изпълнение на командата</summary>
	/// <param name = "strQuery"> Командата която ще изпълним</param>
	/// <param name = "bAlterFlag"> Булев флаг, който показва дали ще правим промени по таблицата </param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL ExecuteCommand(const CString& strQuery, const BOOL bAlterFlag = FALSE)
	{
		HRESULT hResult = S_OK;

		// Ако bAlterFlag е подаден като TRUE , инициализираме CDBPropSet(DBPROPSET_ROWSET)
		if (bAlterFlag == TRUE)
		{
			CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
			InitializeDBPropSet(oUpdateDBPropSet);
			hResult = Open(*m_pSession, strQuery, &oUpdateDBPropSet);
		}
		else
			hResult = Open(*m_pSession, strQuery);

		if (FAILED(hResult))
		{
			CString strMessage;
			strMessage.Format(_T("Error executing query. Error: %d. Query: %s"), hResult, strQuery);
			AfxMessageBox(strMessage);

			return FALSE;
		}

		return TRUE;
	}

	/// <summary>Опит за изчитане на първия ред от Rowset-a</summary>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL MoveToFirstRecordInRowset()
	{
		// Отиваме на първия запис в rowset-a
		HRESULT hResult = MoveFirst();
		if (FAILED(hResult))
		{
			CString strMessage;
			strMessage.Format(_T("Error opening record. Error: %d."), hResult);
			AfxMessageBox(strMessage);

			return FALSE;
		}

		// Проверяваме дали е края на rowset-a
		if (!IsEndOfRowset(hResult))
			return FALSE;

		return TRUE;
	}

	/// <summary>Проверка дали сме стигнали края на Rowset-a</summary>
	///<returns> Връща TRUE ако сме и FALSE ако не сме</returns>
	BOOL IsEndOfRowset(const HRESULT& hResult)
	{
		if (hResult == DB_S_ENDOFROWSET)
		{
			return FALSE;
		}

		return TRUE;
	}

	/// <summary>Rollback-ваме транзакцията</summary>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL AbortTransaction()
	{
		// Aбортираме сесията
		HRESULT hResult = m_pSession->Abort();
		if (FAILED(hResult))
		{
			CString strMessage;
			strMessage.Format(_T("Error aborting a transaction.Unwanted changes may have been made."));
			AfxMessageBox(strMessage);

			return FALSE;
		}

		return TRUE;
	}

	/// <summary>Стартираме транзакция</summary>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL BeginTransaction()
	{
		// Стартираме транзакция
		HRESULT hResult = m_pSession->StartTransaction();
		if (FAILED(hResult))
		{
			CString strMessage;
			strMessage.Format(_T("Error starting a transaction."));
			AfxMessageBox(strMessage);

			return FALSE;
		}

		return TRUE;
	}

	/// <summary>Изпълняваме транзакцията</summary>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL CommitTransaction()
	{
		// Изпълняваме транзакцията
		HRESULT hResult = m_pSession->Commit();
		if (FAILED(hResult))
		{
			CString strMessage;
			strMessage.Format(_T("Error committing the transaction."));
			AfxMessageBox(strMessage);

			return FALSE;
		}

		return TRUE;
	}

	/// <summary>Затваряме сесията и командата</summary>
	///<param name="bIsCommandOpen"> Флаг дали е отворен rowset</param>
	///<param name="eTransactionExit"> Флаг дали трябва да се изпълни или абортира транзакцията</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL CloseSession(const BOOL bIsCommandOpen = TRUE, TransactionExits eTransactionExit = TransactionExitAbort)
	{
		// Ако е отворена команда я затваряме
		if (bIsCommandOpen == TRUE)
		{
			Close();
		}

		// Ако нямаме собствена сесия , я затваряме тук.
		if (m_bCustomSession == FALSE)
		{
			// Проверка дали има отворена транзакция
			XACTTRANSINFO oInfo;
			HRESULT hResult = m_pSession->GetTransactionInfo(&oInfo);
			if (hResult == S_OK)
			{
				// Ако е започната транзакция , според втория флаг(енум) изпълняваме или абортираме
				if (eTransactionExit == TransactionExitCommit)
				{
					if (!CommitTransaction())
					{
						AbortTransaction();
						m_pSession->Close();

						return FALSE;
					}
				}

				if (eTransactionExit == TransactionExitAbort)
				{
					AbortTransaction();
					m_pSession->Close();

					return FALSE;
				}
			}

			m_pSession->Close();
		}

		return TRUE;
	}

public:
	/// <summary>Метод за избор на всички записи в таблица</summary>
	///<param name="oArray"> Масива който запълваме с елементите</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL SelectAll(CAutoFreeMemoryArray<RecordType*>& oArray)
	{
		// Отваряне на сесия
		if (!EstablishSessionConnection())
		{
			return FALSE;
		}

		// Конструираме заявката
		CString strSelectAllQuery;
		strSelectAllQuery.Format(_T("SELECT * FROM %ls WITH(NOLOCK)"), GetTableName());

		// Изпълняваме командата
		if (!ExecuteCommand(strSelectAllQuery))
		{
			CloseSession(FALSE);

			return FALSE;
		}

		HRESULT hResult = S_OK;

		// Прочитаме всички данни
		while (true)
		{
			hResult = MoveNext();
			if (FAILED(hResult))
			{
				CString strMessage;
				strMessage.Format(_T("Error opening record."));
				AfxMessageBox(strMessage);

				CloseSession(TRUE);

				return FALSE;
			}

			if (!IsEndOfRowset(hResult))
			{
				break;
			}

			// Вземаме текущия елемент от rowset-a
			RecordType* pRecord = new RecordType;
			*pRecord = GetAccessor();

			// Пълним подадения масив с данните
			oArray.Add(pRecord);
		}

		// Затваряме командата и сесията
		CloseSession(TRUE);

		return TRUE;
	}

	/// <summary>Метод за избор на един запис в таблица по ID</summary>
	///<param name="lID"> lID по което ще изберем записа</param>
	///<param name="Record"> Записваме избрания запис тук</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL SelectWhereID(const long lID, RecordType& Record)
	{
		// Отваряне на сесия
		if (!EstablishSessionConnection())
		{
			return FALSE;
		}

		// Конструираме заявката
		CString strSelectWhereIDQuery;
		strSelectWhereIDQuery.Format(_T("SELECT * FROM %ls WITH(NOLOCK) WHERE ID=%d"), GetTableName(), lID);

		// Изпълняваме командата
		if (!ExecuteCommand(strSelectWhereIDQuery))
		{
			CloseSession(FALSE);

			return FALSE;
		}

		HRESULT hResult = S_OK;

		// Прочитаме първия ред в rowset-a
		if (!MoveToFirstRecordInRowset())
		{
			CloseSession(TRUE);

			return FALSE;
		}

		// Записваме прочетените данни
		Record = GetAccessor();

		// Затваряме командата и сесията
		CloseSession(TRUE);

		return TRUE;
	}

	/// <summary>Метод за промяна на запис в таблица</summary>
	///<param name="Record"> Новия запис с който редактираме</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL UpdateWhereID(RecordType& Record)
	{
		// Отваряне на сесия и стартираме транзакция
		if (!EstablishSessionConnection(TRUE))
		{
			return FALSE;
		}
		
		// Конструираме заявката
		CString strUpdateWhereIDQuery;
		strUpdateWhereIDQuery.Format(_T("SELECT * FROM %ls WITH(UPDLOCK) WHERE ID = %d"), GetTableName(), Record.lID);

		// Изпълняваме командата
		if (!ExecuteCommand(strUpdateWhereIDQuery, TRUE))
		{
			CloseSession(FALSE, TransactionExitAbort);

			return FALSE;
		}

		HRESULT hResult = S_OK;

		// Прочитаме първия запис в rowset-a
		if (!MoveToFirstRecordInRowset())
		{
			CloseSession(TRUE, TransactionExitAbort);

			return FALSE;
		}

		// Проверка дали някой друг не обработва данните
		if (GetRecordUpdateCounter(Record) != GetAccessorUpdateCounter())
		{
			CString strMessage;
			strMessage.Format(_T("Error updating record.It was being modified by someone else. Error: %d. Query: %s"),
				hResult, strUpdateWhereIDQuery);
			AfxMessageBox(strMessage);

			CloseSession(TRUE, TransactionExitAbort);

			return FALSE;
		}

		// Актуализираме данните с новите и инкрементираме UpdateCounter
		GetAccessor() = Record;
		GetAccessorUpdateCounter()++;

		// Записваме данните
		hResult = SetData(ACCESSOR_WITHOUT_ID);
		if (FAILED(hResult))
		{
			CString strMessage;
			strMessage.Format(_T("Error updating record. Error: %d. Query: %s"), hResult, strUpdateWhereIDQuery);
			AfxMessageBox(strMessage);

			CloseSession(TRUE, TransactionExitAbort);

			return FALSE;
		}

		// Затваряме командата и сесията
		if (!CloseSession(TRUE, TransactionExitCommit))
			return FALSE;

		GetRecordUpdateCounter(Record)++;		

		return TRUE;
	}

	/// <summary>Метод за добавяне на запис в таблица</summary>
	///<param name="Record"> Новия запис който вкарваме</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL Insert(RecordType& Record)
	{
		// Отваряне на сесия 
		if (!EstablishSessionConnection())
		{
			return FALSE;
		}

		// Конструираме заявката
		CString strInsertQuery;
		strInsertQuery.Format(_T("SELECT TOP 0 * FROM %ls"), GetTableName());

		// Изпълняваме командата
		if (!ExecuteCommand(strInsertQuery, TRUE))
		{
			CloseSession(FALSE);

			return FALSE;
		}

		// Присвояваме новия град
		GetAccessor() = Record;

		// Вмъкваме присвоения град в таблицата с първия аксесор
		HRESULT hResult = CRowset::Insert(ACCESSOR_WITHOUT_ID);
		if (FAILED(hResult))
		{
			CString strMessage;
			strMessage.Format(_T("Error inserting. Error: %d. Query: %s"), hResult, strInsertQuery);
			AfxMessageBox(strMessage);

			CloseSession();

			return FALSE;
		}

		// Отваряме записа който сме вмъкнали
		hResult = MoveNext();
		if (FAILED(hResult))
		{
			CloseSession();

			return FALSE;
		}

		// Записваме новия добавен град в recTable , за да имаме ID-то му записано
		Record = GetAccessor();

		// Затваряме командата и сесията
		CloseSession();

		return TRUE;
	}

	/// <summary>Метод за изтриване на запис от таблица по ID</summary>
	///<param name="lID"> ИД на запис който ще изтрием</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL DeleteWhereID(const long lID)
	{
		// Отваряне на сесия u Стартираме транзакция
		if (!EstablishSessionConnection(TRUE))
		{
			return FALSE;
		}

		// Конструираме заявката
		CString strDeleteWhereIDQuery;
		strDeleteWhereIDQuery.Format(_T("SELECT * FROM %ls WITH(ROWLOCK) WHERE ID=%d"), GetTableName(), lID);

		// Изпълняваме командата
		if (!ExecuteCommand(strDeleteWhereIDQuery, TRUE))
		{
			CloseSession(FALSE , TransactionExitAbort);

			return FALSE;
		}

		HRESULT hResult = S_OK;
		// Прочитаме първия ред от rowset-a
		if (!MoveToFirstRecordInRowset())
		{
			CloseSession(TRUE , TransactionExitAbort);

			return FALSE;
		}

		// Изтриваме прочетения ред
		hResult = Delete();
		if (FAILED(hResult))
		{
			CString strMessage;
			strMessage.Format(_T("Error deleting (might be due to reference)"));
			AfxMessageBox(strMessage);

			CloseSession(TRUE, TransactionExitAbort);

			return FALSE;
		}

		// Затваряме сесията и изпълняваме транзакцията
		if (!CloseSession(TRUE, TransactionExitCommit))
			return FALSE;

		return TRUE;
	}


// Overrides
// ----------------
	/// <summary>Достъпва името на таблицата</summary>
	/// <return>Връща името на таблицата </return>
	virtual CString GetTableName() = 0;
	/// <summary> Достъпва UpdateCounter-а на обекта</summary>
	///<param name="Record"> Референция на обект-а</param>
	/// <return> Връща UpdateCounter-а на обекта</return>
	virtual long& GetRecordUpdateCounter(RecordType& Record) = 0;


// Members
// ----------------
protected:
	/// <summary>Член променлива указател към сесия</summary>
	CSession* m_pSession;
	/// <summary>Член променлива флаг за собствена сесия</summary>
	BOOL m_bCustomSession;
};