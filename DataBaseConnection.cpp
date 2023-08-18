#include "pch.h"
#include "DataBaseConnection.h"


/////////////////////////////////////////////////////////////////////////////
// CDataBaseConnection


// Constructor / Destructor
// ----------------
CDataBaseConnection::CDataBaseConnection()
{
	// Първоначална инициализация
	HRESULT hr = ::CoInitialize(nullptr);

	// Създаваме връзка с базата данни
	ConnectToDataBase();
}

CDataBaseConnection::~CDataBaseConnection()
{
	// Затваряме връзката с базата данни
	CloseDataBaseConnection();
}


// Methods
// ----------------

CDataBaseConnection* CDataBaseConnection::GetInstance()
{
	// Ако не съществува инстанция от класа я създаваме
	if (m_pInstance == NULL)
	{
		m_pInstance = new CDataBaseConnection();
	}

	return m_pInstance;
}

BOOL CDataBaseConnection::ConnectToDataBase()
{
	// Създаваме връзка с базата данни
	m_oDataSource.Close();
	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	DataBaseInitialization(oDBPropSet);

	HRESULT hResult = m_oDataSource.Open(_T("SQLOLEDB.1"), &oDBPropSet);
	if (FAILED(hResult))
	{
		CString strMessage;
		strMessage.Format(_T("Unable to connect to SQL Server database. Error: %d"), hResult);
		AfxMessageBox(strMessage);

		return FALSE;
	}

	return TRUE;
}

CDataSource& CDataBaseConnection::GetDataSource()
{
	return m_oDataSource;
}

void CDataBaseConnection::ReleaseInstance()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void CDataBaseConnection::CloseDataBaseConnection()
{
	m_oDataSource.Close();
}

void CDataBaseConnection::DataBaseInitialization(CDBPropSet& oDBPropSet)
{
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-KT67I92"));
	oDBPropSet.AddProperty(DBPROP_AUTH_USERID, _T("aksel"));
	oDBPropSet.AddProperty(DBPROP_AUTH_PASSWORD, _T("123"));
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("Internship"));
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));
}


// Overrides
// ----------------