#include "pch.h"
#include "PhoneBook.h"
#include "PersonsDialog.h"
#include "afxdialogex.h"
#include "PhoneNumbersDialog.h"
#include <regex>

/////////////////////////////////////////////////////////////////////////////
// CPersonsDialog 

#define MENU_INSERT L"��������"
#define MENU_UPDATE L"��������"
#define MENU_DELETE L"���������"

#define NAME_MISSING_MESSAGE L"���� ��������� ������ �� ���."
#define SURNAME_MISSING_MESSAGE L"���� ��������� ������ �� �������."
#define FAMILY_NAME_MISSING_MESSAGE L"���� ��������� ������ �� �������."
#define EGN_MISSING_MESSAGE L"���� ��������� ������ �� ���(10 �������)."
#define CITY_MISSING_MESSAGE L"���� ��������� ������ �� ����."
#define ADDRESS_MISSING_MESSAGE L"���� ��������� ������ �� �����."
#define MESSAGE L"���������."
#define MISSING_PHONE_NUMBER_MESSAGE L"������ ��������� ����� , ������ �� �� ����������?"
#define PHONE_NUMBER_DELETION_MESSAGE L"�������� �� ������ �� �������� ���������� �����?" 
#define CONFIRMATION_MESSAGE  L"������������."

#define NAME_MIN_SIZE 2
#define SURNAME_MIN_SIZE 2
#define FAMILY_NAME_MIN_SIZE 2
#define EGN_SIZE 10
#define ADDRESS_MIN_SIZE 2


// Macros
// ----------------
IMPLEMENT_DYNAMIC(CPersonsDialog, CDialogEx)

BEGIN_MESSAGE_MAP(CPersonsDialog, CDialogEx)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()



// Constructor / Destructor
// ----------------

CPersonsDialog::CPersonsDialog(CPersonInformation& oPersonsInformation, DialogModes eDialogModes,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_PERSONS, pParent) , m_oPersonsInformation(oPersonsInformation) , m_eDialogModes(eDialogModes)
{
}

CPersonsDialog::~CPersonsDialog()
{
}


// MFC Overrides
// ----------------

void CPersonsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PERSONS_FIRST_NAME, m_edbPersonsFirstName);
	DDX_Control(pDX, IDC_EDB_PERSONS_ADDRESS, m_edbPersonsAddress);
	DDX_Control(pDX, IDC_EDB_PERSONS_SECOND_NAME, m_edbPersonsSecondName);
	DDX_Control(pDX, IDC_EDB_PERSONS_THIRD_NAME, m_edbPersonsThirdName);
	DDX_Control(pDX, IDC_EDB_PERSONS_EGN, m_edbPersonsEgn);
	DDX_Control(pDX, IDC_CMB_PERSONS_CITY, m_cmbPersonsCity);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_LSB_PERSONS_PHONE_NUMBERS, m_lsbPersonsPhoneNumbers);

	// �������� ������ �� ������ � ���� ����������
	m_edbPersonsFirstName.SetLimitText(FIRST_NAME_LENGTH - 1);
	m_edbPersonsAddress.SetLimitText(ADDRESS_LENGTH - 1);
	m_edbPersonsSecondName.SetLimitText(SECOND_NAME_LENGTH - 1);
	m_edbPersonsThirdName.SetLimitText(THIRD_NAME_LENGTH - 1);
	m_edbPersonsEgn.SetLimitText(EGN_LENGTH - 1);
}

void CPersonsDialog::OnOK()
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

BOOL CPersonsDialog::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	// ����������� ���� ������ ������� �� � ReadOnly
	if (m_eDialogModes == DialogModeReadOnly)
	{
		m_edbPersonsFirstName.SetReadOnly(TRUE);
		m_edbPersonsSecondName.SetReadOnly(TRUE);
		m_edbPersonsThirdName.SetReadOnly(TRUE);
		m_edbPersonsEgn.SetReadOnly(TRUE);
		m_edbPersonsAddress.SetReadOnly(TRUE);

		m_lsbPersonsPhoneNumbers.EnableWindow(FALSE);
		m_btnOK.EnableWindow(FALSE);
		m_cmbPersonsCity.EnableWindow(FALSE);
		m_edbPersonsFirstName.EnableWindow(FALSE);
		m_edbPersonsSecondName.EnableWindow(FALSE);
		m_edbPersonsThirdName.EnableWindow(FALSE);
		m_edbPersonsEgn.EnableWindow(FALSE);
		m_edbPersonsAddress.EnableWindow(FALSE);
	}

	// ��������� � ������� ������
	PERSONS& m_recPerson = m_oPersonsInformation.GetPerson();
	m_edbPersonsFirstName.SetWindowText(m_recPerson.szFirstName);
	m_edbPersonsSecondName.SetWindowText(m_recPerson.szSecondName);
	m_edbPersonsThirdName.SetWindowText(m_recPerson.szThirdName);
	m_edbPersonsEgn.SetWindowText(m_recPerson.szEgn);
	m_edbPersonsAddress.SetWindowText(m_recPerson.szAddress);

	// ����������� ���� ������ � ��������� � ������
	if (m_oCitiesArray.IsEmpty())
	{
		MessageBox(L"������ ��� ����������� �� ���������",
			MESSAGE);

		return FALSE;
	}

	int nCityIndex = CB_ERR;
	for (INT_PTR nIndex = 0; nIndex < m_oCitiesArray.GetCount(); nIndex++)
	{
		CITIES* pCity = m_oCitiesArray.GetAt(nIndex);
		if (pCity == nullptr)
			return FALSE;

		// ��������� ����� ����� � ���������� ������� � �������
		CString strCityInfo;
		strCityInfo.Format(_T("%s , %s"), pCity->szCityName, pCity->szDistrict);

		int nIndexCombo = m_cmbPersonsCity.AddString(strCityInfo);
		if (nIndexCombo == CB_ERR)
			return FALSE;
		if (m_cmbPersonsCity.SetItemData(nIndexCombo, pCity->lID) == CB_ERR)
			return FALSE;

		// ��� ������� ���������� �� lCityID �� ������ � lID �� ����� , ��������� �������
		if (pCity->lID == m_recPerson.lCityID)
		{
			nCityIndex = nIndexCombo;
		}
	}

	// ��� ������� � ������� , �������� ������������ �������� �� �����-����� �� ����
	if (nCityIndex != CB_ERR)
	{
		m_cmbPersonsCity.SetCurSel(nCityIndex);
	}

	// ��������� ����������� ������ �� ������
	for (INT_PTR nIndex = 0; nIndex < m_oPersonsInformation.GetPhoneNumbers().GetCount(); nIndex++)
	{
		PHONE_NUMBERS* pPhoneNumber = m_oPersonsInformation.GetPhoneNumbers().GetAt(nIndex);
		if (pPhoneNumber == nullptr)
			return FALSE;

		// ��������� ����������� ������
		for (INT_PTR nPhoneTypeIndex = 0; nPhoneTypeIndex < m_oPhoneTypesArray.GetCount(); nPhoneTypeIndex++)
		{
			PHONE_TYPES* pPhoneType = m_oPhoneTypesArray.GetAt(nPhoneTypeIndex);
			if (pPhoneType == nullptr)
				return FALSE;

			if (pPhoneNumber->lPhoneTypeID != pPhoneType->lID)
				continue;

			// ��� ���������� , ��������� ���������� ����� ������ � ���� ��
			CString strPhoneNumber;
			strPhoneNumber.Format(_T("%s  (%s)"), pPhoneNumber->szPhone, pPhoneType->szType);

			// �������� ������-� � ���� �����
			int nListBoxIndex = m_lsbPersonsPhoneNumbers.InsertString((int)nIndex, strPhoneNumber);
			if (nListBoxIndex == CB_ERR)
			{
				MessageBox(L"������ ��� ���������� �� ��������� �����.",
					MESSAGE);

				return FALSE;
			}
			if (m_lsbPersonsPhoneNumbers.SetItemData(nListBoxIndex, (DWORD)pPhoneNumber->lID) == CB_ERR)
			{
				MessageBox(L"������ ��� ��������� �� ����-��.",
					MESSAGE);

				return FALSE;
			}
		}
	}

	return TRUE;
}


// MFC Message Handlers
// ----------------
void CPersonsDialog::OnContextMenu(CWnd * pWnd, CPoint point)
{
	// ������� ������� ��� ��������� �� ����������� ������
	CListBox* pListBox = static_cast<CListBox*>(GetDlgItem(IDC_LSB_PERSONS_PHONE_NUMBERS));
	if (pListBox != nullptr && pWnd == pListBox)
	{
		// ��������� ���������� ����
		CMenu menu;
		if (menu.CreatePopupMenu())
		{
			// �������� ���������� ����� �� ������
			menu.AppendMenu(MF_STRING, ID_LSB_MENU_UPDATE, MENU_UPDATE);
			menu.AppendMenu(MF_STRING, ID_LSB_MENU_INSERT, MENU_INSERT);
			menu.AppendMenu(MF_STRING, ID_LSB_MENU_DELETE, MENU_DELETE);

			CPoint ptScreen = point;
			pListBox->ClientToScreen(&ptScreen);
			GetCursorPos(&ptScreen);

			// ��������� ������
			menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, ptScreen.x, ptScreen.y, this);
		}
	}
}

BOOL CPersonsDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// switch-case �� �� ������� ��� ���������� ������� ���� ����� �� ���������� ����
	switch (LOWORD(wParam))
	{
	case ID_LSB_MENU_INSERT:
		InsertPhoneNumber();
		break;

	case ID_LSB_MENU_UPDATE:
		UpdatePhoneNumber();
		break;

	case ID_LSB_MENU_DELETE:
		DeletePhoneNumber();
		break;

	default:
		return __super::OnCommand(wParam, lParam);
	}

	return TRUE;
}


// Methods
// ----------------
BOOL CPersonsDialog::CheckIsWindowTextValid()
{
	CString strText;
	m_edbPersonsFirstName.GetWindowTextW(strText);

	// ����������� ���� � �������� ���
	if (strText.GetLength() <= NAME_MIN_SIZE)
	{
		MessageBox(NAME_MISSING_MESSAGE,
			MESSAGE);

		return FALSE;
	}

	// ����������� ���� ���������� ��� � �� ��������
	std::wregex regex(L"^[�-��-�]+$");
	if (!std::regex_match(strText.GetString(), regex))
	{
		MessageBox(L"���� ����������� ���� �������� �� �����.",
			L"���������.");
		return FALSE;
	}

	// ����������� ���� � �������� �������
	m_edbPersonsSecondName.GetWindowTextW(strText);
	if (strText.GetLength() <= SURNAME_MIN_SIZE)
	{
		MessageBox(SURNAME_MISSING_MESSAGE,
			MESSAGE);

		return FALSE;
	}

	// ����������� ���� ���������� ������� � �� ��������
	if (!std::regex_match(strText.GetString(), regex))
	{
		MessageBox(L"���� ����������� ���� �������� �� ���������.",
			L"���������.");
		return FALSE;
	}

	// ����������� ���� � �������� �������
	m_edbPersonsThirdName.GetWindowTextW(strText);
	if (strText.GetLength() <= FAMILY_NAME_MIN_SIZE)
	{
		MessageBox(FAMILY_NAME_MISSING_MESSAGE,
			MESSAGE);

		return FALSE;
	}

	// ����������� ���� ���������� ������� � �� ��������
	if (!std::regex_match(strText.GetString(), regex))
	{
		MessageBox(L"���� ����������� ���� �������� �� ���������.",
			L"���������.");
		return FALSE;
	}

	// ����������� ���� � �������� ����� ���
	m_edbPersonsEgn.GetWindowTextW(strText);
	if (strText.GetLength() != EGN_SIZE)
	{
		MessageBox(EGN_MISSING_MESSAGE,
			MESSAGE);

		return FALSE;
	}

	// ����������� ���� ��������� ��������� ����� � �������
	std::wregex egnRegex(L"^\\d+$");
	if (!std::regex_match(strText.GetString(), egnRegex))
	{
		MessageBox(L"���� ���-�� �� ������� ���� �����.",
			L"���������.");
		return FALSE;
	}

	// ����������� ���� � ������ ���� �� ����� �����
	if (m_cmbPersonsCity.GetCurSel() == CB_ERR)
	{
		MessageBox(CITY_MISSING_MESSAGE,
			MESSAGE);

		return FALSE;
	}

	// ����������� ���� � ������� �����
	m_edbPersonsAddress.GetWindowTextW(strText);
	if (strText.GetLength() <= ADDRESS_MIN_SIZE)
	{
		MessageBox(ADDRESS_MISSING_MESSAGE,
			MESSAGE);

		return FALSE;
	}

	// ����������� ���� ��������� ����� � ������� 
	std::wregex addressRegex(L"^[^!@#$%^&*()_+=\\{}|;:', .<> / ? \\] * $");
	if (!std::regex_match(strText.GetString(), regex))
	{
		MessageBox(L"���� �� ����������� ������� �� ������.",
			L"���������.");
		return FALSE;
	}

	// ����������� ���� ���� �� �������� ��� ��������� �����
	if (m_lsbPersonsPhoneNumbers.GetCount() == 0)
	{
		int nMessageBoxResult = MessageBox(MISSING_PHONE_NUMBER_MESSAGE,
			CONFIRMATION_MESSAGE,
			MB_ICONQUESTION | MB_YESNO);

		if (nMessageBoxResult != IDYES)
			return FALSE;
	}

	return TRUE;
}

void CPersonsDialog::SaveDataInBuffer()
{
	// ��������� �� � ���������� � ������� ����� (m_oPersonsInformation)
	PERSONS& m_recPerson = m_oPersonsInformation.GetPerson();

	CString strFirstName;
	m_edbPersonsFirstName.GetWindowTextW(strFirstName);
	wcscpy_s(m_recPerson.szFirstName, strFirstName);

	CString strSecondName;
	m_edbPersonsSecondName.GetWindowTextW(strSecondName);
	wcscpy_s(m_recPerson.szSecondName, strSecondName);

	CString strThirdName;
	m_edbPersonsThirdName.GetWindowTextW(strThirdName);
	wcscpy_s(m_recPerson.szThirdName, strThirdName);

	CString strEgn;
	m_edbPersonsEgn.GetWindowTextW(strEgn);
	wcscpy_s(m_recPerson.szEgn, strEgn);

	int nIndex = m_cmbPersonsCity.GetCurSel();
	m_recPerson.lCityID = static_cast<long>(m_cmbPersonsCity.GetItemData(nIndex));

	CString strAddress;
	m_edbPersonsAddress.GetWindowTextW(strAddress);
	wcscpy_s(m_recPerson.szAddress, strAddress);
}

void CPersonsDialog::InsertPhoneNumber()
{
	PHONE_NUMBERS recPhoneNumber;
	
	// ��������� ����� �� ������� �� ��������� ������
	CPhoneNumbersDialog oPhoneNumbersDialog(recPhoneNumber);
	
	// ������ ������ � ��������� ������
	oPhoneNumbersDialog.FillPhoneTypesArray(m_oPhoneTypesArray);
	if (oPhoneNumbersDialog.DoModal() != IDOK)
	{
		return;
	}

	PERSONS& recPerson = m_oPersonsInformation.GetPerson();

	// ����������� �� �� ������ � ���������� �����
	recPhoneNumber.lPersonID = recPerson.lID;

	// �������� ����� �� ����� ��������� �����
	PHONE_NUMBERS* pNewPhone = new PHONE_NUMBERS();
	*pNewPhone = recPhoneNumber;

	// ��������� ����� ��������� ����� � ������ �� ������
	m_oPersonsInformation.GetPhoneNumbers().Add(pNewPhone);
	
	// ���������  ������ � ������ ��������
	for (INT_PTR nPhoneTypeIndex = 0; nPhoneTypeIndex < m_oPhoneTypesArray.GetCount(); nPhoneTypeIndex++)
	{
		PHONE_TYPES* pPhoneType = m_oPhoneTypesArray.GetAt(nPhoneTypeIndex);
		if (pPhoneType == nullptr)
			return;

		if (recPhoneNumber.lPhoneTypeID != pPhoneType->lID)
			continue;

		// ���� ������� ����� ��� � �������� , �� ���������
		CString strPhoneNumber;
		strPhoneNumber.Format(_T("%s  (%s)"), recPhoneNumber.szPhone, pPhoneType->szType);

		// �������� � ���� ����� ����� ��������� �����
		int nAdded = m_lsbPersonsPhoneNumbers.AddString(strPhoneNumber);
		if (nAdded == CB_ERR)
		{
			MessageBox(L"������ ��� ����������� �� ��������� ������.",
				MESSAGE);

			return;
		}

		break;
	}
}

void CPersonsDialog::UpdatePhoneNumber()
{
	// ����������� ���� � ������ ����� �� ���� ����-�
	int nIndex = m_lsbPersonsPhoneNumbers.GetCurSel();
	if (nIndex == LB_ERR)
		return;

	// ������� ���������� ����� �� ���� ������
	PHONE_NUMBERS* pPhoneNumber = m_oPersonsInformation.GetPhoneNumbers().GetAt(nIndex);
	if (pPhoneNumber == nullptr)
		return;

	// ��������� ����� �� ������� �� ��������� ������ � �� �������� ��������
	CPhoneNumbersDialog oPhoneNumbersDialog(*pPhoneNumber);

	// ������ ������ � ��������� ������
	oPhoneNumbersDialog.FillPhoneTypesArray(m_oPhoneTypesArray);
	if (oPhoneNumbersDialog.DoModal() != IDOK)
	{
		return;
	}

	// ��������� ����������� ������
	for (INT_PTR nPhoneTypeIndex = 0; nPhoneTypeIndex < m_oPhoneTypesArray.GetCount(); nPhoneTypeIndex++)
	{
		PHONE_TYPES* pPhoneType = m_oPhoneTypesArray.GetAt(nPhoneTypeIndex);
		if (pPhoneType == nullptr)
			return;

		if (pPhoneNumber->lPhoneTypeID != pPhoneType->lID)
			continue;

		// ���� ������� �������� ����� ��� � , ��  ���������
		CString strPhoneNumber;
		strPhoneNumber.Format(_T("%s  (%s)"), pPhoneNumber->szPhone, pPhoneType->szType);

		// �� ������� ������ ��� ����������� ��������� ������-� � ��������� �����
		if (m_lsbPersonsPhoneNumbers.DeleteString(nIndex) == CB_ERR)
			return;
		if (m_lsbPersonsPhoneNumbers.InsertString(nIndex, strPhoneNumber) == CB_ERR)
		{
			MessageBox(L"������ ��� ���������� �� ��������� �����.",
				MESSAGE);

			return;
		}

		// ��������� ����� ��������� ����� � ������
		m_oPersonsInformation.GetPhoneNumbers().SetAt(nIndex, pPhoneNumber);

		break;
	}
}

void CPersonsDialog::DeletePhoneNumber()
{
	// ����������� ���� � ������ ����� �� ���� ����-�
	int nIndex = m_lsbPersonsPhoneNumbers.GetCurSel();
	if (nIndex == LB_ERR)
		return;

	// ������� ���������� ����� �� ���� ������
	PHONE_NUMBERS* pPhoneNumber = m_oPersonsInformation.GetPhoneNumbers().GetAt(nIndex);
	if (pPhoneNumber == nullptr)
		return;

	// ��������� �� ������������ ����������� �� ���������� �����
	int nMessageBoxResult = MessageBox(PHONE_NUMBER_DELETION_MESSAGE,
		MESSAGE,
		MB_ICONQUESTION | MB_YESNO);

	if (nMessageBoxResult != IDYES)
	{
		return;
	}

	// ��������� ���������� ����� �� ���� ����� � �� ������
	if (m_lsbPersonsPhoneNumbers.DeleteString(nIndex) == CB_ERR)
		return;
	m_oPersonsInformation.GetPhoneNumbers().Delete(nIndex);
}

void CPersonsDialog::FillCitiesArray(const CCitiesArray& oCitiesArray)
{
	// ���������� ������� �� �������� �� ����� ��� �������� �� �����
	m_oCitiesArray.CopyArray(oCitiesArray);
}

void CPersonsDialog::FillPhoneTypesArray(const CPhoneTypesArray& oPhoneTypesArray)
{
	// ���������� ������� �� �������� �� ����� ��� �������� �� �����
	m_oPhoneTypesArray.CopyArray(oPhoneTypesArray);
}



// Overrides
// ----------------
