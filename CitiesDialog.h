#pragma once
#include "Structures.h"
#include "DialogModes.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesDialog

///<summary> Клас за диалога на градовете</summary>
class CCitiesDialog : public CDialogEx
{
// Macros
// ----------------
	DECLARE_DYNAMIC(CCitiesDialog)

protected:
	DECLARE_MESSAGE_MAP()

	enum { IDD = IDD_DLG_CITIES };


// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	///<summary> Конструктор</summary>
	///<param name="recCity"> Обект от структура CITIES който влиза по референция</param>
	///<param name="oReadWriteEnum"> Подсказка дали трябва да отворим диалога в ReadWrite/ReadOnly</param>
	CCitiesDialog(CITIES& recCity , DialogModes eDialogModes = DialogModeReadWrite , CWnd* pParent = nullptr);
	virtual ~CCitiesDialog();


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
	///<summary> Функция която проверява дали текстовете в едит контролите са валидни</summary>
	///<returns> Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL CheckIsWindowTextValid();
	///<summary> Функция , която записва данните от едит контролите в буфера</summary>
	void SaveDataInBuffer();


// Members
// ----------------
private:
	///<summary> Член променлива едит контрола за името на града</summary>
	CEdit m_edbCityName;
	///<summary> Член променлива едит контрола за областта</summary>
	CEdit m_edbDistrict;
	///<summary> Член променлива референция към структура на град</summary>
	CITIES& m_recCity;
	///<summary> Член променлива(енумератор) флаг за индикация дали е отворено само за четене</summary>
	DialogModes m_eDialogModes;
	///<summary> Член променлива за бутон ОК</summary>
	CButton m_btnOK;
};