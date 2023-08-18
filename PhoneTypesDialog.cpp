#include "pch.h"
#include "PhoneBook.h"
#include "PhoneTypesDialog.h"
#include "afxdialogex.h"
#include <regex>

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDialog

#define PHONE_TYPE_MIN_SIZE 2
#define PHONE_TYPE_MESSAGE _T("���� ��������� ��������� ��� �� � ����� 2 � 32 �������.") // string %d %d
#define MESSAGE _T("���������.")


// Macros
// ----------------
IMPLEMENT_DYNAMIC(CPhoneTypesDialog, CDialogEx)

BEGIN_MESSAGE_MAP(CPhoneTypesDialog, CDialogEx)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CPhoneTypesDialog::CPhoneTypesDialog(PHONE_TYPES& recPhoneType, DialogModes eDialogModes, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_PHONE_TYPES, pParent), m_recPhoneType(recPhoneType), m_eDialogModes(eDialogModes)
{
}

CPhoneTypesDialog::~CPhoneTypesDialog()
{
}


// MFC Overrides
// ----------------

void CPhoneTypesDialog::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDB_PHONE_TYPES_PHONE_TYPE, m_edbPhoneTypesPhoneType);
	DDX_Control(pDX, IDOK, m_btnOK);
}

BOOL CPhoneTypesDialog::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	// ����������� ���� ������ ������� �� � ReadOnly
	if (m_eDialogModes == DialogModeReadOnly)
	{
		m_edbPhoneTypesPhoneType.SetReadOnly(TRUE);

		m_edbPhoneTypesPhoneType.EnableWindow(FALSE);
		m_btnOK.EnableWindow(FALSE);
	}

	// ��������� � ������� ���������� ���
	m_edbPhoneTypesPhoneType.SetWindowText(m_recPhoneType.szType);

	return TRUE;
}

void CPhoneTypesDialog::OnOK()
{
	// ����������� ���� ������ � �������
	if (!CheckIsWindowTextValid())
	{
		return;
	}

	// ��������� �������
	SaveDataInBuffer();

	__super::OnOK();
}


// MFC Message Handlers
// ----------------


// Overrides
// ----------------


// Methods
// ----------------

BOOL CPhoneTypesDialog::CheckIsWindowTextValid()
{
	// ������� ������ �� ���� ���������� ��� �� ����
	CString strText;
	m_edbPhoneTypesPhoneType.GetWindowTextW(strText);

	// ����������� ���� � ��������� � ������ �� �����������
	if (strText.GetLength() <= PHONE_TYPE_MIN_SIZE)
	{
		MessageBox(PHONE_TYPE_MESSAGE,
			MESSAGE);

		return FALSE;
	}

	// ����������� ���� ��������� ���� � �� ��������
	std::wregex regex(L"^[�-��-�]+$");
	if (!std::regex_match(strText.GetString(), regex))
	{
		MessageBox(L"���� ����������� ���� ��������.",
			L"���������.");
		return FALSE;
	}

	return TRUE;
}

void CPhoneTypesDialog::SaveDataInBuffer()
{
	// ��������� ���������� ��� (m_recPhoneType)
	CString strCity;
	m_edbPhoneTypesPhoneType.GetWindowTextW(strCity);
	wcscpy_s(m_recPhoneType.szType, strCity);
}
