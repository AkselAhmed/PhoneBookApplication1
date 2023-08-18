#pragma once
#include "Structures.h"
#include "DialogModes.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDialog

///<summary> Клас за диалога на типовете телефони</summary>
class CPhoneTypesDialog : public CDialogEx
{
// Macros
// ----------------
	DECLARE_DYNAMIC(CPhoneTypesDialog)

protected:
	DECLARE_MESSAGE_MAP()

	enum { IDD = IDD_DLG_PHONE_TYPES };


// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	///<summary> Конструктор</summary>
	///<param name="recPhoneType"> Обект от структура PHONE_TYPES която влиза по референция</param>
	///<param name="oReadWriteEnum"> Подсказка дали трябва да отворим диалога в ReadWrite/ReadOnly</param>
	CPhoneTypesDialog(PHONE_TYPES& recPhoneType, DialogModes eDialogModes = DialogModeReadWrite, CWnd* pParent = nullptr);
	virtual ~CPhoneTypesDialog();


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
	///<summary> Функция която проверява дали текста в едит контролите са валидни</summary>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL CheckIsWindowTextValid();
	///<summary> Функция , която записва данните от едит контролите в буфера</summary>
	void SaveDataInBuffer();


// Members
// ----------------
private:
	///<summary> Член променлива едит контрола за телефонния тип</summary>
	CEdit m_edbPhoneTypesPhoneType;
	///<summary> Член променлива от тип структура PHONE_TYPES</summary>
	PHONE_TYPES& m_recPhoneType;
	///<summary> Член променлива(енумератор) флаг за индикация дали е отворено само за четене</summary>
	DialogModes m_eDialogModes;
	///<summary> Член променлива за бутон ОК</summary>
	CButton m_btnOK;
};