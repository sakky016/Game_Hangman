
// HangmanDlg.h : header file
//

#pragma once


// CHangmanDlg dialog
class CHangmanDlg : public CDialogEx
{
// Construction
public:
	CHangmanDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HANGMAN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedCancel();
    afx_msg void OnEnChangetxthighscores();
    afx_msg void OnBnClickedbtna();
    afx_msg void OnBnClickedbtns();
    afx_msg void OnBnClickedbtnd();
    afx_msg void OnBnClickedbtnf();
    afx_msg void OnBnClickedbtng();
    afx_msg void OnBnClickedbtnh();
    afx_msg void OnBnClickedbtnj();
    afx_msg void OnBnClickedbtnk();
    afx_msg void OnBnClickedbtnl();
    afx_msg void OnBnClickedbtnz();
    afx_msg void OnBnClickedbtnx();
    afx_msg void OnBnClickedbtnc();
    afx_msg void OnBnClickedbtnv();
    afx_msg void OnBnClickedbtnb();
    afx_msg void OnBnClickedbtnn();
    afx_msg void OnBnClickedbtnm();
    afx_msg void OnBnClickedbtnq();
    afx_msg void OnBnClickedbtnw();
    afx_msg void OnBnClickedbtne();
    afx_msg void OnBnClickedbtnr();
    afx_msg void OnBnClickedbtnt();
    afx_msg void OnBnClickedbtny();
    afx_msg void OnBnClickedbtnu();
    afx_msg void OnBnClickedbtni();
    afx_msg void OnBnClickedbtno();
    afx_msg void OnBnClickedbtnp();
    afx_msg void OnBnClickedbtnnewgame();
    afx_msg void OnBnClickedbtnskip();
    afx_msg void OnBnClickedbtnshowhint();
};
