#pragma once
#include "AutoFreeMemoryArray.h"
#include "Structures.h"
#include "OnUpdateHints.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesDocument

///<summary> ���� �������� , ����� ��������� ������� �� ������� CITIES</summary>
class CCitiesDocument : public CDocument
{
//Macros
// --------------
protected:
	DECLARE_DYNCREATE(CCitiesDocument)
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CCitiesDocument();
	virtual ~CCitiesDocument();


// Methods
// ----------------
public:
	///<summary> ������� �� ����� �� ������ �������� �� ������� CITIES</summary>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL PrepareDocumentData();
	///<summary> ������� �� ����� �� ������� �� ID �� ������� CITIES </summary>
	///<param name="lID"> ID �� �������� ����� ������ �� �������� </param>
	///<param name="recCity"> ��������� ������������ ���� , ������������ � ������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL SelectDataWithID(const long lID, CITIES& recCity);
	///<summary> ������� �� �������� �� ������� �� ������� CITIES , ��������� ����� ������� � recCity</summary>
	///<param name="recCity"> ������ ����� � ����� �� ������� ������� </param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL UpdateData(CITIES& recCity);
	///<summary> ������� �� �������� �� ������� � ������� CITIES </summary>
	///<param name="recCity"> ������� �� ����� ���� ����� ������ �� �������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL InsertData(CITIES& recCity);
	///<summary> ������� �� ��������� �� ������� �� ������� CITIES</summary>
	///<param name="lID"> ID �� �������� ����� ������ �� �������</param>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	BOOL DeleteData(const long lID);

	///<summary> ������� ����� ���� ������ �� ������ �� ���������</summary>
	///<returns> ����� ���������� ���������� �� ������ �� ������� m_oCitiesArray </returns>
	const CCitiesArray& GetCitiesArray() const;



// Overrides
// ----------------
private:
	///<summary> ������� ������������ �������� ��� ��������� �� ��� ��������</summary>
	///<returns> ����� TRUE ��� ����� � FALSE ��� ������� </returns>
	virtual BOOL OnNewDocument() override;


// Members
// ----------------
private:
	///<summary> ����� �� ���������</summary>
	CCitiesArray m_oCitiesArray;
};