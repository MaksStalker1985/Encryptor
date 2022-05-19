#pragma once
#include "afxdialogex.h"


// Диалоговое окно mainDialog

class mainDialog : public CDialogEx
{
	DECLARE_DYNAMIC(mainDialog)

public:
	mainDialog(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~mainDialog();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_MD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedDestbutton3();
	afx_msg void OnBnClickedCheck1();
};
