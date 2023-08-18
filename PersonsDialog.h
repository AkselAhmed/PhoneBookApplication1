#pragma once
#include "Structures.h"
#include "DialogModes.h"
#include "PersonsInformation.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsDialog

///<summary> ���� �� ������� �� ������</summary>
class CPersonsDialog : public CDialogEx
{
// Macros
// ----------------
	DECLARE_DYNAMIC(CPersonsDialog)
protected:
	DECLARE_MESSAGE_MAP()

	enum { IDD = IDD_DLG_PERSONS };


// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	///<summary> ����������� ����� ������ � ���������� ����������</summary>
	///<param name="oPersonsInformation">���������� �� ������ � ����������� �� ������</param>
	///<param name="eDialogModes">���� �� ������ / ������ � �����</param>
	CPersonsDialog(CPersonInformation& oPersonsInformation, DialogModes eDialogModes = DialogModeReadWrite, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPersonsDialog();


// MFC Overrides
// ----------------
protected:
	///<summary> ������� �� ������ �� �����</summary>
	virtual void DoDataExchange(CDataExchange* pDX) override;
	///<summary> ������� ����� �� ���� ��� ������������ ��������� �� �������</summary>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	virtual BOOL OnInitDialog() override;
	///<summary> ������� ����� �� ���� ��� ��������� �� ������ ��</summary>
	afx_msg void OnOK() override;


// MFC Message Handlers
// ----------------
protected:
	///<summary> ������� �� ��������� �� ���������� ����</summary>
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);


// Overrides
// ----------------
	///<summary> ������� ����� �������� ��� ��������� �� ������ �������</summary>
	afx_msg BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;


// Methods
// ----------------
private:
	///<summary> ������� ����� ��������� ���� ������ � ���� ���������� �� �������</summary>
	///<returns> ����� TRUE ��� �� � FALSE ��� �� ��</returns>
	BOOL CheckIsWindowTextValid();
	///<summary> ������� , ����� ������� ������� �� ���� ���������� � ������</summary>
	void SaveDataInBuffer();
	///<summary> ������� ����� ������ ������� �� ��������� ������ �� �������� �� ��������� �����</summary>
	void InsertPhoneNumber();
	///<summary> ������� ����� ������ ������� �� ��������� ������ �� ����������� �� ��������� �����</summary>
	void UpdatePhoneNumber();
	///<summary> ������� �� ��������� �� ��������� �����</summary>
	void DeletePhoneNumber();

public:
	///<summary> ������� �� ��������� �� ������ � �������</summary>
	///<param name="oCitiesArray"> ������ �� ����� �� ������ �����</param>
	void FillCitiesArray(const CCitiesArray& oCitiesArray);
	///<summary> ������� �� ��������� �� ������ � ��������� ������</summary>
	///<param name="oPhoneTypesArray"> ������ �� ����� �� ������ �����</param>
	void FillPhoneTypesArray(const CPhoneTypesArray& oPhoneTypesArray);


// Members
// ----------------
private:
	///<summary> ���� ���������� ���� �������� �� ���</summary>
	CEdit m_edbPersonsFirstName;
	///<summary> ���� ���������� ���� �������� �� �����</summary>
	CEdit m_edbPersonsAddress;
	///<summary> ���� ���������� �� ��� ����������� ���� �� ������ � ����������� �� ������</summary>
	CPersonInformation& m_oPersonsInformation;
	///<summary> ���� ���������� enum �� ������������ ���� ������� � ������� �� ������</summary>
	DialogModes m_eDialogModes;
	///<summary> ���� ���������� ���� �������� �� �������</summary>
	CEdit m_edbPersonsSecondName;
	///<summary> ���� ���������� ���� �������� �� �������</summary>
	CEdit m_edbPersonsThirdName;
	///<summary> ���� ���������� ���� �������� �� ���</summary>
	CEdit m_edbPersonsEgn;
	///<summary> ���� ���������� ����� ���� �� ����</summary>
	CComboBox m_cmbPersonsCity;
	///<summary> ���� ���������� ����� �� ���������</summary>
	CCitiesArray m_oCitiesArray;
	///<summary> ���� ���������� �� ����� ��</summary>
	CButton m_btnOK;
	///<summary> ���� ���������� listbox �� ����������� ������ �� �����</summary>
	CListBox m_lsbPersonsPhoneNumbers;
	///<summary> ���� ���������� ����� �� ����������� ������</summary>
	CPhoneTypesArray m_oPhoneTypesArray;
};
