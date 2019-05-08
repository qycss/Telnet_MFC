// CTimeDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "登录.h"
#include "CTimeDlg.h"
#include "afxdialogex.h"


// CTimeDlg 对话框

IMPLEMENT_DYNAMIC(CTimeDlg, CDialogEx)

CTimeDlg::CTimeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TIME, pParent)
{

}

CTimeDlg::~CTimeDlg()
{
}

void CTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTimeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_TIME_RETURN, &CTimeDlg::OnBnClickedBtnTimeReturn)
	ON_EN_CHANGE(IDC_EDIT_TIME, &CTimeDlg::OnEnChangeEditTime)
	ON_STN_CLICKED(IDC_TIME, &CTimeDlg::OnStnClickedTime)
END_MESSAGE_MAP()


// CTimeDlg 消息处理程序

BOOL CTimeDlg::OnInitDialog()
{
	CString strTime;
	CTime tm;
	tm = CTime::GetCurrentTime();         //获取当前系统时间
	strTime = tm.Format("%y年%m月%d日 %X");   //格式化系统时间。即使系统时 间按照Format中设置的格式显示
	SetDlgItemText(IDC_EDIT_TIME, strTime);        //初始化编辑框显示
	SetTimer(1, 1000, NULL);         //启动定时器
	return TRUE;
}


void CTimeDlg::OnBnClickedBtnTimeReturn()
{
	// TODO: 在此添加控件通知处理程序代码

}


void CTimeDlg::OnEnChangeEditTime()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	// TODO:  在此添加控件通知处理程序代码
	CString strTime;
	CTime tm;
	tm = CTime::GetCurrentTime();
	strTime = tm.Format("%Y-%m-%d %H:%M:%S");
	SetDlgItemText(IDC_EDIT_TIME, strTime);        //显示系统时间
	
}


void CTimeDlg::OnStnClickedTime()
{
	// TODO: 在此添加控件通知处理程序代码
}
