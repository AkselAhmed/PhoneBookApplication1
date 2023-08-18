#include "pch.h"
#include "framework.h"

#ifndef SHARED_HANDLERS
#include "PhoneBook.h"
#endif

#include "PhoneTypesData.h"
#include "PhoneNumbersData.h"
#include "CitiesData.h"
#include "PersonsDocument.h"
#include "PersonsView.h"
#include "PersonsDialog.h"
#include "DialogModes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define FIRST_NAME_COLUMN_INDEX 0
#define FIRST_NAME_COLUMN_NAME _T("���")
#define FIRST_NAME_COLUMN_SIZE 150
#define SECOND_NAME_COLUMN_INDEX 1
#define SECOND_NAME_COLUMN_NAME _T("�������")
#define SECOND_NAME_COLUMN_SIZE 150
#define THIRD_NAME_COLUMN_INDEX 2
#define THIRD_NAME_COLUMN_NAME _T("�������")
#define THIRD_NAME_COLUMN_SIZE 150
#define EGN_COLUMN_INDEX 3
#define EGN_COLUMN_NAME _T("���")
#define EGN_COLUMN_SIZE 150
#define PERSON_CITY_COLUMN_INDEX 4
#define PERSON_CITY_COLUMN_NAME _T("����")
#define PERSON_CITY_COLUMN_SIZE 150
#define ADDRESS_COLUMN_INDEX 5
#define ADDRESS_COLUMN_NAME _T("�����")
#define ADDRESS_COLUMN_SIZE 150

const LPCTSTR CPersonsView::lpszMenuRefresh = L"����������";
const LPCTSTR CPersonsView::lpszDeleteMessage = L"������ ���� ������ �������.";
const LPCTSTR CPersonsView::lpszMessage = L"���������";
const LPCTSTR CPersonsView::lpszConfirmation = L"�������� �� ������ �� �������� ������?";
const LPCTSTR CPersonsView::lpszConfirmationMessage = L"�������������";
const LPCTSTR CPersonsView::lpszMenuView = L"�������";
const LPCTSTR CPersonsView::lpszMenuInsert = L"��������";
const LPCTSTR CPersonsView::lpszMenuUpdate = L"��������";
const LPCTSTR CPersonsView::lpszMenuDelete = L"���������";

/////////////////////////////////////////////////////////////////////////////
// CPersonsView


//Macros
// --------------
IMPLEMENT_DYNCREATE(CPersonsView, CListView)

BEGIN_MESSAGE_MAP(CPersonsView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_CONTEXT_MENU_SELECT, SelectPerson)
	ON_COMMAND(ID_CONTEXT_MENU_UPDATE, UpdatePerson)
	ON_COMMAND(ID_CONTEXT_MENU_DELETE, DeletePerson)
	ON_COMMAND(ID_CONTEXT_MENU_INSERT, InsertPerson)
	ON_NOTIFY(NM_DBLCLK, AFX_IDW_PANE_FIRST, &CPersonsView::OnItemDoubleClick)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------
CPersonsView::CPersonsView()
{
}

CPersonsView::~CPersonsView()
{
}


// Methods
// ----------------
CPersonsDocument* CPersonsView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersonsDocument)));
	return (CPersonsDocument*)m_pDocument;
}

void CPersonsView::SelectPerson()
{
	// ������ ��������� GetSelectedPersonInListCtrl �� �� �������� �������� �����
	CPersonInformation oPersonsInformation;

	if (!GetSelectedPersonInListCtrl(oPersonsInformation))
		return;

	CPersonsDocument* pPersonsDoc = GetDocument();
	if (pPersonsDoc == nullptr)
		return;

	// ��������� ����� �� ������� � �� ������ ����� � ���� �� �� ������ � ����� �� ������
	CPersonsDialog oPersonDialog(oPersonsInformation, DialogModeReadOnly);

	// ��������� ������ � ������� � ������ � ������ ��������
	oPersonDialog.FillCitiesArray(pPersonsDoc->GetDocCitiesArray());
	oPersonDialog.FillPhoneTypesArray(pPersonsDoc->GetDocPhoneTypesArray());

	// ��������� �������
	oPersonDialog.DoModal();
}

void CPersonsView::UpdatePerson()
{
	// ������ ��������� GetSelectedPersonInListCtrl �� �� �������� �������� �����
	CPersonInformation oPersonsInformation;
	if (!GetSelectedPersonInListCtrl(oPersonsInformation))
		return;

	CPersonsDocument* pPersonsDoc = GetDocument();
	if (pPersonsDoc == nullptr)
		return;

	// ��������� ����� �� ������� � �� ������ �����
	CPersonsDialog oPersonDialog(oPersonsInformation);

	// ��������� ������ � ������� � ������ � ������ ��������
	oPersonDialog.FillCitiesArray(pPersonsDoc->GetDocCitiesArray());
	oPersonDialog.FillPhoneTypesArray(pPersonsDoc->GetDocPhoneTypesArray());

	// ��������� ������� � ��� ��������� �� ����� �� ����������� ������ � �������� ��
	if (oPersonDialog.DoModal() != IDOK)
	{
		return;
	}

	// ����������� ������ � �������� �� � ������ �����
	if (!pPersonsDoc->UpdateData(oPersonsInformation))
		return;
}

void CPersonsView::InsertPerson()
{
	CPersonInformation oPersonsInformation;

	// ��������� ����� �� ������� � �� ������ ����
	CPersonsDialog oPersonDialog(oPersonsInformation);

	CPersonsDocument* pPersonsDoc = GetDocument();
	if (pPersonsDoc == nullptr)
		return;
	// ��������� ������ � ������� � ������ � ������ ��������
	oPersonDialog.FillCitiesArray(pPersonsDoc->GetDocCitiesArray());
	oPersonDialog.FillPhoneTypesArray(pPersonsDoc->GetDocPhoneTypesArray());

	// ��������� ������� � ��� ��������� �� ����� �� �������� �����
	if (oPersonDialog.DoModal() != IDOK)
	{
		return;
	}

	// �������� ������ � ����������� �� ������ � ������ �����
	if (!pPersonsDoc->InsertData(oPersonsInformation))
		return;
}

void CPersonsView::DeletePerson()
{
	CPersonInformation oPersonsInformation;
	if (!GetSelectedPersonInListCtrl(oPersonsInformation))
		return;

	// ��������� ��������� �� ������������� ����������� �� ����
	int nMessageBoxResult = MessageBox(lpszConfirmation,
		lpszConfirmationMessage,
		MB_ICONQUESTION | MB_YESNO);

	// ��������� ������� � ��� ��������� �� ����� YES ����� �����
	if (nMessageBoxResult != IDYES)
	{
		return;
	}

	// ��������� ����� �� ������ �����
	long lID = oPersonsInformation.GetPerson().lID;
	if (!GetDocument()->DeleteData(lID))
		return;

	// ��������� �� ������� ������ ����
	MessageBox(lpszDeleteMessage,
		lpszMessage);
}

void CPersonsView::RefreshPersons()
{
	// ��������� ���������� �� ���� ���������� � �� ������ ������
	CListCtrl& oListCtrl = GetListCtrl();
	if (!oListCtrl.DeleteAllItems())
	{
		MessageBox(L"��������� ������������ �� ������.",
			lpszMessage);

		return;
	}
	AddItemsToListControl(oListCtrl);
}

void CPersonsView::UpdateInView(const PERSONS& recPerson)
{
	// ������� ���������� �� ���� ����������
	CListCtrl& oListCtrl = GetListCtrl();

	// ��������� ���������� � ���� ����������
	for (int nIndex = 0; nIndex < oListCtrl.GetItemCount(); nIndex++)
	{
		if (oListCtrl.GetItemData(nIndex) != (DWORD)recPerson.lID)
		{
			continue;
		}

		long lID = recPerson.lCityID;
		CCitiesData oCitiesData;
		CITIES recCity;
		oCitiesData.SelectCityWithID(lID, recCity);

		if (!oListCtrl.SetItemText(nIndex, FIRST_NAME_COLUMN_INDEX, recPerson.szFirstName))
			return;
		if (!oListCtrl.SetItemText(nIndex, SECOND_NAME_COLUMN_INDEX, recPerson.szSecondName))
			return;
		if(!oListCtrl.SetItemText(nIndex, THIRD_NAME_COLUMN_INDEX, recPerson.szThirdName))
			return;
		if(!oListCtrl.SetItemText(nIndex, EGN_COLUMN_INDEX, recPerson.szEgn))
			return;
		if(!oListCtrl.SetItemText(nIndex, PERSON_CITY_COLUMN_INDEX, recCity.szCityName))
			return;
		if(!oListCtrl.SetItemText(nIndex, ADDRESS_COLUMN_INDEX, recPerson.szAddress))
			return;

		// ���������� ������
		break;
	}
}

void CPersonsView::InsertInView(const PERSONS& recPerson)
{
	// ������� ���������� �� ���� ����������
	CListCtrl& oListCtrl = GetListCtrl();

	long lID = recPerson.lCityID;
	CCitiesData oCitiesData;
	CITIES recCity;
	if (!oCitiesData.SelectCityWithID(lID, recCity))
		return;

	// �������� � ���� �� ���� ���������� ����� �������
	int nIndex = oListCtrl.InsertItem(oListCtrl.GetItemCount(), recPerson.szFirstName);
	if (nIndex == CB_ERR)
		return;
	if (!oListCtrl.SetItemText(nIndex, SECOND_NAME_COLUMN_INDEX, recPerson.szSecondName))
		return;
	if (!oListCtrl.SetItemText(nIndex, THIRD_NAME_COLUMN_INDEX, recPerson.szThirdName))
		return;
	if(!oListCtrl.SetItemText(nIndex, EGN_COLUMN_INDEX, recPerson.szEgn))
		return;
	if(!oListCtrl.SetItemText(nIndex, PERSON_CITY_COLUMN_INDEX, recCity.szCityName))
		return;
	if(!oListCtrl.SetItemText(nIndex, ADDRESS_COLUMN_INDEX, recPerson.szAddress))
		return;
	if(!oListCtrl.SetItemData(nIndex, (DWORD)recPerson.lID))
		return;
}

void CPersonsView::DeleteInView(const PERSONS& recPerson)
{
	// ������� ���������� �� ���� ����������
	CListCtrl& oListCtrl = GetListCtrl();

	// ��������� ���������� � ���� ����������
	for (int nIndex = 0; nIndex < oListCtrl.GetItemCount(); nIndex++)
	{
		if (oListCtrl.GetItemData(nIndex) != (DWORD)recPerson.lID)
		{
			continue;
		}

		// ���� ���� ������� ����� ����� ������ �� ������� �� ������ �� ���� ����������
		oListCtrl.DeleteItem(nIndex);

		// ���������� ������
		break;
	}
}

BOOL CPersonsView::GetSelectedPersonInListCtrl(CPersonInformation& recPerson)
{
	// ������� ���������� �� ���� ����������
	CListCtrl& oListCtrl = GetListCtrl();

	// ������� ������� �� ������������ �����
	int nSelectedItemIndex = oListCtrl.GetNextItem(-1, LVNI_SELECTED);

	// � ������ , �� ���� ���������� �����
	if (nSelectedItemIndex == CB_ERR)
		return FALSE;

	// ��������� ����� �� CPersonsDocument �� ������ �� ������ �� �����
	CPersonsDocument* pPersonsDocument = GetDocument();
	if (pPersonsDocument == nullptr)
		return FALSE;

	const long lID = (long)oListCtrl.GetItemData(nSelectedItemIndex);

	// ������� �������� ���� � �� �����������
	if (!pPersonsDocument->SelectDataWithID(lID, recPerson))
		return FALSE;

	return TRUE;
}

void CPersonsView::OnUpdate(CView * pSender, LPARAM lHint, CObject * pHint)
{
	// Cast-���� pHint-� � PERSONS
	PERSONS& recPerson = *reinterpret_cast<PERSONS*>(pHint);

	// ����������� lHint �� �� ������� ��� ���������� �������
	switch (lHint)
	{
	case OnUpdateHintUpdate:
		UpdateInView(recPerson);
		break;

	case OnUpdateHintInsert:
		InsertInView(recPerson);
		break;

	case OnUpdateHintDelete:
		DeleteInView(recPerson);
		break;

	default:
		return;
	}
}

void CPersonsView::InitializeListControl(CListCtrl& oListCtrl)
{
	// �������� ��������
	if (oListCtrl.InsertColumn(FIRST_NAME_COLUMN_INDEX, FIRST_NAME_COLUMN_NAME, LVCFMT_LEFT, FIRST_NAME_COLUMN_SIZE) == CB_ERR)
		return;
	if(oListCtrl.InsertColumn(SECOND_NAME_COLUMN_INDEX, SECOND_NAME_COLUMN_NAME, LVCFMT_LEFT, SECOND_NAME_COLUMN_SIZE) == CB_ERR)
		return;
	if(oListCtrl.InsertColumn(THIRD_NAME_COLUMN_INDEX, THIRD_NAME_COLUMN_NAME, LVCFMT_LEFT, THIRD_NAME_COLUMN_SIZE) == CB_ERR)
		return;
	if(oListCtrl.InsertColumn(EGN_COLUMN_INDEX, EGN_COLUMN_NAME, LVCFMT_LEFT, EGN_COLUMN_SIZE) == CB_ERR)
		return;
	if(oListCtrl.InsertColumn(PERSON_CITY_COLUMN_INDEX, PERSON_CITY_COLUMN_NAME, LVCFMT_LEFT, PERSON_CITY_COLUMN_SIZE) == CB_ERR)
		return;
	if(oListCtrl.InsertColumn(ADDRESS_COLUMN_INDEX, ADDRESS_COLUMN_NAME, LVCFMT_LEFT, ADDRESS_COLUMN_SIZE) == CB_ERR)
		return;

	// �������� �������� �� ���� ����������
	oListCtrl.ModifyStyle(0, LVS_REPORT);
	oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}

void CPersonsView::AddItemsToListControl(CListCtrl& oListCtrl)
{
	CPersonsDocument* pPersonsDocument = GetDocument();
	if (pPersonsDocument == nullptr)
		return;

	CPersonsArray oPersonsArray;
	if (!pPersonsDocument->SelectAllPersons(oPersonsArray))
		return;

	// ������ �������� �� ���� ���������� � ������� �� ������ ��
	for (INT_PTR nIndex = 0; nIndex < oPersonsArray.GetCount(); nIndex++)
	{
		PERSONS* pPerson = oPersonsArray.GetAt(nIndex);
		if (pPerson == nullptr)
			return;

		CITIES recCity;
		long lID= pPerson->lCityID;
		CCitiesData oCitiesData;
		if (!oCitiesData.SelectCityWithID(lID, recCity))
			return;
		int nItem = oListCtrl.InsertItem((int)nIndex, pPerson->szFirstName);
		if (nItem == CB_ERR)
			return;
		if (!oListCtrl.SetItemText(nItem, SECOND_NAME_COLUMN_INDEX, pPerson->szSecondName))
			return;
		if (!oListCtrl.SetItemText(nItem, THIRD_NAME_COLUMN_INDEX, pPerson->szThirdName))
			return;
		if (!oListCtrl.SetItemText(nItem, EGN_COLUMN_INDEX, pPerson->szEgn))
			return;
		if (!oListCtrl.SetItemText(nItem, PERSON_CITY_COLUMN_INDEX, recCity.szCityName))
			return;
		if (!oListCtrl.SetItemText(nItem, ADDRESS_COLUMN_INDEX, pPerson->szAddress))
			return;
		if (!oListCtrl.SetItemData(nItem, (DWORD)pPerson->lID))
			return;
	}
}

void CPersonsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPersonsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	CRect oRect;
	CMenu oMainMenu;

	// ���������� oRect �� GetClientRect �� ������ ������������ �� ������� �� ����� �� ����-�
	GetClientRect(&oRect);

	// ������������� ������������ �� ������� � ���������� �� ������
	ClientToScreen(&oRect);

	// ����������� ���� ������������ �� � ������
	if (oRect.PtInRect(point))
	{
		// ��������� ������
		oMainMenu.CreatePopupMenu();
		oMainMenu.AppendMenu(MF_STRING, ID_CONTEXT_MENU_SELECT, lpszMenuView);
		oMainMenu.AppendMenu(MF_STRING, ID_CONTEXT_MENU_INSERT, lpszMenuInsert);
		oMainMenu.AppendMenu(MF_STRING, ID_CONTEXT_MENU_UPDATE, lpszMenuUpdate);
		oMainMenu.AppendMenu(MF_STRING, ID_CONTEXT_MENU_DELETE, lpszMenuDelete);
		oMainMenu.AppendMenu(MF_STRING, ID_CONTEXT_MENU_REFRESH, lpszMenuRefresh);
	}

	// ��������� ������ ����� �� ����-�
	oMainMenu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
}

void CPersonsView::OnItemDoubleClick(NMHDR * pNMHDR, LRESULT * pResult)
{
	SelectPerson();
}

BOOL CPersonsView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// switch-case �� �� ��������� ��� ���������� �������
	switch (LOWORD(wParam))
	{
	case ID_CONTEXT_MENU_SELECT:
		SelectPerson();
		break;

	case ID_CONTEXT_MENU_UPDATE:
		UpdatePerson();
		break;

	case ID_CONTEXT_MENU_DELETE:
		DeletePerson();
		break;

	case ID_CONTEXT_MENU_INSERT:
		InsertPerson();
		break;

	case ID_CONTEXT_MENU_REFRESH:
		RefreshPersons();
		break;

	default:
		return CListView::OnCommand(wParam, lParam);
	}

	return TRUE;
}


// Overrides
// ----------------
void CPersonsView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// ������� ���������� �� ���� ����������
	CListCtrl& oListCtrl = GetListCtrl();

	// �������������� ���� ����������
	InitializeListControl(oListCtrl);

	// �������� �������� � ���� ����������
	AddItemsToListControl(oListCtrl);
}
