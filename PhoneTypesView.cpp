#include "pch.h"
#include "framework.h"

#ifndef SHARED_HANDLERS
#include "PhoneBook.h"
#endif

#include "PhoneTypesView.h"
#include "PhoneTypesDialog.h"
#include "DialogModes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesView

#define PHONE_TYPE_COLUMN_INDEX 0
#define ERROR_SAVING_PHONE_TYPE _T("��������� ��������� �� ���������� ���.")
#define ERROR_DELETING_PHONE_TYPE _T("��������� ��������� �� ���������� ���.")


//Macros
// --------------
IMPLEMENT_DYNCREATE(CPhoneTypesView, CListView)

BEGIN_MESSAGE_MAP(CPhoneTypesView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_CONTEXT_MENU_SELECT, SelectPhoneType)
	ON_COMMAND(ID_CONTEXT_MENU_UPDATE, UpdatePhoneType)
	ON_COMMAND(ID_CONTEXT_MENU_DELETE, DeletePhoneType)
	ON_COMMAND(ID_CONTEXT_MENU_INSERT, InsertPhoneType)
	ON_NOTIFY(NM_DBLCLK, AFX_IDW_PANE_FIRST, &CPhoneTypesView::OnItemDoubleClick)
END_MESSAGE_MAP()


// Constants
// ----------------
const LPCTSTR CPhoneTypesView::lpszMenuRefresh = L"����������";
const LPCTSTR CPhoneTypesView::lpszDeleteMessage = L"���������� ��� ���� ������ �������.";
const LPCTSTR CPhoneTypesView::lpszMessage = L"���������";
const LPCTSTR CPhoneTypesView::lpszConfirmation = L"�������� �� ������ �� �������� ���������� ���?";
const LPCTSTR CPhoneTypesView::lpszConfirmationMessage = L"�������������";
const LPCTSTR CPhoneTypesView::lpszMenuView = L"�������";
const LPCTSTR CPhoneTypesView::lpszMenuInsert = L"��������";
const LPCTSTR CPhoneTypesView::lpszMenuUpdate = L"��������";
const LPCTSTR CPhoneTypesView::lpszMenuDelete = L"���������";


// Constructor / Destructor
// ----------------
CPhoneTypesView::CPhoneTypesView()
{
}

CPhoneTypesView::~CPhoneTypesView()
{
}


// Methods
// ----------------
CPhoneTypesDocument* CPhoneTypesView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhoneTypesDocument)));
	return (CPhoneTypesDocument*)m_pDocument;
}


void CPhoneTypesView::SelectPhoneType()
{
	// ������ ��������� GetSelectedPhoneTypeInListCtrl �� �� �������� �������� ��������� ���
	PHONE_TYPES recSelectedPhoneType;
	if (!GetSelectedPhoneTypeInListCtrl(recSelectedPhoneType))
		return;

	// ��������� ����� �� ������� � �� ������ ��������� ��� � ���� �� �� ������ � ����� �� ������
	CPhoneTypesDialog oPhoneTypesDialog(recSelectedPhoneType, DialogModeReadOnly);

	// ��������� �������
	oPhoneTypesDialog.DoModal();
}

void CPhoneTypesView::UpdatePhoneType()
{
	// ������ ��������� GetSelectedPhoneTypeInListCtrl �� �� �������� �������� ��������� ���
	PHONE_TYPES recSelectedPhoneType;
	if (!GetSelectedPhoneTypeInListCtrl(recSelectedPhoneType))
		return;

	// ��������� ����� �� ������� � �� ������ ��������� ���
	CPhoneTypesDialog oPHONE_TYPESDialog(recSelectedPhoneType);

	// ��������� ������� � ��� ��������� �� ����� �� ����������� ���������� ���
	if (oPHONE_TYPESDialog.DoModal() != IDOK)
	{
		return;
	}

	CPhoneTypesDocument* pPhoneTypesDocument = GetDocument();
	if (pPhoneTypesDocument == nullptr)
		return;

	// ����������� ���������� ��� � ������ �����
	if (!pPhoneTypesDocument->UpdateData(recSelectedPhoneType))
	{
		MessageBox(L"������ ��� ���������� �� ��������� ���.",
			L"���������");

		return;
	}
}

void CPhoneTypesView::InsertPhoneType()
{
	PHONE_TYPES recPhoneTypeToInsert;

	// ��������� ����� �� ������� � �� ������ ��������� ���
	CPhoneTypesDialog oPhoneTypesDialog(recPhoneTypeToInsert);

	// ��������� ������� � ��� ��������� �� ����� �� �������� ���������� ���
	if (oPhoneTypesDialog.DoModal() != IDOK)
	{
		return;
	}

	// ��������� ����� �� CPhoneTypesDocument �� ������ �� ������ �� �����
	CPhoneTypesDocument* pPhoneTypesDocument = GetDocument();
	if (pPhoneTypesDocument == nullptr)
		return;

	// �������� ��������� ���� � ������ �����
	if (!pPhoneTypesDocument->InsertData(recPhoneTypeToInsert))
	{
		MessageBox(L"������ ��� ���������� �� ��������� ���.",
			L"���������");

		return;
	}
}

void CPhoneTypesView::DeletePhoneType()
{
	// ������ ��������� GetSelectedPhoneTypeInListCtrl �� �� �������� �������� ��������� ���
	PHONE_TYPES recDeletePhoneType;
	if (!GetSelectedPhoneTypeInListCtrl(recDeletePhoneType))
		return;

	// ��������� ��������� �� ������������� ����������� �� ��������� ���
	int nMessageBoxResult = MessageBox(lpszConfirmation,
		lpszConfirmationMessage,
		MB_ICONQUESTION | MB_YESNO);

	// ��������� ������� � ��� ��������� �� ����� YES ����� ���������� ���
	if (nMessageBoxResult != IDYES)
	{
		return;
	}

	// ��������� ���������� ��� �� ������ �����
	const long lID = recDeletePhoneType.lID;

	// ��������� ����� �� CPhoneTypesDocument �� ������ �� ������ �� �����
	CPhoneTypesDocument* pPhoneTypesDocument = GetDocument();
	if (pPhoneTypesDocument == nullptr)
		return;

	if (!pPhoneTypesDocument->DeleteData(lID))
	{
		MessageBox(L"������ ��� ����������� �� ��������� ���.",
			L"���������");

		return;
	}

	// ��������� �� ������� ������ ��������� ���
	MessageBox(lpszDeleteMessage,
		lpszMessage);
}

void CPhoneTypesView::RefreshPhoneTypes()
{
	// ��������� ���������� �� ���� ���������� � �� ������ ������
	CListCtrl& oListCtrl = GetListCtrl();
	if (!oListCtrl.DeleteAllItems())
	{
		MessageBox(L"������� ��� ������������ �� �������.",
			lpszMessage);

		return;
	}
	AddItemsToListControl(oListCtrl);
}

void CPhoneTypesView::UpdateInView(const PHONE_TYPES& recPhoneType)
{
	// ������� ���������� �� ���� ����������
	CListCtrl& oListCtrl = GetListCtrl();

	// ��������� ���������� � ���� ����������
	for (int nIndex = 0; nIndex < oListCtrl.GetItemCount(); nIndex++)
	{
		if (oListCtrl.GetItemData(nIndex) != (DWORD)recPhoneType.lID)
		{
			continue;
		}

		// ���� ���� ������� ��������� ���� ����� ������ �� �������� �� ����������� � ���� ����������
		if (!oListCtrl.SetItemText(nIndex, PHONE_TYPE_COLUMN_INDEX, recPhoneType.szType))
		{
			MessageBox(ERROR_SAVING_PHONE_TYPE,
				lpszConfirmationMessage);

			return;
		}

		// ���������� ������
		break;
	}
}

void CPhoneTypesView::InsertInView(const PHONE_TYPES& recPhoneType)
{
	// ������� ���������� �� ���� ����������
	CListCtrl& oListCtrl = GetListCtrl();

	// �������� � ���� �� ���� ���������� ����� �������
	int nIndex = oListCtrl.InsertItem(oListCtrl.GetItemCount(), recPhoneType.szType);

	if (!oListCtrl.SetItemData(nIndex, (DWORD)recPhoneType.lID))
	{
		MessageBox(ERROR_SAVING_PHONE_TYPE,
			lpszConfirmationMessage);

		return;
	}
}

void CPhoneTypesView::DeleteInView(const PHONE_TYPES& recPhoneType)
{
	// ������� ���������� �� ���� ����������
	CListCtrl& oListCtrl = GetListCtrl();

	// ��������� ���������� � ���� ����������
	for (int nIndex = 0; nIndex < oListCtrl.GetItemCount(); nIndex++)
	{
		if (oListCtrl.GetItemData(nIndex) != (DWORD)recPhoneType.lID)
		{
			continue;
		}

		// ���� ���� ������� ��������� ���� ����� ������ �� ������� �� ������ �� ���� ����������
		if (!oListCtrl.DeleteItem(nIndex))
		{
			MessageBox(ERROR_DELETING_PHONE_TYPE,
				lpszConfirmationMessage);

			return;
		}

		// ���������� ������
		break;
	}
}

BOOL CPhoneTypesView::GetSelectedPhoneTypeInListCtrl(PHONE_TYPES& recPhoneType)
{
	// ������� ���������� �� ���� ����������
	CListCtrl& oListCtrl = GetListCtrl();

	// ������� ������� �� ������������ ��������� ���
	int nSelectedItemIndex = oListCtrl.GetNextItem(-1, LVNI_SELECTED);

	// � ������ , �� ���� ���������� ��������� ���
	if (nSelectedItemIndex == CB_ERR)
		return FALSE;

	// ��������� ����� �� CPhoneTypesDocument �� ������ �� ������ �� �����
	CPhoneTypesDocument* pPhoneTypesDocument = GetDocument();
	if (pPhoneTypesDocument == nullptr)
		return FALSE;

	const long lID = (long)oListCtrl.GetItemData(nSelectedItemIndex);

	// ������� �������� ��������� ��� � �� �����������
	if (!pPhoneTypesDocument->SelectDataWithID(lID, recPhoneType))
		return FALSE;

	return TRUE;
}

void CPhoneTypesView::InitializeListControl(CListCtrl& oListCtrl)
{
	// �������� ��������
	if (oListCtrl.InsertColumn(PHONE_TYPE_COLUMN_INDEX, PHONE_TYPE_COLUMN_NAME, LVCFMT_LEFT, PHONE_TYPE_COLUMN_SIZE) == CB_ERR)
	{
		MessageBox(L"��������� ��������� �� ��������.",
			lpszMessage);

		return;
	}

	// �������� �������� �� ���� ����������
	oListCtrl.ModifyStyle(0, LVS_REPORT);
	oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}

void CPhoneTypesView::AddItemsToListControl(CListCtrl& oListCtrl)
{
	// ��������� ����� �� ��������� �� ������ �� ������
	CPhoneTypesDocument* pPhoneTypesDocument = GetDocument();
	if (pPhoneTypesDocument == nullptr)
		return;

	// ������ �������� �� ���� ���������� � ������� �� ������ ��
	for (INT_PTR nIndex = 0; nIndex < pPhoneTypesDocument->GetDocArray().GetCount(); nIndex++)
	{
		PHONE_TYPES* pPhoneType = pPhoneTypesDocument->GetDocArray().GetAt(nIndex);
		if (pPhoneType == nullptr)
			return;

		int nItem = oListCtrl.InsertItem((int)nIndex, pPhoneType->szType);
		if (nItem == CB_ERR)
			return;
		if (!oListCtrl.SetItemData(nItem, (DWORD)pPhoneType->lID))
		{
			MessageBox(L"��������� ��������� �� ������.",
				lpszMessage);

			return;
		}
	}
}

void CPhoneTypesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPhoneTypesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
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

void CPhoneTypesView::OnItemDoubleClick(NMHDR * pNMHDR, LRESULT * pResult)
{
	SelectPhoneType();
}


// Overrides
// ----------------
void CPhoneTypesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// �������� pHint ��� PHONE_TYPES � �� ����������� � recPhoneType
	PHONE_TYPES& recPhoneType = *reinterpret_cast<PHONE_TYPES*>(pHint);

	// ����������� lHint �� �� ������� ��� ���������� �������
	switch (lHint)
	{
	case OnUpdateHintUpdate:
		UpdateInView(recPhoneType);
		break;

	case OnUpdateHintInsert:
		InsertInView(recPhoneType);
		break;

	case OnUpdateHintDelete:
		DeleteInView(recPhoneType);
		break;

	default:
		return;
	}
}

BOOL CPhoneTypesView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// switch-case �� �� ��������� ��� ���������� �������
	switch (LOWORD(wParam))
	{
	case ID_CONTEXT_MENU_SELECT:
		SelectPhoneType();
		break;

	case ID_CONTEXT_MENU_UPDATE:
		UpdatePhoneType();
		break;

	case ID_CONTEXT_MENU_DELETE:
		DeletePhoneType();
		break;

	case ID_CONTEXT_MENU_INSERT:
		InsertPhoneType();
		break;

	case ID_CONTEXT_MENU_REFRESH:
		RefreshPhoneTypes();
		break;

	default:
		return __super::OnCommand(wParam, lParam);
	}

	return TRUE;
}

void CPhoneTypesView::OnInitialUpdate()
{
	__super::OnInitialUpdate();

	// ������� ���������� �� ���� ����������
	CListCtrl& oListCtrl = GetListCtrl();

	// �������������� ���� ����������
	InitializeListControl(oListCtrl);

	// �������� �������� � ���� ����������
	AddItemsToListControl(oListCtrl);
}
