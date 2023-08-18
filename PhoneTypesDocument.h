#pragma once
#include "AutoFreeMemoryArray.h"
#include "Structures.h"
#include "OnUpdateHints.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDocument

///<summary> Клас документ за връзка с дата класа</summary>
class CPhoneTypesDocument : public CDocument
{
//Macros
// --------------
protected:
	DECLARE_DYNCREATE(CPhoneTypesDocument)
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CPhoneTypesDocument();
	virtual ~CPhoneTypesDocument();


// Methods
// ----------------
public:
	///<summary> Функция за зареждане на масивa за телефонни типове</summary>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL PrepareDocumentData();
	///<summary> Функция за избор на телефонен тип от базата</summary>
	///<param name="lID"> ИД на телефонния тип който искаме да извлечем </param>
	///<param name="recPhoneType"> Записваме селектирания телефонен тип </param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL SelectDataWithID(const long lID, PHONE_TYPES& recPhoneType);
	///<summary> Функция за редакция на на телефонен тип от базата</summary>
	///<param name="lID"> ИД на телефонния тип който искаме да редактираме</param>
	///<param name="recPhoneType"> Новите данни с които да заменим старите </param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL UpdateData(PHONE_TYPES& recPhoneType);
	///<summary> Функция за добавяне на телефонен тип в базата</summary>
	///<param name="recPhoneType"> Данните на новия телефонен тип който искаме да добавим</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL InsertData(PHONE_TYPES& recPhoneType);
	///<summary> Функция за изтриване на телефонен тип от базата</summary>
	///<param name="lID"> ИД на телефонния тип който искаме да изтрием</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL DeleteData(const long lID);

	///<summary> Константна функция която дава възможност за достъп до масива за телефонни типове</summary>
	///<returns> Връща референция на масива за телефонни типове</returns>
	const CPhoneTypesArray& GetDocArray() const;


// Overrides
// ----------------
private:
	///<summary> Функция първоначално извикана при създаване на нов документ</summary>
	virtual BOOL OnNewDocument() override;


// Members
// ----------------
private:
	///<summary> Член променлива масив за типовете телефони</summary>
	CPhoneTypesArray m_oPhoneTypesArray;
};