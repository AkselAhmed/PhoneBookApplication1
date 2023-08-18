#pragma once
#include "Structures.h"

#define ACCESSOR_ID 0
#define ACCESSOR_WITHOUT_ID 1

/////////////////////////////////////////////////////////////////////////////
// CBaseAccessor

///<summary> ����� ���������� ���� �� ����������</summary> 
///<param name="RecordType"> ��� �� �����������</param>
template<typename RecordType>
class CBaseAccessor
{
// Macros
// ----------------


// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CBaseAccessor()
	{
	}
	virtual ~CBaseAccessor()
	{
	}

// Methods
// ----------------
public:
	///<summary> ������� ����� ���� ������ �� ���� ������������ �� ��������</summary>
	///<returns> ����� ���������� �� ���� ������������</returns>
	virtual RecordType& GetAccessor() = 0;
	///<summary> ������� ����� ���� ������ �� UpdateCounter-� �� ���� ������������ �� ��������</summary>
	///<returns> ����� ���������� �� UpdateCounter-� �� ���� ������������</returns>
	virtual long& GetAccessorUpdateCounter() = 0;


// Overrides
// ----------------


// Members
// ----------------
protected:
	///<summary> ���� ���������� �� ��� RecordType</summary>
	RecordType m_recRecord;
};
