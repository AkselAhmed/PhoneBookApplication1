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

	// Задаваме лимита на текста в едит контролите
	m_edbCityName.SetLimitText(CITY_NAME_LENGTH-1);
	m_edbDistrict.SetLimitText(DISTRICT_LENGTH-1);
}

BOOL CCitiesDialog::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	// Проверяваме дали трябва диалога да е ReadOnly
	if (m_eDialogModes == DialogModeReadOnly)
	{
		// Изключваме правото за промяна на едит контролите и бутона ОК
		m_edbCityName.SetReadOnly(TRUE);
		m_edbDistrict.SetReadOnly(TRUE);
		m_edbCityName.EnableWindow(FALSE);
		m_edbDistrict.EnableWindow(FALSE);
		m_btnOK.EnableWindow(FALSE);
	}

	// Записваме в едит контролите града и областта
	m_edbCityName.SetWindowText(m_recCity.szCityName);
	m_edbDistrict.SetWindowText(m_recCity.szDistrict);

	return TRUE;
}

void CCitiesDialog::OnOK()
{
	// Проверяваме дали текста е валиден
	if (!CheckIsWindowTextValid())
	{
		return;
	}

	// Записваме данните
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
	// Вземаме текста от едит контролата име на град
	CString strText;
	m_edbCityName.GetWindowTextW(strText);

	// Проверяваме дали е повече от 2 символа
	if (strText.GetLength() <= CITY_MIN_SIZE)
	{
		MessageBox(L"Моля въведения град да е с повече от 2 символа.",
			L"Съобщение.");

		return FALSE;
	}

	// Проверяваме дали въведения град е на кирилица
	std::wregex regex(L"^[А-Яа-я]+$");
	if (!std::regex_match(strText.GetString(), regex))
	{
		MessageBox(L"Моля използвайте само кирилица.",
			L"Съобщение.");
		return FALSE;
	}

	// Вземаме областта от едит контролата и проверяваме дали е повече от 2 символа
	m_edbDistrict.GetWindowTextW(strText);
	if (strText.GetLength() <= DISTRICT_MIN_SIZE)
	{
		MessageBox(L"Моля въведената област да е с повече от 2 символа.",
			L"Съобщение.");

		return FALSE;
	}

	// Проверяваме дали въведената област е на кирилица
	if (!std::regex_match(strText.GetString(), regex))
	{
		MessageBox(L"Моля използвайте само кирилица.",
			L"Съобщение.");
		return FALSE;
	}

	return TRUE;
}

void CCitiesDialog::SaveDataInBuffer()
{
	// Записваме данните от диалога в референтия град(m_recCity)
	CString strCity;
	m_edbCityName.GetWindowTextW(strCity);
	wcscpy_s(m_recCity.szCityName, strCity);

	CString strDistrict;
	m_edbDistrict.GetWindowTextW(strDistrict);
	wcscpy_s(m_recCity.szDistrict, strDistrict);
}
