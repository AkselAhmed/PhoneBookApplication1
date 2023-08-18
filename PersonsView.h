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
	///<summary> ������� , ����� ���� ���������� �� ������ �� ���������</summary>
	///<returns> ����� ����� �������� �� ����� CPersonsDocument </returns>
	CPersonsDocument* GetDocument() const;

	///<summary> ������� �� ������� �� ����� �� ���������� ����</summary>
	afx_msg void SelectPerson();
	///<summary> ������� �� ����������� �� ����� �� ���������� ����</summary>
	afx_msg void UpdatePerson();
	///<summary> ������� �� �������� �� ����� �� ���������� ����</summary>
	afx_msg void InsertPerson();
	///<summary> ������� �� ��������� �� ����� �� ���������� ����</summary>
	afx_msg void DeletePerson();
	///<summary> ������� �� ������������ �� ������ �� ���������� ����</summary>
	afx_msg void RefreshPersons();

	///<summary> ������� �� �������� �� ����� ��  ���� ����������</summary>
	///<param name="recPerson">�������� ����� �� �� ����� �� �� ������� ��� view-��</param>
	afx_msg void UpdateInView(const PERSONS& recPerson);
	///<summary> ������� �� �������� �� ����� � ���� ����������</summary>
	///<param name="recPerson">�������� ����� �� �� ����� �� �� ������� ��� view-��</param>
	afx_msg void InsertInView(const PERSONS& recPerson);
	///<summary> ������� �� ��������� �� ����� �� ���� ����������</summary>
	///<param name="recPerson">�������� ����� �� �� ����� �� �� ������� ��� view-��</param>
	afx_msg void DeleteInView(const PERSONS& recPerson);
	///<summary> ������� �� ������� �� �������� ����� �� view-��</summary>
	///<param name="recPerson">����������� �������� �����</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	afx_msg BOOL GetSelectedPersonInListCtrl(CPersonInformation& recPerson);

protected:
	///<summary> ������� ����� �� ���� ��� ������� �� ������ �����</summary>
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	///<summary> ������� ����� ������� ������������ ���� ��� ����� �����</summary>
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	///<summary> ������� ����� �� ���� ��� ����� ����</summary>
	afx_msg void OnItemDoubleClick(NMHDR* pNMHDR, LRESULT* pResult);

	///<summary> ������� ����� ������������ ���� ���������� � �������� �</summary>
	void InitializeListControl(CListCtrl& oListCtrl);
	///<summary> ������� ����� ����� ���� ���������� � ��������</summary>
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
