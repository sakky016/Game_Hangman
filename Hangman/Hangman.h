
// Hangman.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CHangmanApp:
// See Hangman.cpp for the implementation of this class
//

class CHangmanApp : public CWinApp
{
public:
	CHangmanApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CHangmanApp theApp;
