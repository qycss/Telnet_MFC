#pragma once


// CCalcuDlg �Ի���

class CCalcuDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCalcuDlg)

public:
	CCalcuDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCalcuDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_Calculate };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCalculate();
	afx_msg void OnBnClickedOpenBoard();
};
