#pragma once

#define CITY_COLUMN_INDEX 0
#define DISTRICT_COLUMN_INDEX 1
#define CITY_COLUMN_NAME _T("����")
#define DISTRICT_COLUMN_NAME _T("������")
#define CITY_COLUMN_SIZE 150
#define DISTRICT_COLUMN_SIZE 150
#define ERROR_SAVING_CITY_MESSAGE _T("��������� ��������� �� �����.")
#define ERROR_SAVING_DISTRICT_MESSAGE _T("��������� ��������� �� ��������.")


/////////////////////////////////////////////////////////////////////////////
// CCitiesView

///<summary> ���� View �� ��������� , ����� �� ����� �� ��������� �� ������ </summary>
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
	///<summary> ������� , ����� ���� ���������� �� ������ �� ���������</summary>
	///<returns> ����� ����� �������� �� ����� CCitiesDocument </returns>
	CCitiesDocument* GetDocument() const;

	///<summary> ������� �� ������� �� ���� �� ���������� ����</summary>
	afx_msg void SelectCity();
	///<summary> ������� �� ����������� �� ���� �� ���������� ����</summary>
	afx_msg void UpdateCity();
	///<summary> ������� �� �������� �� ���� �� ���������� ����</summary>
	afx_msg void InsertCity();
	///<summary> ������� �� ��������� �� ���� �� ���������� ����</summary>
	afx_msg void DeleteCity();
	///<summary> ������� �� ������������ �� ��������� �� ���������� ����</summary>
	afx_msg void RefreshCities();

	///<summary> ������� �� �������� �� ���� ��  ���� ����������</summary>
	///<param name="recCity">�������� ���� �� �� ����� �� �� ������� ��� view-��</param>
	afx_msg void UpdateInView(const CITIES& recCity);
	///<summary> ������� �� �������� �� ���� � ���� ����������</summary>
	///<param name="recCity">�������� ���� �� �� ����� �� �� ������� ��� view-��</param>
	afx_msg void InsertInView(const CITIES& recCity);
	///<summary> ������� �� ��������� �� ���� �� ���� ����������</summary>
	///<param name="recCity">�������� ���� �� �� ����� �� �� ������� ��� view-��</param>
	afx_msg void DeleteInView(const CITIES& recCity);
	///<summary> ������� �� ������� �� �������� ���� �� view-��</summary>
	///<param name="recCity"> ����������� �������� ����</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	afx_msg BOOL GetSelectedCityInListCtrl(CITIES& recCity);

protected:
	///<summary> ������� ����� �� ���� ��� ������� �� ������ �����</summary>
	///<param name="point"> ������������ �� ����-�</param>
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	///<summary> ������� ����� ������� ������������ ���� ��� ����� �����</summary>
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	///<summary> ������� ����� �� ���� ��� ����� ����</summary>
	afx_msg void OnItemDoubleClick(NMHDR* pNMHDR, LRESULT* pResult);

	///<summary> ������� ����� ������������ ���� ���������� � �������� �</summary>
	///<param name="oListCtrl"> ���������� �� ���� ����������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL InitializeListControl(CListCtrl& oListCtrl);
	///<summary> ������� ����� ����� ���� ���������� � ��������</summary>
	///<param name="oListCtrl"> ���������� �� ���� ����������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL AddItemsToListControl(CListCtrl& oListCtrl);


// Overrides
// ----------------
protected:
	///<summary> ������� ����� �� ���� ��� ���������� �� ������������</summary>
	virtual void OnInitialUpdate() override;
	///<summary> ������� ����� ����� ������ �� ������������ ����</summary>
	afx_msg BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	///<summary> ������� ����� �� ���� �� ����� View ���� UpdateAllViews</summary>
	afx_msg void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;


// Members
// ----------------
};
