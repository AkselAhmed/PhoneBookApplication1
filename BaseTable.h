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

/// <summary>����� ���������� ���� �� ������ �������� �������</summary>
///<param name="RecordType"> ��� �� �����������</param>
///<param name="AccessorType"> �������� ����� �� ����������</param>
template<typename RecordType , typename AccessorType>
class CBaseTable : public CCommand<CAccessor<AccessorType>>
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	// ����������� �� ����������� , ����� ���� �� ������ ������ �����
	CBaseTable(CSession* pSession = NULL)
	{
		// ��� � �������� ������ ����� � ����������� � ������� ����� m_bCustomSession
		if (pSession != NULL)
		{
			m_pSession = pSession;
			m_bCustomSession = TRUE;
		}

		// ��� �� � �������� ������ ����� �� � ��������� � ������� ����� m_bCustomSession
		else 
		{
			m_pSession = new CSession();
			m_bCustomSession = FALSE;
		}
		
	}

	virtual ~CBaseTable()
	{
		// ���������� ���������� ����� �� �������
		if (m_pSession != NULL && !m_bCustomSession)
			delete m_pSession;
	}


// Methods
// ----------------
protected:
	///<summary> �������������  �� oAlterDBPropSet �� �� ���� �� ����� ������� �� ������</summary>
	void InitializeDBPropSet(CDBPropSet& oAlterDBPropSet)
	{
		oAlterDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
		oAlterDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
		oAlterDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
		oAlterDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	}

public:
	/// <summary>�������� �� �����</summary>
	/// <param name="bTransactionFlag">����� ���� �� ����������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL EstablishSessionConnection(const BOOL bTransactionFlag = FALSE)
	{
		// �������� ���� ������� � ������ , ��� � �� ��������� ����
		if (m_bCustomSession == FALSE)
		{
			// ������ ����������� �� DataSource , �� �� � ���������� �� �������
			CDataBaseConnection* pDataBaseConnection = CDataBaseConnection::GetInstance();
			HRESULT hResult = m_pSession->Open(pDataBaseConnection->GetDataSource());
			if (FAILED(hResult))
			{
				CString strMessage;
				strMessage.Format(_T("Unable to open session. Error: %d"), hResult);
				AfxMessageBox(strMessage);

				return FALSE;
			}

			// ��� � ������� ���� �� ���������� , �������� ����
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

	/// <summary>���������� �� ���������</summary>
	/// <param name = "strQuery"> ��������� ����� �� ��������</param>
	/// <param name = "bAlterFlag"> ����� ����, ����� ������� ���� �� ������ ������� �� ��������� </param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL ExecuteCommand(const CString& strQuery, const BOOL bAlterFlag = FALSE)
	{
		HRESULT hResult = S_OK;

		// ��� bAlterFlag � ������� ���� TRUE , �������������� CDBPropSet(DBPROPSET_ROWSET)
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

	/// <summary>���� �� �������� �� ������ ��� �� Rowset-a</summary>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL MoveToFirstRecordInRowset()
	{
		// ������� �� ������ ����� � rowset-a
		HRESULT hResult = MoveFirst();
		if (FAILED(hResult))
		{
			CString strMessage;
			strMessage.Format(_T("Error opening record. Error: %d."), hResult);
			AfxMessageBox(strMessage);

			return FALSE;
		}

		// ����������� ���� � ���� �� rowset-a
		if (!IsEndOfRowset(hResult))
			return FALSE;

		return TRUE;
	}

	/// <summary>�������� ���� ��� �������� ���� �� Rowset-a</summary>
	///<returns> ����� TRUE ��� ��� � FALSE ��� �� ���</returns>
	BOOL IsEndOfRowset(const HRESULT& hResult)
	{
		if (hResult == DB_S_ENDOFROWSET)
		{
			return FALSE;
		}

		return TRUE;
	}

	/// <summary>Rollback-���� ������������</summary>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL AbortTransaction()
	{
		// A��������� �������
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

	/// <summary>���������� ����������</summary>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL BeginTransaction()
	{
		// ���������� ����������
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

	/// <summary>����������� ������������</summary>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL CommitTransaction()
	{
		// ����������� ������������
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

	/// <summary>��������� ������� � ���������</summary>
	///<param name="bIsCommandOpen"> ���� ���� � ������� rowset</param>
	///<param name="eTransactionExit"> ���� ���� ������ �� �� ������� ��� �������� ������������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL CloseSession(const BOOL bIsCommandOpen = TRUE, TransactionExits eTransactionExit = TransactionExitAbort)
	{
		// ��� � �������� ������� � ���������
		if (bIsCommandOpen == TRUE)
		{
			Close();
		}

		// ��� ������ ��������� ����� , � ��������� ���.
		if (m_bCustomSession == FALSE)
		{
			// �������� ���� ��� �������� ����������
			XACTTRANSINFO oInfo;
			HRESULT hResult = m_pSession->GetTransactionInfo(&oInfo);
			if (hResult == S_OK)
			{
				// ��� � ��������� ���������� , ������ ������ ����(����) ����������� ��� ����������
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
	/// <summary>����� �� ����� �� ������ ������ � �������</summary>
	///<param name="oArray"> ������ ����� ��������� � ����������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL SelectAll(CAutoFreeMemoryArray<RecordType*>& oArray)
	{
		// �������� �� �����
		if (!EstablishSessionConnection())
		{
			return FALSE;
		}

		// ������������ ��������
		CString strSelectAllQuery;
		strSelectAllQuery.Format(_T("SELECT * FROM %ls WITH(NOLOCK)"), GetTableName());

		// ����������� ���������
		if (!ExecuteCommand(strSelectAllQuery))
		{
			CloseSession(FALSE);

			return FALSE;
		}

		HRESULT hResult = S_OK;

		// ��������� ������ �����
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

			// ������� ������� ������� �� rowset-a
			RecordType* pRecord = new RecordType;
			*pRecord = GetAccessor();

			// ������ ��������� ����� � �������
			oArray.Add(pRecord);
		}

		// ��������� ��������� � �������
		CloseSession(TRUE);

		return TRUE;
	}

	/// <summary>����� �� ����� �� ���� ����� � ������� �� ID</summary>
	///<param name="lID"> lID �� ����� �� ������� ������</param>
	///<param name="Record"> ��������� �������� ����� ���</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL SelectWhereID(const long lID, RecordType& Record)
	{
		// �������� �� �����
		if (!EstablishSessionConnection())
		{
			return FALSE;
		}

		// ������������ ��������
		CString strSelectWhereIDQuery;
		strSelectWhereIDQuery.Format(_T("SELECT * FROM %ls WITH(NOLOCK) WHERE ID=%d"), GetTableName(), lID);

		// ����������� ���������
		if (!ExecuteCommand(strSelectWhereIDQuery))
		{
			CloseSession(FALSE);

			return FALSE;
		}

		HRESULT hResult = S_OK;

		// ��������� ������ ��� � rowset-a
		if (!MoveToFirstRecordInRowset())
		{
			CloseSession(TRUE);

			return FALSE;
		}

		// ��������� ����������� �����
		Record = GetAccessor();

		// ��������� ��������� � �������
		CloseSession(TRUE);

		return TRUE;
	}

	/// <summary>����� �� ������� �� ����� � �������</summary>
	///<param name="Record"> ����� ����� � ����� �����������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL UpdateWhereID(RecordType& Record)
	{
		// �������� �� ����� � ���������� ����������
		if (!EstablishSessionConnection(TRUE))
		{
			return FALSE;
		}
		
		// ������������ ��������
		CString strUpdateWhereIDQuery;
		strUpdateWhereIDQuery.Format(_T("SELECT * FROM %ls WITH(UPDLOCK) WHERE ID = %d"), GetTableName(), Record.lID);

		// ����������� ���������
		if (!ExecuteCommand(strUpdateWhereIDQuery, TRUE))
		{
			CloseSession(FALSE, TransactionExitAbort);

			return FALSE;
		}

		HRESULT hResult = S_OK;

		// ��������� ������ ����� � rowset-a
		if (!MoveToFirstRecordInRowset())
		{
			CloseSession(TRUE, TransactionExitAbort);

			return FALSE;
		}

		// �������� ���� ����� ���� �� ��������� �������
		if (GetRecordUpdateCounter(Record) != GetAccessorUpdateCounter())
		{
			CString strMessage;
			strMessage.Format(_T("Error updating record.It was being modified by someone else. Error: %d. Query: %s"),
				hResult, strUpdateWhereIDQuery);
			AfxMessageBox(strMessage);

			CloseSession(TRUE, TransactionExitAbort);

			return FALSE;
		}

		// ������������� ������� � ������ � �������������� UpdateCounter
		GetAccessor() = Record;
		GetAccessorUpdateCounter()++;

		// ��������� �������
		hResult = SetData(ACCESSOR_WITHOUT_ID);
		if (FAILED(hResult))
		{
			CString strMessage;
			strMessage.Format(_T("Error updating record. Error: %d. Query: %s"), hResult, strUpdateWhereIDQuery);
			AfxMessageBox(strMessage);

			CloseSession(TRUE, TransactionExitAbort);

			return FALSE;
		}

		// ��������� ��������� � �������
		if (!CloseSession(TRUE, TransactionExitCommit))
			return FALSE;

		GetRecordUpdateCounter(Record)++;		

		return TRUE;
	}

	/// <summary>����� �� �������� �� ����� � �������</summary>
	///<param name="Record"> ����� ����� ����� ��������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL Insert(RecordType& Record)
	{
		// �������� �� ����� 
		if (!EstablishSessionConnection())
		{
			return FALSE;
		}

		// ������������ ��������
		CString strInsertQuery;
		strInsertQuery.Format(_T("SELECT TOP 0 * FROM %ls"), GetTableName());

		// ����������� ���������
		if (!ExecuteCommand(strInsertQuery, TRUE))
		{
			CloseSession(FALSE);

			return FALSE;
		}

		// ����������� ����� ����
		GetAccessor() = Record;

		// �������� ���������� ���� � ��������� � ������ �������
		HRESULT hResult = CRowset::Insert(ACCESSOR_WITHOUT_ID);
		if (FAILED(hResult))
		{
			CString strMessage;
			strMessage.Format(_T("Error inserting. Error: %d. Query: %s"), hResult, strInsertQuery);
			AfxMessageBox(strMessage);

			CloseSession();

			return FALSE;
		}

		// �������� ������ ����� ��� ��������
		hResult = MoveNext();
		if (FAILED(hResult))
		{
			CloseSession();

			return FALSE;
		}

		// ��������� ����� ������� ���� � recTable , �� �� ����� ID-�� �� ��������
		Record = GetAccessor();

		// ��������� ��������� � �������
		CloseSession();

		return TRUE;
	}

	/// <summary>����� �� ��������� �� ����� �� ������� �� ID</summary>
	///<param name="lID"> �� �� ����� ����� �� �������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL DeleteWhereID(const long lID)
	{
		// �������� �� ����� u ���������� ����������
		if (!EstablishSessionConnection(TRUE))
		{
			return FALSE;
		}

		// ������������ ��������
		CString strDeleteWhereIDQuery;
		strDeleteWhereIDQuery.Format(_T("SELECT * FROM %ls WITH(ROWLOCK) WHERE ID=%d"), GetTableName(), lID);

		// ����������� ���������
		if (!ExecuteCommand(strDeleteWhereIDQuery, TRUE))
		{
			CloseSession(FALSE , TransactionExitAbort);

			return FALSE;
		}

		HRESULT hResult = S_OK;
		// ��������� ������ ��� �� rowset-a
		if (!MoveToFirstRecordInRowset())
		{
			CloseSession(TRUE , TransactionExitAbort);

			return FALSE;
		}

		// ��������� ���������� ���
		hResult = Delete();
		if (FAILED(hResult))
		{
			CString strMessage;
			strMessage.Format(_T("Error deleting (might be due to reference)"));
			AfxMessageBox(strMessage);

			CloseSession(TRUE, TransactionExitAbort);

			return FALSE;
		}

		// ��������� ������� � ����������� ������������
		if (!CloseSession(TRUE, TransactionExitCommit))
			return FALSE;

		return TRUE;
	}


// Overrides
// ----------------
	/// <summary>�������� ����� �� ���������</summary>
	/// <return>����� ����� �� ��������� </return>
	virtual CString GetTableName() = 0;
	/// <summary> �������� UpdateCounter-� �� ������</summary>
	///<param name="Record"> ���������� �� �����-�</param>
	/// <return> ����� UpdateCounter-� �� ������</return>
	virtual long& GetRecordUpdateCounter(RecordType& Record) = 0;


// Members
// ----------------
protected:
	/// <summary>���� ���������� �������� ��� �����</summary>
	CSession* m_pSession;
	/// <summary>���� ���������� ���� �� ��������� �����</summary>
	BOOL m_bCustomSession;
};