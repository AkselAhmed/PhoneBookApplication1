#pragma once
#include "pch.h"
#include <atldbcli.h>

/////////////////////////////////////////////////////////////////////////////
// CDataBaseConnection

///<summary> Singleton ���� �� ������ � ������ �����</summary>
class CDataBaseConnection 
{

// Constants
// ----------------


// Constructor / Destructor
// ----------------
private:
	///<summary> ����������� , ����� ������� ��������� �� ����� ��� ���� ������ � ������� ������ ��� ������ �����</summary>
	CDataBaseConnection();
	///<summary> ���������� , ����� ������� �������� ��� ������ �����</summary>
	~CDataBaseConnection();
	///<summary>��������� ��������� �����������</summary>
	CDataBaseConnection(const CDataBaseConnection& obj) = delete;
	///<summary>��������� �������� =</summary>
	CDataBaseConnection& operator=(const CDataBaseConnection&) = delete;


// Methods
// ----------------
public:
	///<summary> ������� ����� ����� ��������� �� �����</summary>
	static CDataBaseConnection* GetInstance();
	///<summary> ������ �� ������ �� ���� �����</summary>
	///<returns> ����� ���������� �� ���� �����</returns>
	CDataSource& GetDataSource();
	///<summary> ������ �� ��������� �� �����������</summary>
	void ReleaseInstance();

private:
	///<summary> ������������� �� property-���� �� ������ �����</summary>
	void DataBaseInitialization(CDBPropSet& oDBPropSet);
	///<summary> �������� �� �������� � ������ �����</summary>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL ConnectToDataBase();
	///<summary> ������� �������� � ������ �����</summary>
	void CloseDataBaseConnection();


// Overrides
// ----------------


// Members
// ----------------
	///<summary> ���� ���������� �� ��� CDataSource</summary>
	CDataSource m_oDataSource;
	///<summary> ���� ���������� �������� ��������� ��� �����</summary>
	static CDataBaseConnection* m_pInstance;
};