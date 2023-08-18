#include "pch.h"
#include "PhoneBook.h"
#include "CitiesDialog.h"
#include "afxdialogex.h"
#include <regex>

#define CITY_MIN_SIZE 2
#define DISTRICT_MIN_SIZE 2

/////////////////////////////////////////////////////////////////////////////
// CCitiesDialog


// Macros
// ----------------
IMPLEMENT_DYNAMIC(CCitiesDialog, CDialogEx)

BEGIN_MESSAGE_MAP(CCitiesDialog, CDialogEx)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CCitiesDialog::CCitiesDialog(CITIES& recCity , DialogModes eDialogModes , CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_CITIES, pParent), m_recCity(recCity),m_eDialogModes(eDialogModes)
{
}

CCitiesDialog::~CCitiesDialog()
{
}


// MFC Overrides
// ----------------

void CCitiesDialog::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_CITIES_CITY_NAME, m_edbCityName);
	DDX_Control(pDX, IDC_EDB_CITIES_DISTRICT, m_edbDistrict);
	DDX_Control(pDX, IDOK, m_btnOK);

	// �������� ������ �� ������ � ���� ����������
	m_edbCityName.SetLimitText(CITY_NAME_LENGTH-1);
	m_edbDistrict.SetLimitText(DISTRICT_LENGTH-1);
}

BOOL CCitiesDialog::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	// ����������� ���� ������ ������� �� � ReadOnly
	if (m_eDialogModes == DialogModeReadOnly)
	{
		// ���������� ������� �� ������� �� ���� ���������� � ������ ��
		m_edbCityName.SetReadOnly(TRUE);
		m_edbDistrict.SetReadOnly(TRUE);
		m_edbCityName.EnableWindow(FALSE);
		m_edbDistrict.EnableWindow(FALSE);
		m_btnOK.EnableWindow(FALSE);
	}

	// ��������� � ���� ���������� ����� � ��������
	m_edbCityName.SetWindowText(m_recCity.szCityName);
	m_edbDistrict.SetWindowText(m_recCity.szDistrict);

	return TRUE;
}

void CCitiesDialog::OnOK()
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
BOOL CCitiesDialog::CheckIsWindowTextValid()
{
	// ������� ������ �� ���� ���������� ��� �� ����
	CString strText;
	m_edbCityName.GetWindowTextW(strText);

	// ����������� ���� � ������ �� 2 �������
	if (strText.GetLength() <= CITY_MIN_SIZE)
	{
		MessageBox(L"���� ��������� ���� �� � � ������ �� 2 �������.",
			L"���������.");

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

	// ������� �������� �� ���� ���������� � ����������� ���� � ������ �� 2 �������
	m_edbDistrict.GetWindowTextW(strText);
	if (strText.GetLength() <= DISTRICT_MIN_SIZE)
	{
		MessageBox(L"���� ���������� ������ �� � � ������ �� 2 �������.",
			L"���������.");

		return FALSE;
	}

	// ����������� ���� ���������� ������ � �� ��������
	if (!std::regex_match(strText.GetString(), regex))
	{
		MessageBox(L"���� ����������� ���� ��������.",
			L"���������.");
		return FALSE;
	}

	return TRUE;
}

void CCitiesDialog::SaveDataInBuffer()
{
	// ��������� ������� �� ������� � ���������� ����(m_recCity)
	CString strCity;
	m_edbCityName.GetWindowTextW(strCity);
	wcscpy_s(m_recCity.szCityName, strCity);

	CString strDistrict;
	m_edbDistrict.GetWindowTextW(strDistrict);
	wcscpy_s(m_recCity.szDistrict, strDistrict);
}
