#include "pch.h"
#include "framework.h"

#ifndef SHARED_HANDLERS
#include "PhoneBook.h"
#endif

#include "CitiesDocument.h"
#include "CitiesView.h"
#include "CitiesDialog.h"
#include "DialogModes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CCitiesView


//Macros
// --------------
IMPLEMENT_DYNCREATE(CCitiesView, CListView)

BEGIN_MESSAGE_MAP(CCitiesView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_CONTEXT_MENU_SELECT, SelectCity)
	ON_COMMAND(ID_CONTEXT_MENU_UPDATE, UpdateCity)
	ON_COMMAND(ID_CONTEXT_MENU_DELETE, DeleteCity)
	ON_COMMAND(ID_CONTEXT_MENU_INSERT, InsertCity)
	ON_NOTIFY(NM_DBLCLK, AFX_IDW_PANE_FIRST, &CCitiesView::OnItemDoubleClick)
END_MESSAGE_MAP()


// Constants
// ----------------
const LPCTSTR CCitiesView::lpszMenuRefresh = L"����������";
const LPCTSTR CCitiesView::lpszDeleteMessage = L"����� ���� ������ �������.";
const LPCTSTR CCitiesView::lpszMessage = L"���������";
const LPCTSTR CCitiesView::lpszConfirmation = L"�������� �� ������ �� �������� �����?";
const LPCTSTR CCitiesView::lpszConfirmationMessage = L"�������������";
const LPCTSTR CCitiesView::lpszMenuView = L"�������";
const LPCTSTR CCitiesView::lpszMenuInsert = L"��������";
const LPCTSTR CCitiesView::lpszMenuUpdate = L"��������";
const LPCTSTR CCitiesView::lpszMenuDelete = L"���������";


// Constructor / Destructor
// ----------------
CCitiesView::CCitiesView()
{
}

CCitiesView::~CCitiesView()
{
}


// Methods
// ----------------
CCitiesDocument* CCitiesView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCitiesDocument)));
	return (CCitiesDocument*)m_pDocument;
}


void CCitiesView::SelectCity()
{
	// ������ ��������� GetSelectedCityInListCtrl �� �� �������� �������� ����
	CITIES recSelectedCity;
	if (!GetSelectedCityInListCtrl(recSelectedCity))
		return;

	// ��������� ����� �� ������� � �� �������� ���� � ���� �� �� ������ � ����� �� ������
	CCitiesDialog oCitiesDialog(recSelectedCity, DialogModeReadOnly);

	// ��������� �������
	oCitiesDialog.DoModal();	
}

void CCitiesView::UpdateCity()
{
	// ������ ��������� GetSelectedCityInListCtrl �� �� �������� �������� ����
	CITIES recSelectedCity;
	if (!GetSelectedCityInListCtrl(recSelectedCity))
		return;

	// ��������� ����� �� ������� � �� ������ ���������� �� �������� ����
	CCitiesDialog oCitiesDialog(recSelectedCity);

	// ��������� ������� � ��� ��������� �� ����� �� ����������� �����
	if (oCitiesDialog.DoModal() != IDOK)
	{
		return;
	}

	// ��������� �������� ��� ��������� �� ������ �� ������ �� �����
	CCitiesDocument* pCitiesDoc = GetDocument();
	if (pCitiesDoc == nullptr)
		return;

	// ����������� ����� � ������ �����
	if (!pCitiesDoc->UpdateData(recSelectedCity))
	{
		MessageBox(_T("������� ��� ���������� �� �����."),
			lpszMessage);

		return;
	}
}

void CCitiesView::InsertCity()
{
	// ��������� ����� �� ������� � �� ������ ������ ���� �� ����������
	CITIES recCityToInsert;
	CCitiesDialog oCitiesDialog(recCityToInsert);

	// ��������� ������� � ��� ��������� �� ����� �� ������� recCityToInsert �������� � �����
	if (oCitiesDialog.DoModal() != IDOK)
	{
		return;
	}

	// ��������� �������� ��� ��������� �� ������ �� ������ �� �����
	CCitiesDocument* pCitiesDoc = GetDocument();
	if (pCitiesDoc == nullptr)
		return;

	// �������� ����� � ������ �����
	if (!pCitiesDoc->InsertData(recCityToInsert))
	{
		MessageBox(_T("������� ��� ���������� �� �����."),
			lpszMessage);

		return;
	}
}

void CCitiesView::DeleteCity()
{
	// ������ ��������� GetSelectedCityInListCtrl �� �� �������� �������� ����
	CITIES recDeleteCity;
	if (!GetSelectedCityInListCtrl(recDeleteCity))
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

	// ��������� �������� ��� ��������� �� ������ �� ������ �� �����
	CCitiesDocument* pCitiesDoc = GetDocument();
	if (pCitiesDoc == nullptr)
		return;

	// ��������� ����� �� ������
	if (!pCitiesDoc->DeleteData(recDeleteCity.lID))
	{
		MessageBox(_T("������� ��� ����������� �� �����."),
			lpszMessage);

		return;
	}

	// ��������� �� ������� ������ ����
	MessageBox(lpszDeleteMessage,
		lpszMessage);
}

void CCitiesView::RefreshCities()
{
	// ��������� ���������� �� ���� ���������� � �� ������ ������
	CListCtrl& oListCtrl = GetListCtrl();
	if (!oListCtrl.DeleteAllItems())
	{
		MessageBox(_T("������� ��� ������������ �� ������."),
			lpszMessage);

		return;
	}

	if(!AddItemsToListControl(oListCtrl))
	{
		MessageBox(_T("������� ��� ����������� �� ������."),
			lpszMessage);

		return;
	}
}

void CCitiesView::UpdateInView(const CITIES& recCity)
{
	// ������� ���������� �� ���� ����������
	CListCtrl& oListCtrl = GetListCtrl();

	// ��������� ���������� � ���� ����������
	for (int nIndex = 0; nIndex < oListCtrl.GetItemCount(); nIndex++)
	{
		if (oListCtrl.GetItemData(nIndex) != (DWORD)recCity.lID)
		{
			continue;
		}

		// ���� ���� ������� ����� ����� ������ �� �������� �� ����������� � ���� ����������
		if (!oListCtrl.SetItemText(nIndex, CITY_COLUMN_INDEX, recCity.szCityName))
		{
			MessageBox(ERROR_SAVING_CITY_MESSAGE,
				lpszConfirmationMessage);
		}
		if (!oListCtrl.SetItemText(nIndex, DISTRICT_COLUMN_INDEX, recCity.szDistrict))
		{
			MessageBox(ERROR_SAVING_DISTRICT_MESSAGE,
				lpszConfirmationMessage);
		}

		// ���������� ������
		break;
	}
}

void CCitiesView::InsertInView(const CITIES& recCity)
{
	// ������� ���������� �� ���� ����������
	CListCtrl& oListCtrl = GetListCtrl();

	// �������� � ���� �� ���� ���������� ����� �������
	int nIndex = oListCtrl.InsertItem(oListCtrl.GetItemCount(), recCity.szCityName);
	if (!oListCtrl.SetItemText(nIndex, DISTRICT_COLUMN_INDEX, recCity.szDistrict))
	{
		MessageBox(ERROR_SAVING_CITY_MESSAGE,
			lpszConfirmationMessage);
	}
	
	if (!oListCtrl.SetItemData(nIndex, (DWORD)recCity.lID))
	{
		return;
	}
}

void CCitiesView::DeleteInView(const CITIES& recCity)
{
	// ������� ���������� �� ���� ����������
	CListCtrl& oListCtrl = GetListCtrl();

	// ��������� ���������� � ���� ����������
	for (int nIndex = 0; nIndex < oListCtrl.GetItemCount(); nIndex++)
	{
		if (oListCtrl.GetItemData(nIndex) != (DWORD)recCity.lID)
		{
			continue;
		}

		// ���� ���� ������� ����� ����� ������ �� ������� �� ������ �� ���� ����������
		if (!oListCtrl.DeleteItem(nIndex))
			return;

		// ���������� ������
		break;
	}
}

BOOL CCitiesView::GetSelectedCityInListCtrl(CITIES& recCity)
{
	// ������� ���������� �� ���� ����������
	CListCtrl& oListCtrl = GetListCtrl();

	// ������� ������� �� ������������ ����
	int nSelectedItemIndex = oListCtrl.GetNextItem(-1, LVNI_SELECTED);

	// � ������ , �� ���� ���������� ����
	if (nSelectedItemIndex == CB_ERR)
		return FALSE;

	// ��������� �������� ��� ��������� �� ������ �� ������ �� �����
	CCitiesDocument* pCitiesDoc = GetDocument();
	if (pCitiesDoc == nullptr)
		return FALSE;

	// ����������� ��-�� �� �����
	const long lID = (long)oListCtrl.GetItemData(nSelectedItemIndex);
	
	// ��������� ����� �� ������
	if (!pCitiesDoc->SelectDataWithID(lID, recCity))
	{
		MessageBox(_T("������� ��� ����������� �� �����."),
			lpszMessage);

		return FALSE;
	}

	return TRUE;
}

void CCitiesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// �������� pHint ��� CITIES � �� ����������� � recCity �� ����������
	CITIES& recCity = *reinterpret_cast<CITIES*>(pHint);

	// ����������� lHint �� �� ������� ��� ���������� �������
	switch (lHint)
	{
	case OnUpdateHintUpdate:
		UpdateInView(recCity);
		break;

	case OnUpdateHintInsert:
		InsertInView(recCity);
		break;

	case OnUpdateHintDelete:
		DeleteInView(recCity);
		break;

	default:
		return;
	}
}

BOOL CCitiesView::InitializeListControl(CListCtrl& oListCtrl)
{
	// �������� ��������
	if (oListCtrl.InsertColumn(CITY_COLUMN_INDEX, CITY_COLUMN_NAME, LVCFMT_LEFT, CITY_COLUMN_SIZE) == CB_ERR)
		return FALSE;
	if (oListCtrl.InsertColumn(DISTRICT_COLUMN_INDEX, DISTRICT_COLUMN_NAME, LVCFMT_LEFT, DISTRICT_COLUMN_SIZE) == CB_ERR)
		return FALSE;

	// �������� �������� �� ���� ����������
	oListCtrl.ModifyStyle(0, LVS_REPORT);
	oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;
}

BOOL CCitiesView::AddItemsToListControl(CListCtrl& oListCtrl)
{
	// ��������� �������� ��� ��������� �� ������ �� ������ �� �����
	CCitiesDocument* pCitiesDoc = GetDocument();
	if (pCitiesDoc == nullptr)
		return FALSE;

	const CCitiesArray& oCitiesArray = pCitiesDoc->GetCitiesArray();

	// ������ �������� �� ���� ���������� � ������� �� ������ ��
	for (INT_PTR nIndex = 0; nIndex < oCitiesArray.GetCount(); nIndex++)
	{
		const CITIES* pCity = oCitiesArray.GetAt(nIndex);
		if (pCity == nullptr)
			return FALSE;

		int nItem = oListCtrl.InsertItem((int)nIndex, pCity->szCityName);
		if (nItem == CB_ERR)
			return FALSE;
		if (!oListCtrl.SetItemText(nItem, DISTRICT_COLUMN_INDEX, pCity->szDistrict))
			return FALSE;
		if (!oListCtrl.SetItemData(nItem, (DWORD)pCity->lID))
			return FALSE;
	}

	return TRUE;
}

void CCitiesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	// ������������� ������������
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCitiesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	CRect oRect;
	
	// ������� ������������ �� ������� �� ����� �� ����-�
	GetClientRect(&oRect);

	// ������������� ������������ �� ������� � ���������� �� ������
	ClientToScreen(&oRect);

	CMenu oMainMenu;
	// ����������� ���� ������������ �� � ������
	if (oRect.PtInRect(point))
	{
		// ��������� ������
		oMainMenu.CreatePopupMenu();
		oMainMenu.AppendMenu(MF_STRING, ID_CONTEXT_MENU_SELECT , lpszMenuView);
		oMainMenu.AppendMenu(MF_STRING, ID_CONTEXT_MENU_INSERT , lpszMenuInsert);
		oMainMenu.AppendMenu(MF_STRING, ID_CONTEXT_MENU_UPDATE , lpszMenuUpdate);
		oMainMenu.AppendMenu(MF_STRING, ID_CONTEXT_MENU_DELETE , lpszMenuDelete);
		oMainMenu.AppendMenu(MF_STRING, ID_CONTEXT_MENU_REFRESH, lpszMenuRefresh);
	}

	// ��������� ������ ����� �� ����-�
	oMainMenu.TrackPopupMenu(TPM_LEFTALIGN,point.x, point.y, this);
}

void CCitiesView::OnItemDoubleClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	// �������� �����
	SelectCity();
}

BOOL CCitiesView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// switch-case �� �� ��������� ��� ���������� �������
	switch (LOWORD(wParam))
	{
	case ID_CONTEXT_MENU_SELECT:
		SelectCity();
		break;

	case ID_CONTEXT_MENU_UPDATE:
		UpdateCity();
		break;

	case ID_CONTEXT_MENU_DELETE:
		DeleteCity();
		break;

	case ID_CONTEXT_MENU_INSERT:
		InsertCity();
		break;

	case ID_CONTEXT_MENU_REFRESH:
		RefreshCities();
		break;

	default:
		return __super::OnCommand(wParam, lParam);
	}

	return TRUE;
}


// Overrides
// ----------------
void CCitiesView::OnInitialUpdate()
{
	__super::OnInitialUpdate();

	// ������� ���������� �� ���� ����������
	CListCtrl& oListCtrl = GetListCtrl();

	// �������������� ���� ����������
	if (!InitializeListControl(oListCtrl))
	{
		MessageBox(_T("������� ��� ������������� �� ���� ����������."),
			lpszMessage);

		return;
	}

	// �������� �������� � ���� ����������
	if(!AddItemsToListControl(oListCtrl))
	{
		MessageBox(_T("������� ��� �������� �� �������� � ���� ����������."),
			lpszMessage);

		return;
	}
}
