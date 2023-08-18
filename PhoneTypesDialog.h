#pragma once
#include "Structures.h"
#include "DialogModes.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDialog

///<summary> ���� �� ������� �� �������� ��������</summary>
class CPhoneTypesDialog : public CDialogEx
{
// Macros
// ----------------
	DECLARE_DYNAMIC(CPhoneTypesDialog)

protected:
	DECLARE_MESSAGE_MAP()

	enum { IDD = IDD_DLG_PHONE_TYPES };


// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	///<summary> �����������</summary>
	///<param name="recPhoneType"> ����� �� ��������� PHONE_TYPES ����� ����� �� ����������</param>
	///<param name="oReadWriteEnum"> ��������� ���� ������ �� ������� ������� � ReadWrite/ReadOnly</param>
	CPhoneTypesDialog(PHONE_TYPES& recPhoneType, DialogModes eDialogModes = DialogModeReadWrite, CWnd* pParent = nullptr);
	virtual ~CPhoneTypesDialog();


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
	///<summary> ������� ����� ��������� ���� ������ � ���� ���������� �� �������</summary>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL CheckIsWindowTextValid();
	///<summary> ������� , ����� ������� ������� �� ���� ���������� � ������</summary>
	void SaveDataInBuffer();


// Members
// ----------------
private:
	///<summary> ���� ���������� ���� �������� �� ���������� ���</summary>
	CEdit m_edbPhoneTypesPhoneType;
	///<summary> ���� ���������� �� ��� ��������� PHONE_TYPES</summary>
	PHONE_TYPES& m_recPhoneType;
	///<summary> ���� ����������(����������) ���� �� ��������� ���� � �������� ���� �� ������</summary>
	DialogModes m_eDialogModes;
	///<summary> ���� ���������� �� ����� ��</summary>
	CButton m_btnOK;
};