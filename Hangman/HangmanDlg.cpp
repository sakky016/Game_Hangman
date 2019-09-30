
// HangmanDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Hangman.h"
#include "HangmanDlg.h"
#include "afxdialogex.h"
#include "game.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static bool g_bFirstRun = true;
// CHangmanDlg dialog



CHangmanDlg::CHangmanDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HANGMAN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHangmanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHangmanDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(btnA, &CHangmanDlg::OnBnClickedbtna)
    ON_BN_CLICKED(btnS, &CHangmanDlg::OnBnClickedbtns)
    ON_BN_CLICKED(btnD, &CHangmanDlg::OnBnClickedbtnd)
    ON_BN_CLICKED(btnF, &CHangmanDlg::OnBnClickedbtnf)
    ON_BN_CLICKED(btnG, &CHangmanDlg::OnBnClickedbtng)
    ON_BN_CLICKED(btnH, &CHangmanDlg::OnBnClickedbtnh)
    ON_BN_CLICKED(btnJ, &CHangmanDlg::OnBnClickedbtnj)
    ON_BN_CLICKED(btnK, &CHangmanDlg::OnBnClickedbtnk)
    ON_BN_CLICKED(btnL, &CHangmanDlg::OnBnClickedbtnl)
    ON_BN_CLICKED(btnZ, &CHangmanDlg::OnBnClickedbtnz)
    ON_BN_CLICKED(btnX, &CHangmanDlg::OnBnClickedbtnx)
    ON_BN_CLICKED(btnC, &CHangmanDlg::OnBnClickedbtnc)
    ON_BN_CLICKED(btnV, &CHangmanDlg::OnBnClickedbtnv)
    ON_BN_CLICKED(btnB, &CHangmanDlg::OnBnClickedbtnb)
    ON_BN_CLICKED(btnN, &CHangmanDlg::OnBnClickedbtnn)
    ON_BN_CLICKED(btnM, &CHangmanDlg::OnBnClickedbtnm)
    ON_BN_CLICKED(btnQ, &CHangmanDlg::OnBnClickedbtnq)
    ON_BN_CLICKED(btnW, &CHangmanDlg::OnBnClickedbtnw)
    ON_BN_CLICKED(btnE, &CHangmanDlg::OnBnClickedbtne)
    ON_BN_CLICKED(btnR, &CHangmanDlg::OnBnClickedbtnr)
    ON_BN_CLICKED(btnT, &CHangmanDlg::OnBnClickedbtnt)
    ON_BN_CLICKED(btnY, &CHangmanDlg::OnBnClickedbtny)
    ON_BN_CLICKED(btnU, &CHangmanDlg::OnBnClickedbtnu)
    ON_BN_CLICKED(btnI, &CHangmanDlg::OnBnClickedbtni)
    ON_BN_CLICKED(btnO, &CHangmanDlg::OnBnClickedbtno)
    ON_BN_CLICKED(btnP, &CHangmanDlg::OnBnClickedbtnp)
    ON_BN_CLICKED(btnNewGame, &CHangmanDlg::OnBnClickedbtnnewgame)
    ON_BN_CLICKED(btnSkip, &CHangmanDlg::OnBnClickedbtnskip)
    ON_BN_CLICKED(btnShowHint, &CHangmanDlg::OnBnClickedbtnshowhint)
END_MESSAGE_MAP()


// CHangmanDlg message handlers

BOOL CHangmanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

    // This should be done after LoadDictionary()
    InitializeGame(GetSafeHwnd());



	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHangmanDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHangmanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHangmanDlg::OnBnClickedbtna()
{
    OnGuessLetter('A');
}


void CHangmanDlg::OnBnClickedbtns()
{
    OnGuessLetter('S');
}


void CHangmanDlg::OnBnClickedbtnd()
{
    OnGuessLetter('D');
}


void CHangmanDlg::OnBnClickedbtnf()
{
    OnGuessLetter('F');
}


void CHangmanDlg::OnBnClickedbtng()
{
    OnGuessLetter('G');
}


void CHangmanDlg::OnBnClickedbtnh()
{
    OnGuessLetter('H');
}


void CHangmanDlg::OnBnClickedbtnj()
{
    OnGuessLetter('J');
}


void CHangmanDlg::OnBnClickedbtnk()
{
    OnGuessLetter('K');
}


void CHangmanDlg::OnBnClickedbtnl()
{
    OnGuessLetter('L');
}


void CHangmanDlg::OnBnClickedbtnz()
{
    OnGuessLetter('Z');
}


void CHangmanDlg::OnBnClickedbtnx()
{
    OnGuessLetter('X');
}


void CHangmanDlg::OnBnClickedbtnc()
{
    OnGuessLetter('C');
}


void CHangmanDlg::OnBnClickedbtnv()
{
    OnGuessLetter('V');
}


void CHangmanDlg::OnBnClickedbtnb()
{
    OnGuessLetter('B');
}


void CHangmanDlg::OnBnClickedbtnn()
{
    OnGuessLetter('N');
}


void CHangmanDlg::OnBnClickedbtnm()
{
    OnGuessLetter('M');
}


void CHangmanDlg::OnBnClickedbtnq()
{
    OnGuessLetter('Q');
}


void CHangmanDlg::OnBnClickedbtnw()
{
    OnGuessLetter('W');
}


void CHangmanDlg::OnBnClickedbtne()
{
    OnGuessLetter('E');
}


void CHangmanDlg::OnBnClickedbtnr()
{
    OnGuessLetter('R');
}


void CHangmanDlg::OnBnClickedbtnt()
{
    OnGuessLetter('T');
}


void CHangmanDlg::OnBnClickedbtny()
{
    OnGuessLetter('Y');
}


void CHangmanDlg::OnBnClickedbtnu()
{
    OnGuessLetter('U');
}


void CHangmanDlg::OnBnClickedbtni()
{
    OnGuessLetter('I');
}


void CHangmanDlg::OnBnClickedbtno()
{
    OnGuessLetter('O');
}


void CHangmanDlg::OnBnClickedbtnp()
{
    OnGuessLetter('P');
}


void CHangmanDlg::OnBnClickedbtnnewgame()
{
    if (g_bFirstRun)
    {
        StartNewGame();
        g_bFirstRun = false;
    }
    else
    {
        int choice = MessageBox(L"Are you sure you want to start a new game?\n\n\
                                Scores will be reset and word dictionary will be reloaded", L"New Game", MB_YESNO | MB_DEFBUTTON2);
        if (choice == IDYES)
        {
            StartNewGame();
        }
    }
}


void CHangmanDlg::OnBnClickedbtnskip()
{
    ContinueGame();
}


void CHangmanDlg::OnBnClickedbtnshowhint()
{
    ShowHint();
}
