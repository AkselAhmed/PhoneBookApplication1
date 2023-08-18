#pragma once
#include "AutoFreeMemoryArray.h"
#include "Structures.h"
#include "OnUpdateHints.h"
#include "PersonsInformation.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsDocument

///<summary> Клас документ , който съхранява данните за хората</summary>
class CPersonsDocument : public CDocument
{
//Macros
// --------------
protected:
	DECLARE_DYNCREATE(CPersonsDocument)
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CPersonsDocument();
	virtual ~CPersonsDocument();


// Methods
// ----------------
public:
	///<summary> Функция за зареждане на масиви за градове , хора и телефонни типове</summary>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL PrepareDocumentData();
	
	///<summary> Функция за зареждане на масива за хора</summary>
	///<param name="oPersonsArray"> Масива в който записваме хората</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL SelectAllPersons(CPersonsArray& oPersonsArray);
	///<summary> Функция за избор на човек и телефонните му номера </summary>
	///<param name="lID"> ИД на елемента който искаме да извлечем </param>
	///<param name="recPerson"> Записваме селектирания човек </param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL SelectDataWithID(const long lID, CPersonInformation& recPersons);
	///<summary> Функция за редакция на човек и телефонните му номера</summary>
	///<param name="recPerson"> Новите данни с които да заменим старите </param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL UpdateData(CPersonInformation& recPerson);
	///<summary> Функция за добавяне на на човек и телефонните му номера</summary>
	///<param name="recPerson"> Данните на новия човек който искаме да добавим</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL InsertData(CPersonInformation& recPerson);
	///<summary> Функция за изтриване на човек и телефонните му номера</summary>
	///<param name="lID"> ИД на елемента който искаме да изтрием</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL DeleteData(const long lID);

	///<summary> Константна функция която дава възможност за достъп до масива за хора</summary>
	///<returns> Връща референция на масива за хора</returns>
	const CPersonsArray& GetDocArray() const;
	///<summary> Константна функция която дава възможност за достъп до масива за градове</summary>
	///<returns> Връща референция на масива за градове</returns>
	const CCitiesArray& GetDocCitiesArray() const;
	///<summary> Константна функция която дава възможност за достъп до масива за телефонни типове</summary>
	///<returns> Връща референция на масива за телефонни типове</returns>
	const CPhoneTypesArray& GetDocPhoneTypesArray() const;


// Overrides
// ----------------
private:
	///<summary> Функция първоначално извикана при създаване на нов документ</summary>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	virtual BOOL OnNewDocument() override;


// Members
// ----------------
private:
	///<summary> Член променлива масив за хора</summary>
	CPersonsArray m_oPersonsArray;
	///<summary> Член променлива масив за градове</summary>
	CCitiesArray m_oCitiesArray;
	///<summary> Член променлива масив за типове телефони</summary>
	CPhoneTypesArray m_oPhoneTypesArray;
};