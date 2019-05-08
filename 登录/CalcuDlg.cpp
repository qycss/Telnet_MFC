// CalcuDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��¼.h"
#include "CalcuDlg.h"
#include "afxdialogex.h"

#include <string>

// CCalcuDlg �Ի���

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


// CCalcuDlg ��Ϣ�������

//������������;
void CCalcuDlg::OnBnClickedButtonCalculate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString CCalExpresion;
	std::string CalExpresion;

	char recvBuffer[10];

	// ����socket��̬���ӿ�(dll);
	WORD wVersionRequested;
	WSADATA wsaData;	// ��ṹ�����ڽ���Wjndows Socket�Ľṹ��Ϣ��;
	int err;

	wVersionRequested = MAKEWORD( 1, 1 );	// ����1.1�汾��WinSock��;

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		return ;			// ����ֵΪ���ʱ���Ǳ�ʾ�ɹ�����WSAStartup;
	}

	if ( LOBYTE( wsaData.wVersion ) != 1 ||	HIBYTE( wsaData.wVersion ) != 1 ) {
		// ���������ֽ��ǲ���1�����ֽ��ǲ���1��ȷ���Ƿ������������1.1�汾;
		// ����Ļ�������WSACleanup()�����Ϣ����������;
		WSACleanup( );
		return ; 
	}

	// ����socket������������ʽ�׽��֣������׽��ֺ�sockClient;
	// SOCKET socket(int af, int type, int protocol);;
	// ��һ��������ָ����ַ��(TCP/IPֻ����AF_INET��Ҳ��д��PF_INET);
	// �ڶ�����ѡ���׽��ֵ�����(��ʽ�׽���)�����������ض���ַ�������Э�飨0Ϊ�Զ���;
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

	// ���׽���sockClient��Զ����������;
	// int connect( SOCKET s,  const struct sockaddr* name,  int namelen);;
	// ��һ����������Ҫ�������Ӳ������׽���;
	// �ڶ����������趨����Ҫ���ӵĵ�ַ��Ϣ;
	// ��������������ַ�ĳ���;
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");		// ���ػ�·��ַ��127.0.0.1; 
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	//����;	
	USES_CONVERSION;

	GetDlgItemText(IDC_EDIT_Expresion, CCalExpresion);
	CalExpresion = (std::string)(W2A(CCalExpresion));
	send(sockClient, "c", strlen("c")+1, 0);
	send(sockClient, CalExpresion.c_str(), CalExpresion.length()+1, 0);
	recv(sockClient, recvBuffer, 10, 0);
	SetDlgItemText(IDC_EDIT_Answer,static_cast<CString>(recvBuffer));


	closesocket(sockClient);
	WSACleanup();	// ��ֹ���׽��ֿ��ʹ��;
}

//open board
void CCalcuDlg::OnBnClickedOpenBoard()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString CCalExpresion;
	std::string CalExpresion;

	char recvBuffer[10];

	// ����socket��̬���ӿ�(dll);
	WORD wVersionRequested;
	WSADATA wsaData;	// ��ṹ�����ڽ���Wjndows Socket�Ľṹ��Ϣ��;
	int err;

	wVersionRequested = MAKEWORD( 1, 1 );	// ����1.1�汾��WinSock��;

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		return ;			// ����ֵΪ���ʱ���Ǳ�ʾ�ɹ�����WSAStartup;
	}

	if ( LOBYTE( wsaData.wVersion ) != 1 ||	HIBYTE( wsaData.wVersion ) != 1 ) {
		// ���������ֽ��ǲ���1�����ֽ��ǲ���1��ȷ���Ƿ������������1.1�汾;
		// ����Ļ�������WSACleanup()�����Ϣ����������;
		WSACleanup( );
		return ; 
	}

	// ����socket������������ʽ�׽��֣������׽��ֺ�sockClient;
	// SOCKET socket(int af, int type, int protocol);;
	// ��һ��������ָ����ַ��(TCP/IPֻ����AF_INET��Ҳ��д��PF_INET);
	// �ڶ�����ѡ���׽��ֵ�����(��ʽ�׽���)�����������ض���ַ�������Э�飨0Ϊ�Զ���;
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

	// ���׽���sockClient��Զ����������;
	// int connect( SOCKET s,  const struct sockaddr* name,  int namelen);;
	// ��һ����������Ҫ�������Ӳ������׽���;
	// �ڶ����������趨����Ҫ���ӵĵ�ַ��Ϣ;
	// ��������������ַ�ĳ���;
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");		// ���ػ�·��ַ��127.0.0.1; 
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
	WSACleanup();	// ��ֹ���׽��ֿ��ʹ��;
}
