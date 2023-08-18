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
const LPCTSTR CCitiesView::lpszMenuRefresh = L"Обновяване";
const LPCTSTR CCitiesView::lpszDeleteMessage = L"Града беше изтрит успешно.";
const LPCTSTR CCitiesView::lpszMessage = L"Съобщение";
const LPCTSTR CCitiesView::lpszConfirmation = L"Наистина ли искате да изтриете града?";
const LPCTSTR CCitiesView::lpszConfirmationMessage = L"Потвърждаване";
const LPCTSTR CCitiesView::lpszMenuView = L"Преглед";
const LPCTSTR CCitiesView::lpszMenuInsert = L"Добавяне";
const LPCTSTR CCitiesView::lpszMenuUpdate = L"Редакция";
const LPCTSTR CCitiesView::lpszMenuDelete = L"Изтриване";


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
	// Викаме функцията GetSelectedCityInListCtrl за да присвоим избрания град
	CITIES recSelectedCity;
	if (!GetSelectedCityInListCtrl(recSelectedCity))
		return;

	// Създаваме обект от диалога и му подаваме град и флаг да го отвори в режим на четене
	CCitiesDialog oCitiesDialog(recSelectedCity, DialogModeReadOnly);

	// Изкаравме диалога
	oCitiesDialog.DoModal();	
}

void CCitiesView::UpdateCity()
{
	// Викаме функцията GetSelectedCityInListCtrl за да присвоим избрания град
	CITIES recSelectedCity;
	if (!GetSelectedCityInListCtrl(recSelectedCity))
		return;

	// Създаваме обект от диалога и му даваме референция на избрания град
	CCitiesDialog oCitiesDialog(recSelectedCity);

	// Изкаравме диалога и при натискане на бутон ОК редактираме града
	if (oCitiesDialog.DoModal() != IDOK)
	{
		return;
	}

	// Създаваме указател към документа за достъп до масива от данни
	CCitiesDocument* pCitiesDoc = GetDocument();
	if (pCitiesDoc == nullptr)
		return;

	// Редактираме града в базата данни
	if (!pCitiesDoc->UpdateData(recSelectedCity))
	{
		MessageBox(_T("Неуспех при редакцията на града."),
			lpszMessage);

		return;
	}
}

void CCitiesView::InsertCity()
{
	// Създаваме обект от диалога и му даваме празен град по референция
	CITIES recCityToInsert;
	CCitiesDialog oCitiesDialog(recCityToInsert);

	// Изкаравме диалога и при натискане на бутон ОК връщаме recCityToInsert напълнен с данни
	if (oCitiesDialog.DoModal() != IDOK)
	{
		return;
	}

	// Създаваме указател към документа за достъп до масива от данни
	CCitiesDocument* pCitiesDoc = GetDocument();
	if (pCitiesDoc == nullptr)
		return;

	// Вмъкваме града в базата данни
	if (!pCitiesDoc->InsertData(recCityToInsert))
	{
		MessageBox(_T("Неуспех при вмъкването на града."),
			lpszMessage);

		return;
	}
}

void CCitiesView::DeleteCity()
{
	// Викаме функцията GetSelectedCityInListCtrl за да присвоим избрания град
	CITIES recDeleteCity;
	if (!GetSelectedCityInListCtrl(recDeleteCity))
		return;

	// Изкарваме съобщение за потвърждаване изтриването на град
	int nMessageBoxResult = MessageBox(lpszConfirmation,
									lpszConfirmationMessage,
								MB_ICONQUESTION | MB_YESNO);

	// Изкаравме диалога и при натискане на бутон YES трием града
	if (nMessageBoxResult != IDYES)
	{
		return;
	}

	// Създаваме указател към документа за достъп до масива от данни
	CCitiesDocument* pCitiesDoc = GetDocument();
	if (pCitiesDoc == nullptr)
		return;

	// Изтриваме града от базата
	if (!pCitiesDoc->DeleteData(recDeleteCity.lID))
	{
		MessageBox(_T("Неуспех при изтриването на града."),
			lpszMessage);

		return;
	}

	// Съобщение за успешно изтрит град
	MessageBox(lpszDeleteMessage,
		lpszMessage);
}

void CCitiesView::RefreshCities()
{
	// Изтриваме елементите от лист контролата и ги пълним наново
	CListCtrl& oListCtrl = GetListCtrl();
	if (!oListCtrl.DeleteAllItems())
	{
		MessageBox(_T("Неуспех при обновяването на даните."),
			lpszMessage);

		return;
	}

	if(!AddItemsToListControl(oListCtrl))
	{
		MessageBox(_T("Неуспех при зареждането на даните."),
			lpszMessage);

		return;
	}
}

void CCitiesView::UpdateInView(const CITIES& recCity)
{
	// Вземаме референция на лист контролата
	CListCtrl& oListCtrl = GetListCtrl();

	// Изцикляме елементите в лист контролата
	for (int nIndex = 0; nIndex < oListCtrl.GetItemCount(); nIndex++)
	{
		if (oListCtrl.GetItemData(nIndex) != (DWORD)recCity.lID)
		{
			continue;
		}

		// След като намерим града който искаме да променим го редактираме в лист контролата
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

		// Прекъсваме цикъла
		break;
	}
}

void CCitiesView::InsertInView(const CITIES& recCity)
{
	// Вземаме референция на лист контролата
	CListCtrl& oListCtrl = GetListCtrl();

	// Вмъкваме в края на лист контролата новия елемент
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
	// Вземаме референция на лист контролата
	CListCtrl& oListCtrl = GetListCtrl();

	// Изцикляме елементите в лист контролата
	for (int nIndex = 0; nIndex < oListCtrl.GetItemCount(); nIndex++)
	{
		if (oListCtrl.GetItemData(nIndex) != (DWORD)recCity.lID)
		{
			continue;
		}

		// След като намерим града който искаме да изтрием го махаме от лист контролата
		if (!oListCtrl.DeleteItem(nIndex))
			return;

		// Прекъсваме цикъла
		break;
	}
}

BOOL CCitiesView::GetSelectedCityInListCtrl(CITIES& recCity)
{
	// Вземаме референция на лист контролата
	CListCtrl& oListCtrl = GetListCtrl();

	// Вземаме индекса на селектирания град
	int nSelectedItemIndex = oListCtrl.GetNextItem(-1, LVNI_SELECTED);

	// В случай , че няма селектиран град
	if (nSelectedItemIndex == CB_ERR)
		return FALSE;

	// Създаваме указател към документа за достъп до масива от данни
	CCitiesDocument* pCitiesDoc = GetDocument();
	if (pCitiesDoc == nullptr)
		return FALSE;

	// Присвояваме ИД-то на града
	const long lID = (long)oListCtrl.GetItemData(nSelectedItemIndex);
	
	// Изтриваме града от базата
	if (!pCitiesDoc->SelectDataWithID(lID, recCity))
	{
		MessageBox(_T("Неуспех при извличането на града."),
			lpszMessage);

		return FALSE;
	}

	return TRUE;
}

void CCitiesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// Кастваме pHint към CITIES и го присвояваме в recCity по референция
	CITIES& recCity = *reinterpret_cast<CITIES*>(pHint);

	// Проверяваме lHint за да насочим към правилната функция
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
	// Добавяме колоните
	if (oListCtrl.InsertColumn(CITY_COLUMN_INDEX, CITY_COLUMN_NAME, LVCFMT_LEFT, CITY_COLUMN_SIZE) == CB_ERR)
		return FALSE;
	if (oListCtrl.InsertColumn(DISTRICT_COLUMN_INDEX, DISTRICT_COLUMN_NAME, LVCFMT_LEFT, DISTRICT_COLUMN_SIZE) == CB_ERR)
		return FALSE;

	// Добавяме свойства на лист контролата
	oListCtrl.ModifyStyle(0, LVS_REPORT);
	oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;
}

BOOL CCitiesView::AddItemsToListControl(CListCtrl& oListCtrl)
{
	// Създаваме указател към документа за достъп до масива от данни
	CCitiesDocument* pCitiesDoc = GetDocument();
	if (pCitiesDoc == nullptr)
		return FALSE;

	const CCitiesArray& oCitiesArray = pCitiesDoc->GetCitiesArray();

	// Пълним колоните на лист контролата с данните от масива ни
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
	// Преобразуваме координатите
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCitiesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	CRect oRect;
	
	// Вземаме координатите на клиента по време на клик-а
	GetClientRect(&oRect);

	// Преобразуваме координатите на клиента в координати на екрана
	ClientToScreen(&oRect);

	CMenu oMainMenu;
	// Проверяваме дали координатите са в обсега
	if (oRect.PtInRect(point))
	{
		// Създаваме менюто
		oMainMenu.CreatePopupMenu();
		oMainMenu.AppendMenu(MF_STRING, ID_CONTEXT_MENU_SELECT , lpszMenuView);
		oMainMenu.AppendMenu(MF_STRING, ID_CONTEXT_MENU_INSERT , lpszMenuInsert);
		oMainMenu.AppendMenu(MF_STRING, ID_CONTEXT_MENU_UPDATE , lpszMenuUpdate);
		oMainMenu.AppendMenu(MF_STRING, ID_CONTEXT_MENU_DELETE , lpszMenuDelete);
		oMainMenu.AppendMenu(MF_STRING, ID_CONTEXT_MENU_REFRESH, lpszMenuRefresh);
	}

	// Показваме менюто вляво от клик-а
	oMainMenu.TrackPopupMenu(TPM_LEFTALIGN,point.x, point.y, this);
}

void CCitiesView::OnItemDoubleClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	// Избираме града
	SelectCity();
}

BOOL CCitiesView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// switch-case за да препратим към правилната функция
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

	// Вземаме референция на лист контролата
	CListCtrl& oListCtrl = GetListCtrl();

	// Инициализираме лист контролата
	if (!InitializeListControl(oListCtrl))
	{
		MessageBox(_T("Неуспех при инициализация на лист контролата."),
			lpszMessage);

		return;
	}

	// Добавяме елементи в лист контролата
	if(!AddItemsToListControl(oListCtrl))
	{
		MessageBox(_T("Неуспех при добавяне на елементи в лист контролата."),
			lpszMessage);

		return;
	}
}
