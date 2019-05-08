
// 登录Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "登录.h"
#include "登录Dlg.h"
#include "afxdialogex.h"

#include "CalcuDlg.h"
#include <string>
#include <cstdio>
#include <Winsock2.h>
#include "ClientDlg.h"
#pragma comment(lib,"ws2_32.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C登录Dlg 对话框




C登录Dlg::C登录Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C登录Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C登录Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C登录Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C登录Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C登录Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// C登录Dlg 消息处理程序

BOOL C登录Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void C登录Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C登录Dlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting	
	CBitmap   bitmap;
	bitmap.LoadBitmap(IDB_BITMAP_LOGIN);    //这个IDB_BITMAP1要自己添加
	CBrush   brush;
	brush.CreatePatternBrush(&bitmap);
	CBrush* pOldBrush = dc.SelectObject(&brush);
	dc.Rectangle(-250, -250, 1500, 180);   // 这些参数可以调整图片添加位置和大小
	//dc.Rectangle(0, 0, 1500, 1500);
	dc.SelectObject(pOldBrush);



	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C登录Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//注册;
void C登录Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码;
	CString CUserName, CUserCode;
	GetDlgItemText(IDC_EDIT_UserName, CUserName);    
	GetDlgItemText(IDC_EDIT_UserCode, CUserCode);
		
	char recvBuffer[10];

	// 加载socket动态链接库(dll);
	WORD wVersionRequested;
	WSADATA wsaData;	// 这结构是用于接收Wjndows Socket的结构信息的;
	int err;

	wVersionRequested = MAKEWORD( 1, 1 );	// 请求1.1版本的WinSock库;

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		return ;			// 返回值为零的时候是表示成功申请WSAStartup;
	}

	if ( LOBYTE( wsaData.wVersion ) != 1 ||	HIBYTE( wsaData.wVersion ) != 1 ) {
		// 检查这个低字节是不是1，高字节是不是1以确定是否我们所请求的1.1版本;
		// 否则的话，调用WSACleanup()清除信息，结束函数;
		WSACleanup( );
		return ; 
	}

	// 创建socket操作，建立流式套接字，返回套接字号sockClient;
	// SOCKET socket(int af, int type, int protocol);;
	// 第一个参数，指定地址簇(TCP/IP只能是AF_INET，也可写成PF_INET);
	// 第二个，选择套接字的类型(流式套接字)，第三个，特定地址家族相关协议（0为自动）;
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

	// 将套接字sockClient与远程主机相连;
	// int connect( SOCKET s,  const struct sockaddr* name,  int namelen);;
	// 第一个参数：需要进行连接操作的套接字;
	// 第二个参数：设定所需要连接的地址信息;
	// 第三个参数：地址的长度;
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");		// 本地回路地址是127.0.0.1; 
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	//注册;
    USES_CONVERSION;
	send(sockClient, "r", strlen("r")+1, 0);
	send(sockClient, ((std::string)(W2A(CUserName))).c_str(), 9, 0);
	send(sockClient, ((std::string)(W2A(CUserCode))).c_str(), 9, 0);
	recv(sockClient, recvBuffer, 10, 0);
	if(strcmp(recvBuffer,"true") == 0)
		MessageBox(_T("注册成功"), _T("网络课设"), MB_OK );
	else
		MessageBox(_T("注册失败"), _T("网络课设"), MB_OK );


	closesocket(sockClient);
	WSACleanup();	// 终止对套接字库的使用;
}


//登录;
void C登录Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString CUserName, CUserCode;
	GetDlgItemText(IDC_EDIT_UserName, CUserName);
	GetDlgItemText(IDC_EDIT_UserCode, CUserCode);

	char recvBuffer[10];

	// 加载socket动态链接库(dll);
	WORD wVersionRequested;
	WSADATA wsaData;	// 这结构是用于接收Wjndows Socket的结构信息的;
	int err;

	wVersionRequested = MAKEWORD( 1, 1 );	// 请求1.1版本的WinSock库;

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		return ;			// 返回值为零的时候是表示成功申请WSAStartup;
	}

	if ( LOBYTE( wsaData.wVersion ) != 1 ||	HIBYTE( wsaData.wVersion ) != 1 ) {
		// 检查这个低字节是不是1，高字节是不是1以确定是否我们所请求的1.1版本;
		// 否则的话，调用WSACleanup()清除信息，结束函数;
		WSACleanup( );
		return ; 
	}

	// 创建socket操作，建立流式套接字，返回套接字号sockClient;
	// SOCKET socket(int af, int type, int protocol);;
	// 第一个参数，指定地址簇(TCP/IP只能是AF_INET，也可写成PF_INET);
	// 第二个，选择套接字的类型(流式套接字)，第三个，特定地址家族相关协议（0为自动）;
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

	// 将套接字sockClient与远程主机相连;
	// int connect( SOCKET s,  const struct sockaddr* name,  int namelen);;
	// 第一个参数：需要进行连接操作的套接字;
	// 第二个参数：设定所需要连接的地址信息;
	// 第三个参数：地址的长度;
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");		// 本地回路地址是127.0.0.1; 
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	//登录;
	USES_CONVERSION;
	send(sockClient, "l", strlen("l")+1, 0);
	send(sockClient, ((std::string)(W2A(CUserName))).c_str(), 9, 0);
	send(sockClient, ((std::string)(W2A(CUserCode))).c_str(), 9, 0);
	recv(sockClient, recvBuffer, 10, 0);
	if(strcmp(recvBuffer,"true") == 0)
		MessageBox(_T("登录成功"), _T("网络"), MB_OK );
	else
		MessageBox(_T("登录失败"), _T("网络"), MB_OK );


	closesocket(sockClient);
	WSACleanup();	// 终止对套接字库的使用;

	if (strcmp(recvBuffer, "true") == 0) {
		//打开主界面
		INT_PTR nRes;             // 用于保存DoModal函数的返回值   
		ClientDlg clientDlg;           // 构造对话框类CTipDlg的实例   
		nRes = clientDlg.DoModal();  // 弹出对话框   
	}
	

}
