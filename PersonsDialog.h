#pragma once
#include "Structures.h"
#include "DialogModes.h"
#include "PersonsInformation.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsDialog

///<summary> Клас за диалога на хората</summary>
class CPersonsDialog : public CDialogEx
{
// Macros
// ----------------
	DECLARE_DYNAMIC(CPersonsDialog)
protected:
	DECLARE_MESSAGE_MAP()

	enum { IDD = IDD_DLG_PERSONS };


// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	///<summary> Конструктор който работи с подадената референция</summary>
	///<param name="oPersonsInformation">Информация за човека и телефонните му номера</param>
	///<param name="eDialogModes">Флаг за четене / четене и запис</param>
	CPersonsDialog(CPersonInformation& oPersonsInformation, DialogModes eDialogModes = DialogModeReadWrite, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPersonsDialog();


// MFC Overrides
// ----------------
protected:
	///<summary> Функция за обмяна на данни</summary>
	virtual void DoDataExchange(CDataExchange* pDX) override;
	///<summary> Функция която се вика при първоначално зареждане на диалога</summary>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	virtual BOOL OnInitDialog() override;
	///<summary> Функция която се вика при натискане на бутона ОК</summary>
	afx_msg void OnOK() override;


// MFC Message Handlers
// ----------------
protected:
	///<summary> Функция за създаване на контекстно меню</summary>
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);


// Overrides
// ----------------
	///<summary> Функция която препраща към избраната от менюто команда</summary>
	afx_msg BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;


// Methods
// ----------------
private:
	///<summary> Функция която проверява дали текста в едит контролите са валидни</summary>
	///<returns> Връща TRUE ако са и FALSE ако не са</returns>
	BOOL CheckIsWindowTextValid();
	///<summary> Функция , която записва данните от едит контролите в буфера</summary>
	void SaveDataInBuffer();
	///<summary> Функция която отваря диалога за телефонни номера за вмъкване на телефонен номер</summary>
	void InsertPhoneNumber();
	///<summary> Функция която отваря диалога за телефонни номера за редактиране на телефонен номер</summary>
	void UpdatePhoneNumber();
	///<summary> Функция за изтриване на телефонен номер</summary>
	void DeletePhoneNumber();

public:
	///<summary> Функция за запълване на масива с градове</summary>
	///<param name="oCitiesArray"> Масива от който ще пълним нашия</param>
	void FillCitiesArray(const CCitiesArray& oCitiesArray);
	///<summary> Функция за запълване на масива с телефонни типове</summary>
	///<param name="oPhoneTypesArray"> Масива от който ще пълним нашия</param>
	void FillPhoneTypesArray(const CPhoneTypesArray& oPhoneTypesArray);


// Members
// ----------------
private:
	///<summary> Член променлива едит контрола за име</summary>
	CEdit m_edbPersonsFirstName;
	///<summary> Член променлива едит контрола за адрес</summary>
	CEdit m_edbPersonsAddress;
	///<summary> Член променлива от тип транспортен клас за човека и телефонните му номера</summary>
	CPersonInformation& m_oPersonsInformation;
	///<summary> Член променлива enum за разпознаване дали диалога е отворен за четене</summary>
	DialogModes m_eDialogModes;
	///<summary> Член променлива едит контрола за презиме</summary>
	CEdit m_edbPersonsSecondName;
	///<summary> Член променлива едит контрола за фамилия</summary>
	CEdit m_edbPersonsThirdName;
	///<summary> Член променлива едит контрола за ЕГН</summary>
	CEdit m_edbPersonsEgn;
	///<summary> Член променлива комбо бокс за град</summary>
	CComboBox m_cmbPersonsCity;
	///<summary> Член променлива масив за градовете</summary>
	CCitiesArray m_oCitiesArray;
	///<summary> Член променлива за бутон ОК</summary>
	CButton m_btnOK;
	///<summary> Член променлива listbox за телефонните номера на човек</summary>
	CListBox m_lsbPersonsPhoneNumbers;
	///<summary> Член променлива масив за телефонните типове</summary>
	CPhoneTypesArray m_oPhoneTypesArray;
};
