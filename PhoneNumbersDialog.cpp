#include "pch.h"
#include "PhoneBook.h"
#include "PhoneNumbersDialog.h"
#include "afxdialogex.h"
#include <regex>

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersDialog

#define PHONE_MIN_SIZE_MESSAGE L"���� ��������� ��������� ����� �� � � ������ �� 5 �������."
#define MESSAGE L"���������."
#define PHONE_TYPE_MISSING_MESSAGE L"���� �������� ��� �� ���������� �����."

#define PHONE_NUMBER_MIN_SIZE 5


// Macros
// ----------------
IMPLEMENT_DYNAMIC(CPhoneNumbersDialog, CDialogEx)

BEGIN_MESSAGE_MAP(CPhoneNumbersDialog, CDialogEx)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------
CPhoneNumbersDialog::CPhoneNumbersDialog(PHONE_NUMBERS& recPhoneNumber, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_PHONE_NUMBERS, pParent), m_recPhoneNumber(recPhoneNumber)
{
}

CPhoneNumbersDialog::~CPhoneNumbersDialog()
{
}


// MFC Overrides
// ----------------
BOOL CPhoneNumbersDialog::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	// �������� ������������ �������� �� ���� ���������� �������� ��������� �����
	m_edbPhoneNumbersPhoneNumber.SetWindowText(m_recPhoneNumber.szPhone);

	int nSelectIndex = CB_ERR;
	// ��������� ������ � ��������� ������ � �� ��������� � ���� ����������
	for (INT_PTR nIndex = 0; nIndex < m_oPhoneTypesArray.GetCount(); nIndex++)
	{
		PHONE_TYPES* pPhoneType = m_oPhoneTypesArray.GetAt(nIndex);
		if (pPhoneType == nullptr)
			return FALSE;

		// ��� ��� ������ � ������� ������� � ��� , �������� �������
		if (m_recPhoneNumber.lPhoneTypeID == pPhoneType->lID)
		{
			nSelectIndex = (int)nIndex;
		}

		// ��������� �������� �������� � �����-�����
		CString strPhoneType;
		strPhoneType.Format(_T("%s"), pPhoneType->szType);
		if(m_cmbPhoneTypesType.AddString(strPhoneType) == CB_ERR)
		{
			MessageBox(L"������ ��� ���������� �� ��� �������.",
				MESSAGE);

			return FALSE;
		}

		if(m_cmbPhoneTypesType.SetItemData((int)nIndex, (DWORD)pPhoneType->lID) == CB_ERR)
		{
			MessageBox(L"������ ��� ���������� �� ���� �� ��������� ���.",
				MESSAGE);

			return FALSE;
		}
	}

	// ��� ������� � ������� , �������� ������������ �������� �� �����-�����
	if (nSelectIndex != CB_ERR)
	{
		m_cmbPhoneTypesType.SetCurSel(nSelectIndex);
	}	

	return TRUE;
}

void CPhoneNumbersDialog::OnOK()
{
	// ����������� ���� ������ � ������� � �������
	if (!CheckIsWindowTextValid())
		return;

	// ��������� �������
	SaveDataInBuffer();

	__super::OnOK();
}

void CPhoneNumbersDialog::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PHONE_NUMBERS_PHONE_NUMBER, m_edbPhoneNumbersPhoneNumber);
	DDX_Control(pDX, IDC_CMB_PHONE_TYPES_TYPE, m_cmbPhoneTypesType);
}


// MFC Message Handlers
// ----------------


// Overrides
// ----------------


// Methods
// ----------------
BOOL CPhoneNumbersDialog::CheckIsWindowTextValid()
{
	CString strPhoneNumber;
	m_edbPhoneNumbersPhoneNumber.GetWindowTextW(strPhoneNumber);

	// �������� ���� ���������� ����� � � ���� 5 �������
	if (strPhoneNumber.GetLength() < PHONE_NUMBER_MIN_SIZE)
	{
		MessageBox(PHONE_MIN_SIZE_MESSAGE,
			MESSAGE);

		return FALSE;
	}

	// ����������� ���� ��������� ��������� ����� � �������
	std::wregex regex(L"^\\d+$");
	if (!std::regex_match(strPhoneNumber.GetString(), regex))
	{
		MessageBox(L"���� ���������� ����� �� ������� ���� �����.",
			L"���������.");
		return FALSE;
	}

	// �������� ���� � ������ �������� ��������� ���
	if (m_cmbPhoneTypesType.GetCurSel() == CB_ERR)
	{
		MessageBox(PHONE_TYPE_MISSING_MESSAGE,
			MESSAGE);

		return FALSE;
	}

	return TRUE;
}

void CPhoneNumbersDialog::SaveDataInBuffer()
{
	// ��������� ���������� ����� �� ���� ����������
	CString strPhoneNumber;
	m_edbPhoneNumbersPhoneNumber.GetWindowTextW(strPhoneNumber);
	wcscpy_s(m_recPhoneNumber.szPhone, strPhoneNumber);

	int nSelectedItem = m_cmbPhoneTypesType.GetCurSel();

	// ��������� ��-�� �� ���������� ��� ������ �� ���� ����������
	m_recPhoneNumber.lPhoneTypeID = (long)m_cmbPhoneTypesType.GetItemData(nSelectedItem);
}

void CPhoneNumbersDialog::FillPhoneTypesArray(const CPhoneTypesArray& oPhoneTypesArray)
{
	// ���������� ������� �� �������� �� ����� ��� �������� �� �����
	m_oPhoneTypesArray.CopyArray(oPhoneTypesArray);
}
