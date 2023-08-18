#pragma once

#include "Structures.h"
#include "PersonsInformation.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersDialog

class CPhoneNumbersDialog : public CDialogEx
{
// Macros
// ----------------
	DECLARE_DYNAMIC(CPhoneNumbersDialog)
	DECLARE_MESSAGE_MAP()

	enum { IDD = IDD_DLG_PHONE_NUMBERS };


// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	///<summary> Конструктор който приема референция за номера</summary>
	CPhoneNumbersDialog(PHONE_NUMBERS& recPhoneNumber , CWnd* pParent = nullptr);
	virtual ~CPhoneNumbersDialog();


// MFC Overrides
// ----------------
protected:
	///<summary> Функция за обмяна на данни</summary>
	virtual void DoDataExchange(CDataExchange* pDX) override;
	///<summary> Функция която се вика при първоначално зареждане на диалога</summary>
	virtual BOOL OnInitDialog() override;
	///<summary> Функция която се вика при натискане на бутона ОК</summary>
	afx_msg void OnOK() override;


// MFC Message Handlers
// ----------------


// Overrides
// ----------------


// Methods
// ----------------
private:
	///<summary> Функция която проверява дали текстовете в диалога са валидни</summary>
	///<returns> Връща TRUE ако са и FALSE ако не са </returns>
	BOOL CheckIsWindowTextValid();
	///<summary> Функция , която записва данните от диалога в буфера</summary>
	void SaveDataInBuffer();

public:
	///<summary> Функция за напълване на масива с телефонни типове</summary>
	///<param name="oPhoneTypesArray"> Масива от който ще пълним нашия</param>
	void FillPhoneTypesArray(const CPhoneTypesArray& oPhoneTypesArray);


// Members
// ----------------
private:
	///<summary> Член променлива референция за телефонния номер</summary>
	PHONE_NUMBERS& m_recPhoneNumber;
	///<summary> Член променлива за едит контрола на телефонен номер</summary>
	CEdit m_edbPhoneNumbersPhoneNumber;
	///<summary> Член променлива масив за телефонни типове</summary>
	CPhoneTypesArray m_oPhoneTypesArray;
	///<summary> Член променлива комбо бокс за телефонен тип</summary>
	CComboBox m_cmbPhoneTypesType;
};
