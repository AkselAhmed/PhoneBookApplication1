
// PhoneBook.h : main header file for the PhoneBook application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPhoneBookApp:
// See PhoneBook.cpp for the implementation of this class
//

class CPhoneBookApp : public CWinAppEx
{
public:
	CPhoneBookApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPhoneBookApp theApp;
