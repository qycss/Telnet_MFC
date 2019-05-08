// CalcuDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "登录.h"
#include "CalcuDlg.h"
#include "afxdialogex.h"

#include <string>

// CCalcuDlg 对话框

IMPLEMENT_DYNAMIC(CCalcuDlg, CDialogEx)

CCalcuDlg::CCalcuDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCalcuDlg::IDD, pParent)
{

}

CCalcuDlg::~CCalcuDlg()
{
}

void CCalcuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCalcuDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Calculate, &CCalcuDlg::OnBnClickedButtonCalculate)
	ON_BN_CLICKED(IDC_BUTTON_OpenBoard, &CCalcuDlg::OnBnClickedOpenBoard)
END_MESSAGE_MAP()


// CCalcuDlg 消息处理程序

//计算四则运算;
void CCalcuDlg::OnBnClickedButtonCalculate()
{
	// TODO: 在此添加控件通知处理程序代码
	CString CCalExpresion;
	std::string CalExpresion;

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

	//计算;	
	USES_CONVERSION;

	GetDlgItemText(IDC_EDIT_Expresion, CCalExpresion);
	CalExpresion = (std::string)(W2A(CCalExpresion));
	send(sockClient, "c", strlen("c")+1, 0);
	send(sockClient, CalExpresion.c_str(), CalExpresion.length()+1, 0);
	recv(sockClient, recvBuffer, 10, 0);
	SetDlgItemText(IDC_EDIT_Answer,static_cast<CString>(recvBuffer));


	closesocket(sockClient);
	WSACleanup();	// 终止对套接字库的使用;
}

//open board
void CCalcuDlg::OnBnClickedOpenBoard()
{
	// TODO: 在此添加控件通知处理程序代码
	CString CCalExpresion;
	std::string CalExpresion;

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

	//open;	
	USES_CONVERSION;

	GetDlgItemText(IDC_EDIT_Expresion, CCalExpresion);
	CalExpresion = (std::string)(W2A(CCalExpresion));
	send(sockClient, "o", strlen("o")+1, 0);
	send(sockClient, CalExpresion.c_str(), CalExpresion.length()+1, 0);
	recv(sockClient, recvBuffer, 10, 0);

	closesocket(sockClient);
	WSACleanup();	// 终止对套接字库的使用;
}
