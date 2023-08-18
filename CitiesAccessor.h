#pragma once

#include "BaseAccessor.h"

#define CITIES_ID_COLUMN 1
#define CITIES_UPDATE_COUNTER_COLUMN 2
#define CITIES_CITY_NAME_COLUMN 3
#define CITIES_DISTRICT_COLUMN 4

/////////////////////////////////////////////////////////////////////////////
// CCitiesAccessor�

///<summary> ���� Accessor �� ��������� CITIES</summary> 
class CCitiesAccessor : public CBaseAccessor<CITIES>
{
// Macros
// ----------------
protected:
	BEGIN_ACCESSOR_MAP(CCitiesAccessor, 2)
		BEGIN_ACCESSOR(ACCESSOR_ID, true)
			COLUMN_ENTRY(CITIES_ID_COLUMN, m_recCity.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ACCESSOR_WITHOUT_ID, true)
			COLUMN_ENTRY(CITIES_UPDATE_COUNTER_COLUMN, m_recCity.lUpdateCounter)
			COLUMN_ENTRY(CITIES_CITY_NAME_COLUMN, m_recCity.szCityName)
			COLUMN_ENTRY(CITIES_DISTRICT_COLUMN, m_recCity.szDistrict)
		END_ACCESSOR()
	END_ACCESSOR_MAP()


// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CCitiesAccessor()
	{
	}
	virtual ~CCitiesAccessor()
	{
	}

// Methods
// ----------------


// Overrides
// ----------------
public:
	///<summary> ������� �� ������ �� UpdateCounter-� �� ���� ������������</summary>
	/// <returns> ����� ���������� �� UpdateCounter-� �� ���� ������������ </returns>
	long& GetAccessorUpdateCounter() override 
	{
		return m_recCity.lUpdateCounter;
	}

	///<summary> ������� ����� ���� ������ �� ���� ������������ �� ��������</summary>
	/// <returns> ����� ���������� �� ���� ������������</returns>
	CITIES& GetAccessor() override
	{
		return m_recCity;
	}


// Members
// ----------------
private:
	///<summary> ���� ���������� �� ��� ��������� CITIES</summary>
	CITIES m_recCity;
};
