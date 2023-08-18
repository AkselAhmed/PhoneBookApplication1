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
#define FIRST_NAME_COLUMN_NAME _T("Име")
#define FIRST_NAME_COLUMN_SIZE 150
#define SECOND_NAME_COLUMN_INDEX 1
#define SECOND_NAME_COLUMN_NAME _T("Презиме")
#define SECOND_NAME_COLUMN_SIZE 150
#define THIRD_NAME_COLUMN_INDEX 2
#define THIRD_NAME_COLUMN_NAME _T("Фамилия")
#define THIRD_NAME_COLUMN_SIZE 150
#define EGN_COLUMN_INDEX 3
#define EGN_COLUMN_NAME _T("ЕГН")
#define EGN_COLUMN_SIZE 150
#define PERSON_CITY_COLUMN_INDEX 4
#define PERSON_CITY_COLUMN_NAME _T("Град")
#define PERSON_CITY_COLUMN_SIZE 150
#define ADDRESS_COLUMN_INDEX 5
#define ADDRESS_COLUMN_NAME _T("Адрес")
#define ADDRESS_COLUMN_SIZE 150

const LPCTSTR CPersonsView::lpszMenuRefresh = L"Обновяване";
const LPCTSTR CPersonsView::lpszDeleteMessage = L"Записа беше изтрит успешно.";
const LPCTSTR CPersonsView::lpszMessage = L"Съобщение";
const LPCTSTR CPersonsView::lpszConfirmation = L"Наистина ли искате да изтриете записа?";
const LPCTSTR CPersonsView::lpszConfirmationMessage = L"Потвърждаване";
const LPCTSTR CPersonsView::lpszMenuView = L"Преглед";
const LPCTSTR CPersonsView::lpszMenuInsert = L"Добавяне";
const LPCTSTR CPersonsView::lpszMenuUpdate = L"Редакция";
const LPCTSTR CPersonsView::lpszMenuDelete = L"Изтриване";

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
	// Викаме функцията GetSelectedPersonInListCtrl за да присвоим избрания човек
	CPersonInformation oPersonsInformation;

	if (!GetSelectedPersonInListCtrl(oPersonsInformation))
		return;

	CPersonsDocument* pPersonsDoc = GetDocument();
	if (pPersonsDoc == nullptr)
		return;

	// Създаваме обект от диалога и му даваме човек и флаг да го отвори в режим на четене
	CPersonsDialog oPersonDialog(oPersonsInformation, DialogModeReadOnly);

	// Зареждаме масива с градове и масива с типове телефони
	oPersonDialog.FillCitiesArray(pPersonsDoc->GetDocCitiesArray());
	oPersonDialog.FillPhoneTypesArray(pPersonsDoc->GetDocPhoneTypesArray());

	// Изкаравме диалога
	oPersonDialog.DoModal();
}

void CPersonsView::UpdatePerson()
{
	// Викаме функцията GetSelectedPersonInListCtrl за да присвоим избрания човек
	CPersonInformation oPersonsInformation;
	if (!GetSelectedPersonInListCtrl(oPersonsInformation))
		return;

	CPersonsDocument* pPersonsDoc = GetDocument();
	if (pPersonsDoc == nullptr)
		return;

	// Създаваме обект от диалога и му даваме човек
	CPersonsDialog oPersonDialog(oPersonsInformation);

	// Зареждаме масива с градове и масива с типове телефони
	oPersonDialog.FillCitiesArray(pPersonsDoc->GetDocCitiesArray());
	oPersonDialog.FillPhoneTypesArray(pPersonsDoc->GetDocPhoneTypesArray());

	// Изкаравме диалога и при натискане на бутон ОК редактираме човека и номерата му
	if (oPersonDialog.DoModal() != IDOK)
	{
		return;
	}

	// Редактираме човека и номерата му в базата данни
	if (!pPersonsDoc->UpdateData(oPersonsInformation))
		return;
}

void CPersonsView::InsertPerson()
{
	CPersonInformation oPersonsInformation;

	// Създаваме обект от диалога и му даваме град
	CPersonsDialog oPersonDialog(oPersonsInformation);

	CPersonsDocument* pPersonsDoc = GetDocument();
	if (pPersonsDoc == nullptr)
		return;
	// Зареждаме масива с градове и масива с типове телефони
	oPersonDialog.FillCitiesArray(pPersonsDoc->GetDocCitiesArray());
	oPersonDialog.FillPhoneTypesArray(pPersonsDoc->GetDocPhoneTypesArray());

	// Изкаравме диалога и при натискане на бутон ОК добавяме града
	if (oPersonDialog.DoModal() != IDOK)
	{
		return;
	}

	// Вмъкваме човека и телефонните му номера в базата данни
	if (!pPersonsDoc->InsertData(oPersonsInformation))
		return;
}

void CPersonsView::DeletePerson()
{
	CPersonInformation oPersonsInformation;
	if (!GetSelectedPersonInListCtrl(oPersonsInformation))
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

	// Изтриваме града от базата данни
	long lID = oPersonsInformation.GetPerson().lID;
	if (!GetDocument()->DeleteData(lID))
		return;

	// Съобщение за успешно изтрит град
	MessageBox(lpszDeleteMessage,
		lpszMessage);
}

void CPersonsView::RefreshPersons()
{
	// Изтриваме елементите от лист контролата и ги пълним наново
	CListCtrl& oListCtrl = GetListCtrl();
	if (!oListCtrl.DeleteAllItems())
	{
		MessageBox(L"Неуспешно презареждане на хората.",
			lpszMessage);

		return;
	}
	AddItemsToListControl(oListCtrl);
}

void CPersonsView::UpdateInView(const PERSONS& recPerson)
{
	// Вземаме референция на лист контролата
	CListCtrl& oListCtrl = GetListCtrl();

	// Изцикляме елементите в лист контролата
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

		// Прекъсваме цикъла
		break;
	}
}

void CPersonsView::InsertInView(const PERSONS& recPerson)
{
	// Вземаме референция на лист контролата
	CListCtrl& oListCtrl = GetListCtrl();

	long lID = recPerson.lCityID;
	CCitiesData oCitiesData;
	CITIES recCity;
	if (!oCitiesData.SelectCityWithID(lID, recCity))
		return;

	// Вмъкваме в края на лист контролата новия елемент
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
	// Вземаме референция на лист контролата
	CListCtrl& oListCtrl = GetListCtrl();

	// Изцикляме елементите в лист контролата
	for (int nIndex = 0; nIndex < oListCtrl.GetItemCount(); nIndex++)
	{
		if (oListCtrl.GetItemData(nIndex) != (DWORD)recPerson.lID)
		{
			continue;
		}

		// След като намерим града който искаме да изтрием го махаме от лист контролата
		oListCtrl.DeleteItem(nIndex);

		// Прекъсваме цикъла
		break;
	}
}

BOOL CPersonsView::GetSelectedPersonInListCtrl(CPersonInformation& recPerson)
{
	// Вземаме референция на лист контролата
	CListCtrl& oListCtrl = GetListCtrl();

	// Вземаме индекса на селектирания човек
	int nSelectedItemIndex = oListCtrl.GetNextItem(-1, LVNI_SELECTED);

	// В случай , че няма селектиран човек
	if (nSelectedItemIndex == CB_ERR)
		return FALSE;

	// Създаваме обект от CPersonsDocument за достъп до масива от данни
	CPersonsDocument* pPersonsDocument = GetDocument();
	if (pPersonsDocument == nullptr)
		return FALSE;

	const long lID = (long)oListCtrl.GetItemData(nSelectedItemIndex);

	// Вземаме избрания град и го присвояваме
	if (!pPersonsDocument->SelectDataWithID(lID, recPerson))
		return FALSE;

	return TRUE;
}

void CPersonsView::OnUpdate(CView * pSender, LPARAM lHint, CObject * pHint)
{
	// Cast-ваме pHint-а в PERSONS
	PERSONS& recPerson = *reinterpret_cast<PERSONS*>(pHint);

	// Проверяваме lHint за да насочим към правилната функция
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
	// Добавяме колоните
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

	// Добавяме свойства на лист контролата
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

	// Пълним колоните на лист контролата с данните от масива ни
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

void CPersonsView::OnItemDoubleClick(NMHDR * pNMHDR, LRESULT * pResult)
{
	SelectPerson();
}

BOOL CPersonsView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// switch-case за да препратим към правилната функция
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

	// Вземаме референция на лист контролата
	CListCtrl& oListCtrl = GetListCtrl();

	// Инициализираме лист контролата
	InitializeListControl(oListCtrl);

	// Добавяме елементи в лист контролата
	AddItemsToListControl(oListCtrl);
}
