#pragma once

#include "Structures.h"
#include "PersonsInformation.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersDialog

class CPhoneNumbersDialog : public CDialogEx
{
// Macros
// ----------------
	DECLARE_DYNAMIC(CPhoneNumbersDialog)
	DECLARE_MESSAGE_MAP()

	enum { IDD = IDD_DLG_PHONE_NUMBERS };


// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	///<summary> ����������� ����� ������ ���������� �� ������</summary>
	CPhoneNumbersDialog(PHONE_NUMBERS& recPhoneNumber , CWnd* pParent = nullptr);
	virtual ~CPhoneNumbersDialog();


// MFC Overrides
// ----------------
protected:
	///<summary> ������� �� ������ �� �����</summary>
	virtual void DoDataExchange(CDataExchange* pDX) override;
	///<summary> ������� ����� �� ���� ��� ������������ ��������� �� �������</summary>
	virtual BOOL OnInitDialog() override;
	///<summary> ������� ����� �� ���� ��� ��������� �� ������ ��</summary>
	afx_msg void OnOK() override;


// MFC Message Handlers
// ----------------


// Overrides
// ----------------


// Methods
// ----------------
private:
	///<summary> ������� ����� ��������� ���� ���������� � ������� �� �������</summary>
	///<returns> ����� TRUE ��� �� � FALSE ��� �� �� </returns>
	BOOL CheckIsWindowTextValid();
	///<summary> ������� , ����� ������� ������� �� ������� � ������</summary>
	void SaveDataInBuffer();

public:
	///<summary> ������� �� ��������� �� ������ � ��������� ������</summary>
	///<param name="oPhoneTypesArray"> ������ �� ����� �� ������ �����</param>
	void FillPhoneTypesArray(const CPhoneTypesArray& oPhoneTypesArray);


// Members
// ----------------
private:
	///<summary> ���� ���������� ���������� �� ���������� �����</summary>
	PHONE_NUMBERS& m_recPhoneNumber;
	///<summary> ���� ���������� �� ���� �������� �� ��������� �����</summary>
	CEdit m_edbPhoneNumbersPhoneNumber;
	///<summary> ���� ���������� ����� �� ��������� ������</summary>
	CPhoneTypesArray m_oPhoneTypesArray;
	///<summary> ���� ���������� ����� ���� �� ��������� ���</summary>
	CComboBox m_cmbPhoneTypesType;
};
