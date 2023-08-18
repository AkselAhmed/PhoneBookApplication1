#pragma once
#include "AutoFreeMemoryArray.h"
#include "Structures.h"
#include "OnUpdateHints.h"
#include "PersonsInformation.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsDocument

///<summary> ���� �������� , ����� ��������� ������� �� ������</summary>
class CPersonsDocument : public CDocument
{
//Macros
// --------------
protected:
	DECLARE_DYNCREATE(CPersonsDocument)
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CPersonsDocument();
	virtual ~CPersonsDocument();


// Methods
// ----------------
public:
	///<summary> ������� �� ��������� �� ������ �� ������� , ���� � ��������� ������</summary>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL PrepareDocumentData();
	
	///<summary> ������� �� ��������� �� ������ �� ����</summary>
	///<param name="oPersonsArray"> ������ � ����� ��������� ������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL SelectAllPersons(CPersonsArray& oPersonsArray);
	///<summary> ������� �� ����� �� ����� � ����������� �� ������ </summary>
	///<param name="lID"> �� �� �������� ����� ������ �� �������� </param>
	///<param name="recPerson"> ��������� ������������ ����� </param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL SelectDataWithID(const long lID, CPersonInformation& recPersons);
	///<summary> ������� �� �������� �� ����� � ����������� �� ������</summary>
	///<param name="recPerson"> ������ ����� � ����� �� ������� ������� </param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL UpdateData(CPersonInformation& recPerson);
	///<summary> ������� �� �������� �� �� ����� � ����������� �� ������</summary>
	///<param name="recPerson"> ������� �� ����� ����� ����� ������ �� �������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL InsertData(CPersonInformation& recPerson);
	///<summary> ������� �� ��������� �� ����� � ����������� �� ������</summary>
	///<param name="lID"> �� �� �������� ����� ������ �� �������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL DeleteData(const long lID);

	///<summary> ���������� ������� ����� ���� ���������� �� ������ �� ������ �� ����</summary>
	///<returns> ����� ���������� �� ������ �� ����</returns>
	const CPersonsArray& GetDocArray() const;
	///<summary> ���������� ������� ����� ���� ���������� �� ������ �� ������ �� �������</summary>
	///<returns> ����� ���������� �� ������ �� �������</returns>
	const CCitiesArray& GetDocCitiesArray() const;
	///<summary> ���������� ������� ����� ���� ���������� �� ������ �� ������ �� ��������� ������</summary>
	///<returns> ����� ���������� �� ������ �� ��������� ������</returns>
	const CPhoneTypesArray& GetDocPhoneTypesArray() const;


// Overrides
// ----------------
private:
	///<summary> ������� ������������ �������� ��� ��������� �� ��� ��������</summary>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	virtual BOOL OnNewDocument() override;


// Members
// ----------------
private:
	///<summary> ���� ���������� ����� �� ����</summary>
	CPersonsArray m_oPersonsArray;
	///<summary> ���� ���������� ����� �� �������</summary>
	CCitiesArray m_oCitiesArray;
	///<summary> ���� ���������� ����� �� ������ ��������</summary>
	CPhoneTypesArray m_oPhoneTypesArray;
};