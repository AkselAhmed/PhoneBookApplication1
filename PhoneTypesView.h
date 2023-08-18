#pragma once
#define MAKE_READ_ONLY_DIALOG TRUE

#include "PhoneTypesDocument.h"

#define PHONE_TYPE_COLUMN_INDEX 0
#define PHONE_TYPE_COLUMN_NAME _T("��� �������")
#define PHONE_TYPE_COLUMN_SIZE 150


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesView

///<summary> ���� View �� ������� PHONE_TYPES</summary>
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
	///<summary> ������� , ����� ���� ���������� �� ������ �� ���������</summary>
	///<returns> ����� ����� �������� �� ����� CPhoneTypesDocument </returns>
	CPhoneTypesDocument* GetDocument() const;

	///<summary> ������� �� ������� �� ��������� ��� �� ���������� ����</summary>
	afx_msg void SelectPhoneType();
	///<summary> ������� �� ����������� �� ��������� ��� �� ���������� ����</summary>
	afx_msg void UpdatePhoneType();
	///<summary> ������� �� �������� �� ��������� ��� �� ���������� ����</summary>
	afx_msg void InsertPhoneType();
	///<summary> ������� �� ��������� �� ��������� ��� �� ���������� ����</summary>
	afx_msg void DeletePhoneType();
	///<summary> ������� �� ������������ �� ��������� �������� �� ���������� ����</summary>
	afx_msg void RefreshPhoneTypes();

	///<summary> ������� �� �������� �� ��������� ��� ��  ���� ����������</summary>
	///<param name="recPhoneType">�������� ��������� ��� �� �� ����� �� �� ������� ��� view-��</param>
	afx_msg void UpdateInView(const PHONE_TYPES& recPhoneType);
	///<summary> ������� �� �������� �� ��������� ��� � ���� ����������</summary>
	///<param name="recPhoneType">�������� ��������� ��� �� �� ����� �� �� ������� ��� view-��</param>
	afx_msg void InsertInView(const PHONE_TYPES& recPhoneType);
	///<summary> ������� �� ��������� �� ��������� ��� �� ���� ����������</summary>
	///<param name="recPhoneType">�������� ��������� ��� �� �� ����� �� �� ������� ��� view-��</param>
	afx_msg void DeleteInView(const PHONE_TYPES& recPhoneType);
	///<summary> ������� �� ������� �� �������� ��������� ��� �� view-��</summary>
	///<param name="recPhoneType">����������� �������� ��������� ���</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	afx_msg BOOL GetSelectedPhoneTypeInListCtrl(PHONE_TYPES& recPhoneType);

protected:
	///<summary> ������� ����� �� ���� ��� ������� �� ������ �����</summary>
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	///<summary> ������� ����� ������� ������������ ���� ��� ����� �����</summary>
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	///<summary> ������� ����� �� ���� ��� ����� ����</summary>
	afx_msg void OnItemDoubleClick(NMHDR* pNMHDR, LRESULT* pResult);

	///<summary> ������� ����� ������������ ���� ���������� � �������� �</summary>
	///<param name="oListCtrl"> ���������� �� ���� ����������</param>
	void InitializeListControl(CListCtrl& oListCtrl);
	///<summary> ������� ����� ����� ���� ���������� � ��������</summary>
	///<param name="oListCtrl"> ���������� �� ���� ����������</param>
	void AddItemsToListControl(CListCtrl& oListCtrl);


// Overrides
// ----------------
protected:
	///<summary> ������� ����� �� ���� ��� ���������� �� ������������</summary>
	virtual void OnInitialUpdate() override;
	///<summary> ������� ����� ����� ��������� ������ �� ������������ ����</summary>
	afx_msg BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	///<summary> ������� ����� �� ���� �� ����� View ���� UpdateAllViews</summary>
	afx_msg void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;


// Members
// ----------------
};

