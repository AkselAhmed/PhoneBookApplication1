#pragma once
#include <atldbcli.h>


/////////////////////////////////////////////////////////////////////////////
// CAutoFreeMemoryArray


///<summary> ���������� ���� ����� ����������� �������� ������� �� � ��������� CTypedPtrArray</summary>
///<param name="ArrayType"> ��� �� ������</param>
template<typename ArrayType>
class CAutoFreeMemoryArray : public CTypedPtrArray<CPtrArray,ArrayType>
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CAutoFreeMemoryArray() {}
	///<summary> ���������� , ����� ����������� �������� ������� �� ������</summary>
	virtual ~CAutoFreeMemoryArray()
	{
		const INT_PTR nFirst = 0;
		while(GetCount() > nFirst)
		{
			Delete(nFirst);
		}

		RemoveAll();
	}


// Methods
// ----------------
	///<summary> ������� ����� ������� ������� � �������� �������</summary>
	///<param name="nIndex"> ������� �� ����� ��������� ��������</param> 
	void Delete(const INT_PTR nIndex)
	{
		ArrayType pType = GetAt(nIndex);
		if (pType == nullptr)
			return;

		delete pType;
		pType = nullptr;

		// ��������� ����� �� ������
		RemoveAt(nIndex);
	}
	
	///<summary> ������� ����� ������ ����� ��� �������� �� �����</summary>
	///<param name="oArray"> ������ �� ����� �� �������� ����������</param> 
	void CopyArray(const CAutoFreeMemoryArray<ArrayType>& oArray)
	{
		for (INT_PTR nIndex = 0; nIndex < oArray.GetCount(); nIndex++)
		{
			ArrayType pType = oArray.GetAt(nIndex);
			if (pType == nullptr)
				continue;

			// �������� �� ����� �� ����� ��������
			ArrayType pNewType = new typename std::remove_pointer<ArrayType>::type();
			*pNewType = *pType;

			Add(pNewType);
		}
	}


// Overrides
// ----------------


// Members
// ----------------
};