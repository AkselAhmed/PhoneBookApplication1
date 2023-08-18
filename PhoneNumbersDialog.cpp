#include "pch.h"
#include "PhoneBook.h"
#include "PhoneNumbersDialog.h"
#include "afxdialogex.h"
#include <regex>

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersDialog

#define PHONE_MIN_SIZE_MESSAGE L"Моля въведения телефонен номер да е с повече от 5 символа."
#define MESSAGE L"Съобщение."
#define PHONE_TYPE_MISSING_MESSAGE L"Моля изберете тип на телефонния номер."

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

	// Задаваме първоначална стойност на едит контролата избрания телефонен номер
	m_edbPhoneNumbersPhoneNumber.SetWindowText(m_recPhoneNumber.szPhone);

	int nSelectIndex = CB_ERR;
	// Обхождаме масива с телефонни типове и ги записваме в лист контролата
	for (INT_PTR nIndex = 0; nIndex < m_oPhoneTypesArray.GetCount(); nIndex++)
	{
		PHONE_TYPES* pPhoneType = m_oPhoneTypesArray.GetAt(nIndex);
		if (pPhoneType == nullptr)
			return FALSE;

		// Ако сме влезли с валиден телефон и тип , запзваме индекса
		if (m_recPhoneNumber.lPhoneTypeID == pPhoneType->lID)
		{
			nSelectIndex = (int)nIndex;
		}

		// Записваме типовете телефони в комбо-бокса
		CString strPhoneType;
		strPhoneType.Format(_T("%s"), pPhoneType->szType);
		if(m_cmbPhoneTypesType.AddString(strPhoneType) == CB_ERR)
		{
			MessageBox(L"Грешка при вмъкването на тип телефон.",
				MESSAGE);

			return FALSE;
		}

		if(m_cmbPhoneTypesType.SetItemData((int)nIndex, (DWORD)pPhoneType->lID) == CB_ERR)
		{
			MessageBox(L"Грешка при вмъкването на дата за телефонен тип.",
				MESSAGE);

			return FALSE;
		}
	}

	// Ако индекса е валиден , задаваме първоначална стойност на комбо-бокса
	if (nSelectIndex != CB_ERR)
	{
		m_cmbPhoneTypesType.SetCurSel(nSelectIndex);
	}	

	return TRUE;
}

void CPhoneNumbersDialog::OnOK()
{
	// Проверяваме дали текста в диалога е валиден
	if (!CheckIsWindowTextValid())
		return;

	// Записваме данните
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

	// Проверка дали телефонния номер е с поне 5 символа
	if (strPhoneNumber.GetLength() < PHONE_NUMBER_MIN_SIZE)
	{
		MessageBox(PHONE_MIN_SIZE_MESSAGE,
			MESSAGE);

		return FALSE;
	}

	// Проверяваме дали въведения телефонен номер е валиден
	std::wregex regex(L"^\\d+$");
	if (!std::regex_match(strPhoneNumber.GetString(), regex))
	{
		MessageBox(L"Моля телефонния номер да съдържа само цифри.",
			L"Съобщение.");
		return FALSE;
	}

	// Проверка дали е избран правилен телефонен тип
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
	// Записваме телефонния номер от едит контролата
	CString strPhoneNumber;
	m_edbPhoneNumbersPhoneNumber.GetWindowTextW(strPhoneNumber);
	wcscpy_s(m_recPhoneNumber.szPhone, strPhoneNumber);

	int nSelectedItem = m_cmbPhoneTypesType.GetCurSel();

	// Записваме ИД-то на телефонния тип избран от лист контролата
	m_recPhoneNumber.lPhoneTypeID = (long)m_cmbPhoneTypesType.GetItemData(nSelectedItem);
}

void CPhoneNumbersDialog::FillPhoneTypesArray(const CPhoneTypesArray& oPhoneTypesArray)
{
	// Използваме функция за копиране на масив със заделяне на памет
	m_oPhoneTypesArray.CopyArray(oPhoneTypesArray);
}
