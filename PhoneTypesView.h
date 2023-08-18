#pragma once
#define MAKE_READ_ONLY_DIALOG TRUE

#include "PhoneTypesDocument.h"

#define PHONE_TYPE_COLUMN_INDEX 0
#define PHONE_TYPE_COLUMN_NAME _T("Тип телефон")
#define PHONE_TYPE_COLUMN_SIZE 150


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesView

///<summary> Клас View за талбица PHONE_TYPES</summary>
class CPhoneTypesView : public CListView
{
//Macros
// --------------
protected:
	DECLARE_DYNCREATE(CPhoneTypesView)
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------
private:
	static const LPCTSTR lpszDeleteMessage;
	static const LPCTSTR lpszMessage;
	static const LPCTSTR lpszConfirmation;
	static const LPCTSTR lpszConfirmationMessage;
	static const LPCTSTR lpszMenuView;
	static const LPCTSTR lpszMenuInsert;
	static const LPCTSTR lpszMenuUpdate;
	static const LPCTSTR lpszMenuDelete;
	static const LPCTSTR lpszMenuRefresh;


// Constructor / Destructor
// ----------------
public:
	CPhoneTypesView();
	virtual ~CPhoneTypesView();


// Methods
// ----------------
private:
	///<summary> Функция , която дава възможност за достъп до документа</summary>
	///<returns> Връща обект указател от класа CPhoneTypesDocument </returns>
	CPhoneTypesDocument* GetDocument() const;

	///<summary> Функция за преглед на телефонен тип от контекстно меню</summary>
	afx_msg void SelectPhoneType();
	///<summary> Функция за редактиране на телефонен тип от контекстно меню</summary>
	afx_msg void UpdatePhoneType();
	///<summary> Функция за добавяне на телефонен тип от контекстно меню</summary>
	afx_msg void InsertPhoneType();
	///<summary> Функция за изтриване на телефонен тип от контекстно меню</summary>
	afx_msg void DeletePhoneType();
	///<summary> Функция за презареждане на телефонен типвоете от контекстно меню</summary>
	afx_msg void RefreshPhoneTypes();

	///<summary> Функция за редакция на телефонен тип от  лист контролата</summary>
	///<param name="recPhoneType">Подаваме телефонен тип за да можем да го намерим във view-то</param>
	afx_msg void UpdateInView(const PHONE_TYPES& recPhoneType);
	///<summary> Функция за вмъкване на телефонен тип в лист контролата</summary>
	///<param name="recPhoneType">Подаваме телефонен тип за да можем да го намерим във view-то</param>
	afx_msg void InsertInView(const PHONE_TYPES& recPhoneType);
	///<summary> Функция за изтриване на телефонен тип от лист контролата</summary>
	///<param name="recPhoneType">Подаваме телефонен тип за да можем да го намерим във view-то</param>
	afx_msg void DeleteInView(const PHONE_TYPES& recPhoneType);
	///<summary> Функция за вземане на избрания телефонен тип от view-то</summary>
	///<param name="recPhoneType">Присвояваме избрания телефонен тип</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	afx_msg BOOL GetSelectedPhoneTypeInListCtrl(PHONE_TYPES& recPhoneType);

protected:
	///<summary> Функция която се вика при пускане на десния бутон</summary>
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	///<summary> Функция която създава контекстното меню при десен бутон</summary>
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	///<summary> Функция която се вика при двоен клик</summary>
	afx_msg void OnItemDoubleClick(NMHDR* pNMHDR, LRESULT* pResult);

	///<summary> Функция която инициализира лист контролата и колоните й</summary>
	///<param name="oListCtrl"> Референция на лист контролата</param>
	void InitializeListControl(CListCtrl& oListCtrl);
	///<summary> Функция която пълни лист контролата с елементи</summary>
	///<param name="oListCtrl"> Референция на лист контролата</param>
	void AddItemsToListControl(CListCtrl& oListCtrl);


// Overrides
// ----------------
protected:
	///<summary> Функция която се вика при стартиране на приложението</summary>
	virtual void OnInitialUpdate() override;
	///<summary> Функция която взема параметър избора от контекстното меню</summary>
	afx_msg BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	///<summary> Функция която се вика на всяко View след UpdateAllViews</summary>
	afx_msg void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;


// Members
// ----------------
};

