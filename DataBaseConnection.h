#pragma once
#include "pch.h"
#include <atldbcli.h>

/////////////////////////////////////////////////////////////////////////////
// CDataBaseConnection

///<summary> Singleton клас за връзка с базата данни</summary>
class CDataBaseConnection 
{

// Constants
// ----------------


// Constructor / Destructor
// ----------------
private:
	///<summary> Конструктор , който създава инстанция на класа ако няма такава и създава връзка към базата данни</summary>
	CDataBaseConnection();
	///<summary> Деструктор , който затваря връзката към базата данни</summary>
	~CDataBaseConnection();
	///<summary>Изтриваме копиращия конструктор</summary>
	CDataBaseConnection(const CDataBaseConnection& obj) = delete;
	///<summary>Изтриваме оператор =</summary>
	CDataBaseConnection& operator=(const CDataBaseConnection&) = delete;


// Methods
// ----------------
public:
	///<summary> Функция която връща инстанция от класа</summary>
	static CDataBaseConnection* GetInstance();
	///<summary> Фунция за достъп до дата сорса</summary>
	///<returns> Връща референция на дата сорса</returns>
	CDataSource& GetDataSource();
	///<summary> Фунция за изтриване на инстанцията</summary>
	void ReleaseInstance();

private:
	///<summary> Инициализация на property-тата на базата данни</summary>
	void DataBaseInitialization(CDBPropSet& oDBPropSet);
	///<summary> Отваряне на връзката с базата данни</summary>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL ConnectToDataBase();
	///<summary> Затваря връзката с базата данни</summary>
	void CloseDataBaseConnection();


// Overrides
// ----------------


// Members
// ----------------
	///<summary> Член променлива от тип CDataSource</summary>
	CDataSource m_oDataSource;
	///<summary> Член променлива указател инстанция към класа</summary>
	static CDataBaseConnection* m_pInstance;
};