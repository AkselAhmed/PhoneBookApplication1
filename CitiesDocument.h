#pragma once
#include "AutoFreeMemoryArray.h"
#include "Structures.h"
#include "OnUpdateHints.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesDocument

///<summary> Клас документ , който съхранява данните от таблица CITIES</summary>
class CCitiesDocument : public CDocument
{
//Macros
// --------------
protected:
	DECLARE_DYNCREATE(CCitiesDocument)
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CCitiesDocument();
	virtual ~CCitiesDocument();


// Methods
// ----------------
public:
	///<summary> Функция за избор на всички елементи от таблица CITIES</summary>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL PrepareDocumentData();
	///<summary> Функция за избор на елемент по ID от таблица CITIES </summary>
	///<param name="lID"> ID на елемента който искаме да извлечем </param>
	///<param name="recCity"> Записваме селектирания град , първоначално е празен</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL SelectDataWithID(const long lID, CITIES& recCity);
	///<summary> Функция за редакция на елемент от таблица CITIES , записваме новия елемент в recCity</summary>
	///<param name="recCity"> Новите данни с които да заменим старите </param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL UpdateData(CITIES& recCity);
	///<summary> Функция за добавяне на елемент в таблица CITIES </summary>
	///<param name="recCity"> Данните на новия град който искаме да добавим</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL InsertData(CITIES& recCity);
	///<summary> Функция за изтриване на елемент от таблица CITIES</summary>
	///<param name="lID"> ID на елемента който искаме да изтрием</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL DeleteData(const long lID);

	///<summary> Функция която дава достъп до масива за градовете</summary>
	///<returns> Връща константна референция на масива за градове m_oCitiesArray </returns>
	const CCitiesArray& GetCitiesArray() const;



// Overrides
// ----------------
private:
	///<summary> Функция първоначално извикана при създаване на нов документ</summary>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	virtual BOOL OnNewDocument() override;


// Members
// ----------------
private:
	///<summary> Масив за градовете</summary>
	CCitiesArray m_oCitiesArray;
};