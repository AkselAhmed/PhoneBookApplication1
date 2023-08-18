#pragma once
#include "Structures.h"
#include "DialogModes.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesDialog

///<summary> ���� �� ������� �� ���������</summary>
class CCitiesDialog : public CDialogEx
{
// Macros
// ----------------
	DECLARE_DYNAMIC(CCitiesDialog)

protected:
	DECLARE_MESSAGE_MAP()

	enum { IDD = IDD_DLG_CITIES };


// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	///<summary> �����������</summary>
	///<param name="recCity"> ����� �� ��������� CITIES ����� ����� �� ����������</param>
	///<param name="oReadWriteEnum"> ��������� ���� ������ �� ������� ������� � ReadWrite/ReadOnly</param>
	CCitiesDialog(CITIES& recCity , DialogModes eDialogModes = DialogModeReadWrite , CWnd* pParent = nullptr);
	virtual ~CCitiesDialog();


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
	///<summary> ������� ����� ��������� ���� ���������� � ���� ���������� �� �������</summary>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL CheckIsWindowTextValid();
	///<summary> ������� , ����� ������� ������� �� ���� ���������� � ������</summary>
	void SaveDataInBuffer();


// Members
// ----------------
private:
	///<summary> ���� ���������� ���� �������� �� ����� �� �����</summary>
	CEdit m_edbCityName;
	///<summary> ���� ���������� ���� �������� �� ��������</summary>
	CEdit m_edbDistrict;
	///<summary> ���� ���������� ���������� ��� ��������� �� ����</summary>
	CITIES& m_recCity;
	///<summary> ���� ����������(����������) ���� �� ��������� ���� � �������� ���� �� ������</summary>
	DialogModes m_eDialogModes;
	///<summary> ���� ���������� �� ����� ��</summary>
	CButton m_btnOK;
};