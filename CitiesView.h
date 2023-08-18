#pragma once

#define CITY_COLUMN_INDEX 0
#define DISTRICT_COLUMN_INDEX 1
#define CITY_COLUMN_NAME _T("Град")
#define DISTRICT_COLUMN_NAME _T("Област")
#define CITY_COLUMN_SIZE 150
#define DISTRICT_COLUMN_SIZE 150
#define ERROR_SAVING_CITY_MESSAGE _T("Неуспешно записване на града.")
#define ERROR_SAVING_DISTRICT_MESSAGE _T("Неуспешно записване на областта.")


/////////////////////////////////////////////////////////////////////////////
// CCitiesView

///<summary> Клас View за градовете , който се грижи за промените по екрана </summary>
class CCitiesView : public CListView
{
//Macros
// --------------
protected:
	DECLARE_DYNCREATE(CCitiesView)
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
	CCitiesView();
	virtual ~CCitiesView();


// Methods
// ----------------
private:
	///<summary> Функция , която дава възможност за достъп до документа</summary>
	///<returns> Връща обект указател от класа CCitiesDocument </returns>
	CCitiesDocument* GetDocument() const;

	///<summary> Функция за преглед на град от контекстно меню</summary>
	afx_msg void SelectCity();
	///<summary> Функция за редактиране на град от контекстно меню</summary>
	afx_msg void UpdateCity();
	///<summary> Функция за добавяне на град от контекстно меню</summary>
	afx_msg void InsertCity();
	///<summary> Функция за изтриване на град от контекстно меню</summary>
	afx_msg void DeleteCity();
	///<summary> Функция за презареждане на градвоете от контекстно меню</summary>
	afx_msg void RefreshCities();

	///<summary> Функция за редакция на град от  лист контролата</summary>
	///<param name="recCity">Подаваме град за да можем да го намерим във view-то</param>
	afx_msg void UpdateInView(const CITIES& recCity);
	///<summary> Функция за вмъкване на град в лист контролата</summary>
	///<param name="recCity">Подаваме град за да можем да го намерим във view-то</param>
	afx_msg void InsertInView(const CITIES& recCity);
	///<summary> Функция за изтриване на град от лист контролата</summary>
	///<param name="recCity">Подаваме град за да можем да го намерим във view-то</param>
	afx_msg void DeleteInView(const CITIES& recCity);
	///<summary> Функция за вземане на избрания град от view-то</summary>
	///<param name="recCity"> Присвояваме избрания град</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	afx_msg BOOL GetSelectedCityInListCtrl(CITIES& recCity);

protected:
	///<summary> Функция която се вика при пускане на десния бутон</summary>
	///<param name="point"> Координатите на клик-а</param>
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	///<summary> Функция която създава контекстното меню при десен бутон</summary>
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	///<summary> Функция която се вика при двоен клик</summary>
	afx_msg void OnItemDoubleClick(NMHDR* pNMHDR, LRESULT* pResult);

	///<summary> Функция която инициализира лист контролата и колоните й</summary>
	///<param name="oListCtrl"> Референция на лист контролата</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL InitializeListControl(CListCtrl& oListCtrl);
	///<summary> Функция която пълни лист контролата с елементи</summary>
	///<param name="oListCtrl"> Референция на лист контролата</param>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL AddItemsToListControl(CListCtrl& oListCtrl);


// Overrides
// ----------------
protected:
	///<summary> Функция която се вика при стартиране на приложението</summary>
	virtual void OnInitialUpdate() override;
	///<summary> Функция която взема избора от контекстното меню</summary>
	afx_msg BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	///<summary> Функция която се вика на всяко View след UpdateAllViews</summary>
	afx_msg void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;


// Members
// ----------------
};
