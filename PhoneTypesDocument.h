#pragma once
#include "AutoFreeMemoryArray.h"
#include "Structures.h"
#include "OnUpdateHints.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDocument

///<summary> ���� �������� �� ������ � ���� �����</summary>
class CPhoneTypesDocument : public CDocument
{
//Macros
// --------------
protected:
	DECLARE_DYNCREATE(CPhoneTypesDocument)
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CPhoneTypesDocument();
	virtual ~CPhoneTypesDocument();


// Methods
// ----------------
public:
	///<summary> ������� �� ��������� �� �����a �� ��������� ������</summary>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL PrepareDocumentData();
	///<summary> ������� �� ����� �� ��������� ��� �� ������</summary>
	///<param name="lID"> �� �� ���������� ��� ����� ������ �� �������� </param>
	///<param name="recPhoneType"> ��������� ������������ ��������� ��� </param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL SelectDataWithID(const long lID, PHONE_TYPES& recPhoneType);
	///<summary> ������� �� �������� �� �� ��������� ��� �� ������</summary>
	///<param name="lID"> �� �� ���������� ��� ����� ������ �� �����������</param>
	///<param name="recPhoneType"> ������ ����� � ����� �� ������� ������� </param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL UpdateData(PHONE_TYPES& recPhoneType);
	///<summary> ������� �� �������� �� ��������� ��� � ������</summary>
	///<param name="recPhoneType"> ������� �� ����� ��������� ��� ����� ������ �� �������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL InsertData(PHONE_TYPES& recPhoneType);
	///<summary> ������� �� ��������� �� ��������� ��� �� ������</summary>
	///<param name="lID"> �� �� ���������� ��� ����� ������ �� �������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL DeleteData(const long lID);

	///<summary> ���������� ������� ����� ���� ���������� �� ������ �� ������ �� ��������� ������</summary>
	///<returns> ����� ���������� �� ������ �� ��������� ������</returns>
	const CPhoneTypesArray& GetDocArray() const;


// Overrides
// ----------------
private:
	///<summary> ������� ������������ �������� ��� ��������� �� ��� ��������</summary>
	virtual BOOL OnNewDocument() override;


// Members
// ----------------
private:
	///<summary> ���� ���������� ����� �� �������� ��������</summary>
	CPhoneTypesArray m_oPhoneTypesArray;
};