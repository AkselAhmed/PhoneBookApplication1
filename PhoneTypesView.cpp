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
#define ERROR_SAVING_PHONE_TYPE _T("Неуспешно записване на телефонния тип.")
#define ERROR_DELETING_PHONE_TYPE _T("Неуспешно изтриване на телефонния тип.")


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
const LPCTSTR CPhoneTypesView::lpszMenuRefresh = L"Обновяване";
const LPCTSTR CPhoneTypesView::lpszDeleteMessage = L"Телефонния тип беше изтрит успешно.";
const LPCTSTR CPhoneTypesView::lpszMessage = L"Съобщение";
const LPCTSTR CPhoneTypesView::lpszConfirmation = L"Наистина ли искате да изтриете телефонния тип?";
const LPCTSTR CPhoneTypesView::lpszConfirmationMessage = L"Потвърждаване";
const LPCTSTR CPhoneTypesView::lpszMenuView = L"Преглед";
const LPCTSTR CPhoneTypesView::lpszMenuInsert = L"Добавяне";
const LPCTSTR CPhoneTypesView::lpszMenuUpdate = L"Редакция";
const LPCTSTR CPhoneTypesView::lpszMenuDelete = L"Изтриване";


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
	// Викаме функцията GetSelectedPhoneTypeInListCtrl за да присвоим избрания телефонен тип
	PHONE_TYPES recSelectedPhoneType;
	if (!GetSelectedPhoneTypeInListCtrl(recSelectedPhoneType))
		return;

	// Създаваме обект от диалога и му даваме телефонен тип и флаг да го отвори в режим на четене
	CPhoneTypesDialog oPhoneTypesDialog(recSelectedPhoneType, DialogModeReadOnly);

	// Изкаравме диалога
	oPhoneTypesDialog.DoModal();
}

void CPhoneTypesView::UpdatePhoneType()
{
	// Викаме функцията GetSelectedPhoneTypeInListCtrl за да присвоим избрания телефонен тип
	PHONE_TYPES recSelectedPhoneType;
	if (!GetSelectedPhoneTypeInListCtrl(recSelectedPhoneType))
		return;

	// Създаваме обект от диалога и му даваме телефонен тип
	CPhoneTypesDialog oPHONE_TYPESDialog(recSelectedPhoneType);

	// Изкаравме диалога и при натискане на бутон ОК редактираме телефонния тип
	if (oPHONE_TYPESDialog.DoModal() != IDOK)
	{
		return;
	}

	CPhoneTypesDocument* pPhoneTypesDocument = GetDocument();
	if (pPhoneTypesDocument == nullptr)
		return;

	// Редактираме телефонния тип в базата данни
	if (!pPhoneTypesDocument->UpdateData(recSelectedPhoneType))
	{
		MessageBox(L"Грешка при редакцията на телефонен тип.",
			L"Съобщение");

		return;
	}
}

void CPhoneTypesView::InsertPhoneType()
{
	PHONE_TYPES recPhoneTypeToInsert;

	// Създаваме обект от диалога и му даваме телефонен тип
	CPhoneTypesDialog oPhoneTypesDialog(recPhoneTypeToInsert);

	// Изкаравме диалога и при натискане на бутон ОК добавяме телефонния тип
	if (oPhoneTypesDialog.DoModal() != IDOK)
	{
		return;
	}

	// Създаваме обект от CPhoneTypesDocument за достъп до масива от данни
	CPhoneTypesDocument* pPhoneTypesDocument = GetDocument();
	if (pPhoneTypesDocument == nullptr)
		return;

	// Вмъкваме телефонен типа в базата данни
	if (!pPhoneTypesDocument->InsertData(recPhoneTypeToInsert))
	{
		MessageBox(L"Грешка при вмъкването на телефонен тип.",
			L"Съобщение");

		return;
	}
}

void CPhoneTypesView::DeletePhoneType()
{
	// Викаме функцията GetSelectedPhoneTypeInListCtrl за да присвоим избрания телефонен тип
	PHONE_TYPES recDeletePhoneType;
	if (!GetSelectedPhoneTypeInListCtrl(recDeletePhoneType))
		return;

	// Изкарваме съобщение за потвърждаване изтриването на телефонен тип
	int nMessageBoxResult = MessageBox(lpszConfirmation,
		lpszConfirmationMessage,
		MB_ICONQUESTION | MB_YESNO);

	// Изкаравме диалога и при натискане на бутон YES трием телефонния тип
	if (nMessageBoxResult != IDYES)
	{
		return;
	}

	// Изтриваме телефонния тип от базата данни
	const long lID = recDeletePhoneType.lID;

	// Създаваме обект от CPhoneTypesDocument за достъп до масива от данни
	CPhoneTypesDocument* pPhoneTypesDocument = GetDocument();
	if (pPhoneTypesDocument == nullptr)
		return;

	if (!pPhoneTypesDocument->DeleteData(lID))
	{
		MessageBox(L"Грешка при изтриването на телефонен тип.",
			L"Съобщение");

		return;
	}

	// Съобщение за успешно изтрит телефонен тип
	MessageBox(lpszDeleteMessage,
		lpszMessage);
}

void CPhoneTypesView::RefreshPhoneTypes()
{
	// Изтриваме елементите от лист контролата и ги пълним наново
	CListCtrl& oListCtrl = GetListCtrl();
	if (!oListCtrl.DeleteAllItems())
	{
		MessageBox(L"Неуспех при обновяването на данните.",
			lpszMessage);

		return;
	}
	AddItemsToListControl(oListCtrl);
}

void CPhoneTypesView::UpdateInView(const PHONE_TYPES& recPhoneType)
{
	// Вземаме референция на лист контролата
	CListCtrl& oListCtrl = GetListCtrl();

	// Изцикляме елементите в лист контролата
	for (int nIndex = 0; nIndex < oListCtrl.GetItemCount(); nIndex++)
	{
		if (oListCtrl.GetItemData(nIndex) != (DWORD)recPhoneType.lID)
		{
			continue;
		}

		// След като намерим телефонен типа който искаме да променим го редактираме в лист контролата
		if (!oListCtrl.SetItemText(nIndex, PHONE_TYPE_COLUMN_INDEX, recPhoneType.szType))
		{
			MessageBox(ERROR_SAVING_PHONE_TYPE,
				lpszConfirmationMessage);

			return;
		}

		// Прекъсваме цикъла
		break;
	}
}

void CPhoneTypesView::InsertInView(const PHONE_TYPES& recPhoneType)
{
	// Вземаме референция на лист контролата
	CListCtrl& oListCtrl = GetListCtrl();

	// Вмъкваме в края на лист контролата новия елемент
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
	// Вземаме референция на лист контролата
	CListCtrl& oListCtrl = GetListCtrl();

	// Изцикляме елементите в лист контролата
	for (int nIndex = 0; nIndex < oListCtrl.GetItemCount(); nIndex++)
	{
		if (oListCtrl.GetItemData(nIndex) != (DWORD)recPhoneType.lID)
		{
			continue;
		}

		// След като намерим телефонен типа който искаме да изтрием го махаме от лист контролата
		if (!oListCtrl.DeleteItem(nIndex))
		{
			MessageBox(ERROR_DELETING_PHONE_TYPE,
				lpszConfirmationMessage);

			return;
		}

		// Прекъсваме цикъла
		break;
	}
}

BOOL CPhoneTypesView::GetSelectedPhoneTypeInListCtrl(PHONE_TYPES& recPhoneType)
{
	// Вземаме референция на лист контролата
	CListCtrl& oListCtrl = GetListCtrl();

	// Вземаме индекса на селектирания телефонен тип
	int nSelectedItemIndex = oListCtrl.GetNextItem(-1, LVNI_SELECTED);

	// В случай , че няма селектиран телефонен тип
	if (nSelectedItemIndex == CB_ERR)
		return FALSE;

	// Създаваме обект от CPhoneTypesDocument за достъп до масива от данни
	CPhoneTypesDocument* pPhoneTypesDocument = GetDocument();
	if (pPhoneTypesDocument == nullptr)
		return FALSE;

	const long lID = (long)oListCtrl.GetItemData(nSelectedItemIndex);

	// Вземаме избрания телефонен тип и го присвояваме
	if (!pPhoneTypesDocument->SelectDataWithID(lID, recPhoneType))
		return FALSE;

	return TRUE;
}

void CPhoneTypesView::InitializeListControl(CListCtrl& oListCtrl)
{
	// Добавяме колоните
	if (oListCtrl.InsertColumn(PHONE_TYPE_COLUMN_INDEX, PHONE_TYPE_COLUMN_NAME, LVCFMT_LEFT, PHONE_TYPE_COLUMN_SIZE) == CB_ERR)
	{
		MessageBox(L"Неуспешно зареждане на колоните.",
			lpszMessage);

		return;
	}

	// Добавяме свойства на лист контролата
	oListCtrl.ModifyStyle(0, LVS_REPORT);
	oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}

void CPhoneTypesView::AddItemsToListControl(CListCtrl& oListCtrl)
{
	// Създаваме обект от документа за достъп до масива
	CPhoneTypesDocument* pPhoneTypesDocument = GetDocument();
	if (pPhoneTypesDocument == nullptr)
		return;

	// Пълним колоните на лист контролата с данните от масива ни
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
			MessageBox(L"Неуспешно записване на датата.",
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

	// Използваме oRect за GetClientRect да вземем координатите на клиента по време на клик-а
	GetClientRect(&oRect);

	// Преобразуваме координатите на клиента в координати на екрана
	ClientToScreen(&oRect);

	// Проверяваме дали координатите са в обсега
	if (oRect.PtInRect(point))
	{
		// Създаваме менюто
		oMainMenu.CreatePopupMenu();
		oMainMenu.AppendMenu(MF_STRING, ID_CONTEXT_MENU_SELECT, lpszMenuView);
		oMainMenu.AppendMenu(MF_STRING, ID_CONTEXT_MENU_INSERT, lpszMenuInsert);
		oMainMenu.AppendMenu(MF_STRING, ID_CONTEXT_MENU_UPDATE, lpszMenuUpdate);
		oMainMenu.AppendMenu(MF_STRING, ID_CONTEXT_MENU_DELETE, lpszMenuDelete);
		oMainMenu.AppendMenu(MF_STRING, ID_CONTEXT_MENU_REFRESH, lpszMenuRefresh);
	}

	// Показваме менюто вляво от клик-а
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
	// Кастваме pHint към PHONE_TYPES и го присвояваме в recPhoneType
	PHONE_TYPES& recPhoneType = *reinterpret_cast<PHONE_TYPES*>(pHint);

	// Проверяваме lHint за да насочим към правилната функция
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
	// switch-case за да препратим към правилната функция
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

	// Вземаме референция на лист контролата
	CListCtrl& oListCtrl = GetListCtrl();

	// Инициализираме лист контролата
	InitializeListControl(oListCtrl);

	// Добавяме елементи в лист контролата
	AddItemsToListControl(oListCtrl);
}
