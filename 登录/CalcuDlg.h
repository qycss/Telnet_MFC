#pragma once


// CCalcuDlg 对话框

class CCalcuDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCalcuDlg)

public:
	CCalcuDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCalcuDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_Calculate };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCalculate();
	afx_msg void OnBnClickedOpenBoard();
};
