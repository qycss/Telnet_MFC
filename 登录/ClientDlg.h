#pragma once


// ClientDlg 对话框


class ClientDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ClientDlg)

public:
	ClientDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ClientDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_Client };
protected:	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持


//实现
protected:
	
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:

	afx_msg void OnBnClickedButtonCal();
	void OnBnClickedButtonNotepad();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonBrowser();
	afx_msg void OnBnClickedButtonHelp();
	afx_msg void OnBnClickedButtonChg();
	afx_msg void OnBnClickedButtonRestore();
};
