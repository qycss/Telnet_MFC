// ClientDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "登录.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include "CalcuDlg.h"
#include <time.h>
#include <string>
#include <Winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#define HELPMSG "help - Show Help Menu \r\n" \
                "notepad - Open The Notepad \r\n" \
                "time - Get Local Time \r\n" \
				"chrome - Open The Chrome \r\n" \
                "swap - Swap Mouse Button \r\n" \
                "restore - Restore Mouse Button \r\n" \
				"calculate - Calculate \r\n" \
				


// ClientDlg 对话框

IMPLEMENT_DYNAMIC(ClientDlg, CDialogEx)

ClientDlg::ClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ClientDlg::IDD, pParent)
{

}

ClientDlg::~ClientDlg()
{
}

void ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ClientDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CAL, &ClientDlg::OnBnClickedButtonCal)
	ON_BN_CLICKED(IDC_BUTTON_NOTEPAD, &ClientDlg::OnBnClickedButtonNotepad)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_BROWSER, &ClientDlg::OnBnClickedButtonBrowser)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &ClientDlg::OnBnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_CHG, &ClientDlg::OnBnClickedButtonChg)
	ON_BN_CLICKED(IDC_BUTTON_RESTORE, &ClientDlg::OnBnClickedButtonRestore)
END_MESSAGE_MAP()




// ClientDlg 消息处理程序

BOOL ClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CString strTime;
	CTime tm;
	tm = CTime::GetCurrentTime();         //获取当前系统时间
	strTime = tm.Format("%Y年%m月%d日\n %H:%M:%S");   //格式化系统时间。即使系统时间按照Format中设置的格式显示
	SetDlgItemText(IDC_TIME, strTime);        //初始化编辑框显示
	SetTimer(1, 1000, NULL);         //启动定时器

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE

}


void ClientDlg::OnBnClickedButtonNotepad()
{

	// TODO: 在此添加控件通知处理程序代码
	CString ClientExpression;
	std::string CExpression;

	char recvBuffer[10];

	// 加载socket动态链接库(dll);
	WORD wVersionRequested;
	WSADATA wsaData;	// 这结构是用于接收Wjndows Socket的结构信息的;
	int err;

	wVersionRequested = MAKEWORD(1, 1);	// 请求1.1版本的WinSock库;

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return;			// 返回值为零的时候是表示成功申请WSAStartup;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		// 检查这个低字节是不是1，高字节是不是1以确定是否我们所请求的1.1版本;
		// 否则的话，调用WSACleanup()清除信息，结束函数;
		WSACleanup();
		return;
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
	connect(sockClient, (SOCKADDR*)& addrSrv, sizeof(SOCKADDR));

	//open;	
	USES_CONVERSION;

	GetDlgItemText(IDC_EDIT_Expresion, ClientExpression);
	CExpression = (std::string)(W2A(ClientExpression));
	send(sockClient, "o", strlen("o") + 1, 0);
	send(sockClient, CExpression.c_str(), CExpression.length() + 1, 0);
	recv(sockClient, recvBuffer, 10, 0);

	closesocket(sockClient);
	WSACleanup();	// 终止对套接字库的使用;
	

}

//计算器
void ClientDlg::OnBnClickedButtonCal()
{
	// TODO: 在此添加控件通知处理程序代码
	INT_PTR	nRes;
	CCalcuDlg calcuDlg;
	nRes = calcuDlg.DoModal();
}

//显示时间
void ClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
	CString strTime;
	CTime tm;
	tm = CTime::GetCurrentTime();
	strTime = tm.Format("%Y年%m月%d日\n %H:%M:%S");
	SetDlgItemText(IDC_TIME, strTime);        //显示系统时间
}

//浏览器
void ClientDlg::OnBnClickedButtonBrowser()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	CString ClientExpression;
	std::string CExpression;

	char recvBuffer[10];

	// 加载socket动态链接库(dll);
	WORD wVersionRequested;
	WSADATA wsaData;	// 这结构是用于接收Wjndows Socket的结构信息的;
	int err;

	wVersionRequested = MAKEWORD(1, 1);	// 请求1.1版本的WinSock库;

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return;			// 返回值为零的时候是表示成功申请WSAStartup;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		// 检查这个低字节是不是1，高字节是不是1以确定是否我们所请求的1.1版本;
		// 否则的话，调用WSACleanup()清除信息，结束函数;
		WSACleanup();
		return;
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
	connect(sockClient, (SOCKADDR*)& addrSrv, sizeof(SOCKADDR));

	//open;	
	USES_CONVERSION;

	GetDlgItemText(IDC_EDIT_Expresion, ClientExpression);
	CExpression = (std::string)(W2A(ClientExpression));
	send(sockClient, "b", strlen("b") + 1, 0);
	send(sockClient, CExpression.c_str(), CExpression.length() + 1, 0);
	recv(sockClient, recvBuffer, 10, 0);

	closesocket(sockClient);
	WSACleanup();	// 终止对套接字库的使用;
}


//帮助
void ClientDlg::OnBnClickedButtonHelp()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T(HELPMSG), _T("功能介绍"), MB_OK);

	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	CString ClientExpression;
	std::string CExpression;

	char recvBuffer[10];

	// 加载socket动态链接库(dll);
	WORD wVersionRequested;
	WSADATA wsaData;	// 这结构是用于接收Wjndows Socket的结构信息的;
	int err;

	wVersionRequested = MAKEWORD(1, 1);	// 请求1.1版本的WinSock库;

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return;			// 返回值为零的时候是表示成功申请WSAStartup;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		// 检查这个低字节是不是1，高字节是不是1以确定是否我们所请求的1.1版本;
		// 否则的话，调用WSACleanup()清除信息，结束函数;
		WSACleanup();
		return;
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
	connect(sockClient, (SOCKADDR*)& addrSrv, sizeof(SOCKADDR));

	//open;	
	USES_CONVERSION;

	GetDlgItemText(IDC_EDIT_Expresion, ClientExpression);
	CExpression = (std::string)(W2A(ClientExpression));
	send(sockClient, "h", strlen("h") + 1, 0);
	send(sockClient, CExpression.c_str(), CExpression.length() + 1, 0);
	recv(sockClient, recvBuffer, 10, 0);

	closesocket(sockClient);
	WSACleanup();	// 终止对套接字库的使用;
}



void ClientDlg::OnBnClickedButtonChg()
{
	// TODO: 在此添加控件通知处理程序代码

	CString ClientExpression;
	std::string CExpression;

	char recvBuffer[10];

	// 加载socket动态链接库(dll);
	WORD wVersionRequested;
	WSADATA wsaData;	// 这结构是用于接收Wjndows Socket的结构信息的;
	int err;

	wVersionRequested = MAKEWORD(1, 1);	// 请求1.1版本的WinSock库;

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return;			// 返回值为零的时候是表示成功申请WSAStartup;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		// 检查这个低字节是不是1，高字节是不是1以确定是否我们所请求的1.1版本;
		// 否则的话，调用WSACleanup()清除信息，结束函数;
		WSACleanup();
		return;
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
	connect(sockClient, (SOCKADDR*)& addrSrv, sizeof(SOCKADDR));

	//open;	
	USES_CONVERSION;

	GetDlgItemText(IDC_EDIT_Expresion, ClientExpression);
	CExpression = (std::string)(W2A(ClientExpression));
	send(sockClient, "C", strlen("C") + 1, 0);
	send(sockClient, CExpression.c_str(), CExpression.length() + 1, 0);
	recv(sockClient, recvBuffer, 10, 0);

	closesocket(sockClient);
	WSACleanup();	// 终止对套接字库的使用;
}


void ClientDlg::OnBnClickedButtonRestore()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码

	CString ClientExpression;
	std::string CExpression;

	char recvBuffer[10];

	// 加载socket动态链接库(dll);
	WORD wVersionRequested;
	WSADATA wsaData;	// 这结构是用于接收Wjndows Socket的结构信息的;
	int err;

	wVersionRequested = MAKEWORD(1, 1);	// 请求1.1版本的WinSock库;

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return;			// 返回值为零的时候是表示成功申请WSAStartup;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		// 检查这个低字节是不是1，高字节是不是1以确定是否我们所请求的1.1版本;
		// 否则的话，调用WSACleanup()清除信息，结束函数;
		WSACleanup();
		return;
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
	connect(sockClient, (SOCKADDR*)& addrSrv, sizeof(SOCKADDR));

	//open;	
	USES_CONVERSION;

	GetDlgItemText(IDC_EDIT_Expresion, ClientExpression);
	CExpression = (std::string)(W2A(ClientExpression));
	send(sockClient, "R", strlen("R") + 1, 0);
	send(sockClient, CExpression.c_str(), CExpression.length() + 1, 0);
	recv(sockClient, recvBuffer, 10, 0);

	closesocket(sockClient);
	WSACleanup();	// 终止对套接字库的使用;
}
