#pragma once

#include "PersonsDocument.h"
#include "PersonsInformation.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsView

class CPersonsView : public CListView
{
//Macros
// --------------
protected:
	DECLARE_DYNCREATE(CPersonsView)
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
	CPersonsView();
	virtual ~CPersonsView();


// Methods
// ----------------
private:
	///<summary> Функция , която дава възможност за достъп до документа</summary>
	///<returns> Връща обект указател от класа CPersonsDocument </returns>
	CPersonsDocument* GetDocument() const;

	///<summary> Функция за преглед на човек от контекстно меню</summary>
	afx_msg void SelectPerson();
	///<summary> Функция за редактиране на човек от контекстно меню</summary>
	afx_msg void UpdatePerson();
	///<summary> Функция за добавяне на човек от контекстно меню</summary>
	afx_msg void InsertPerson();
	///<summary> Функция за изтриване на човек от контекстно меню</summary>
	afx_msg void DeletePerson();
	///<summary> Функция за презареждане на хората от контекстно меню</summary>
	afx_msg void RefreshPersons();

	///<summary> Функция за редакция на човек от  лист контролата</summary>
	///<param name="recPerson">Подаваме човек за да можем да го намерим във view-то</param>
	afx_msg void UpdateInView(const PERSONS& recPerson);
	///<summary> Функция за вмъкване на човек в лист контролата</summary>
	///<param name="recPerson">Подаваме човек за да можем да го намерим във view-то</param>
	afx_msg void InsertInView(const PERSONS& recPerson);
	///<summary> Функция за изтриване на човек от лист контролата</summary>
	///<param name="recPerson">Подаваме човек за да можем да го намерим във view-то</param>
	afx_msg void DeleteInView(const PERSONS& recPerson);
	///<summary> Функция за вземане на избрания човек от view-то</summary>
	///<param name="recPerson">Присвояваме избрания човек</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	afx_msg BOOL GetSelectedPersonInListCtrl(CPersonInformation& recPerson);

protected:
	///<summary> Функция която се вика при пускане на десния бутон</summary>
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	///<summary> Функция която създава контекстното меню при десен бутон</summary>
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	///<summary> Функция която се вика при двоен клик</summary>
	afx_msg void OnItemDoubleClick(NMHDR* pNMHDR, LRESULT* pResult);

	///<summary> Функция която инициализира лист контролата и колоните й</summary>
	void InitializeListControl(CListCtrl& oListCtrl);
	///<summary> Функция която пълни лист контролата с елементи</summary>
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
