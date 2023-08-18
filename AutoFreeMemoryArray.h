#pragma once
#include <atldbcli.h>


/////////////////////////////////////////////////////////////////////////////
// CAutoFreeMemoryArray


///<summary> Темплейтен клас който автоматично зачиства паметта си и наследява CTypedPtrArray</summary>
///<param name="ArrayType"> Тип на масива</param>
template<typename ArrayType>
class CAutoFreeMemoryArray : public CTypedPtrArray<CPtrArray,ArrayType>
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CAutoFreeMemoryArray() {}
	///<summary> Деструктор , който автоматично зачиства паметта на масива</summary>
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
	///<summary> Функция която изтрива елемент и занулява паметта</summary>
	///<param name="nIndex"> Позиция на която изтриваме елемента</param> 
	void Delete(const INT_PTR nIndex)
	{
		ArrayType pType = GetAt(nIndex);
		if (pType == nullptr)
			return;

		delete pType;
		pType = nullptr;

		// Изтриваме града от масива
		RemoveAt(nIndex);
	}
	
	///<summary> Функция която копира масив със заделяне на памет</summary>
	///<param name="oArray"> Масива от който ще копираме елементите</param> 
	void CopyArray(const CAutoFreeMemoryArray<ArrayType>& oArray)
	{
		for (INT_PTR nIndex = 0; nIndex < oArray.GetCount(); nIndex++)
		{
			ArrayType pType = oArray.GetAt(nIndex);
			if (pType == nullptr)
				continue;

			// Заделяне на памет за новия указател
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