#include <WINSOCK2.H>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <string.h>
#include <time.h>
#include <sstream>
#include <stdlib.h>
#define _WIN32_WINNT    0x0500
#include <windows.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32")
using namespace std;
#define HELPMSG "help - Show Help Menu \r\n" \
                "notepad - Open The Notepad \r\n" \
                "time - Get Local Time \r\n" \
				"chrome - Open The Chrome \r\n" \
                "swap - Swap Mouse Button \r\n" \
                "restore - Restore Mouse Button \r\n" \
				"calculate - Calculate \r\n" \
				"end - End Calculate \r\n" \
                "exit - Quit BdShell"


float main2(string line);

int main()
{
	// ����socket��̬���ӿ�(dll)
	WORD wVersionRequested;
	WSADATA wsaData;	// ��ṹ�����ڽ���Wjndows Socket�Ľṹ��Ϣ��
	int err;

	wVersionRequested = MAKEWORD(1, 1);	// ����1.1�汾��WinSock��

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return -1;			// ����ֵΪ���ʱ���Ǳ�ʾ�ɹ�����WSAStartup
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		// ���������ֽ��ǲ���1�����ֽ��ǲ���1��ȷ���Ƿ������������1.1�汾
		// ����Ļ�������WSACleanup()�����Ϣ����������
		WSACleanup();
		return -1;
	}

	// ����socket������������ʽ�׽��֣������׽��ֺ�sockSrv
	// SOCKET socket(int af, int type, int protocol);
	// ��һ��������ָ����ַ��(TCP/IPֻ����AF_INET��Ҳ��д��PF_INET)
	// �ڶ�����ѡ���׽��ֵ�����(��ʽ�׽���)�����������ض���ַ�������Э�飨0Ϊ�Զ���
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	// �׽���sockSrv�뱾�ص�ַ����
	// int bind(SOCKET s, const struct sockaddr* name, int namelen);
	// ��һ��������ָ����Ҫ�󶨵��׽��֣�
	// �ڶ���������ָ�����׽��ֵı��ص�ַ��Ϣ���õ�ַ�ṹ�������õ�����Э��Ĳ�ͬ����ͬ
	// ������������ָ��������Э���ַ�ĳ���
	// PS: struct sockaddr{ u_short sa_family; char sa_data[14];};
	//                      sa_familyָ���õ�ַ���壬 sa_data��ռλռ��һ���ڴ������������
	//     ��TCP/IP�У���ʹ��sockaddr_in�ṹ�滻sockaddr���Է�����д��ַ��Ϣ
	// 
	//     struct sockaddr_in{ short sin_family; unsigned short sin_port; struct in_addr sin_addr; char sin_zero[8];};
	//     sin_family��ʾ��ַ�壬����IP��ַ��sin_family��Ա��һֱ��AF_INET��
	//     sin_portָ����Ҫ������׽��ֵĶ˿ڡ�
	//     sin_addr�����׽��ֵ�����IP��ַ��
	//     sin_zero[8]�������������sockaddr_in��sockaddr�ṹ�ĳ���һ����
	//     ��IP��ַָ��ΪINADDR_ANY�������׽������κη�������ػ�����IP��ַ���ͻ�������ݡ�
	//     �����ֻ���׽���ʹ�ö��IP�е�һ����ַ����ָ��ʵ�ʵ�ַ����inet_addr()������
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // ��INADDR_ANYת��Ϊ�����ֽ��򣬵��� htonl(long��)��htons(����)
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	bind(sockSrv, (SOCKADDR*)& addrSrv, sizeof(SOCKADDR)); // �ڶ�����Ҫǿ������ת��

	// ���׽�������Ϊ����ģʽ���������󣩣� listen()֪ͨTCP������׼���ý�������
	// int listen(SOCKET s,  int backlog);
	// ��һ������ָ����Ҫ���õ��׽��֣��ڶ�������Ϊ���ȴ����Ӷ��е���󳤶ȣ�
	listen(sockSrv, 10);

	// accept()���������ӣ��ȴ��ͻ�������
	// SOCKET accept(  SOCKET s,  struct sockaddr* addr,  int* addrlen);
	// ��һ������������һ�����ڼ���״̬�µ��׽���
	// �ڶ���������sockaddr���ڱ���ͻ��˵�ַ����Ϣ
	// ����������������ָ�������ַ�ĳ���
	// ���ص��������������״̬�µ��׽���ͨ�ŵ��׽���

	// �ͻ������û��˽���ͨ��

	// send(), ���׽����Ϸ�������
	// int send( SOCKET s,  const char* buf,  int len,  int flags);
	// ��һ����������Ҫ������Ϣ���׽��֣�
	// �ڶ�����������������Ҫ�����͵����ݣ�
	// ������������buffer�����ݳ��ȣ�
	// ���ĸ�������һЩ���Ͳ���������

	// recv(), ���׽����Ͻ�������
	// int recv(  SOCKET s,  char* buf,  int len,  int flags);
	// ��һ���������������Ӻ���׽��֣�
	// �ڶ�����������������
	// �������������������ݵĳ��ȣ�
	// ���ĸ�������һЩ���Ͳ���������

	SOCKADDR_IN  addrClient;
	int len = sizeof(SOCKADDR);

	while (true) {	// ���ϵȴ��ͻ�������ĵ���
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)& addrClient, &len);
		cout << "���ӳɹ���" << endl;

		char recvChar[2];
		recv(sockConn, recvChar, 2, 0);

		if (recvChar[0] == 'r')        //��Ϊע��;
		{
			char recvUserName[9];
			char recvUserCode[9];
			recv(sockConn, recvUserName, 9, 0);
			recv(sockConn, recvUserCode, 9, 0);

			//ע��;
			cout << "ע����..." << endl;
			cout << "�û�����" << recvUserName << "\t���룺" << recvUserCode << endl;

			fstream file("F:\\user.dat", ios::out | ios::binary | ios::app);
			file.write((char*)recvUserName, sizeof(recvUserName));
			file.write((char*)recvUserCode, sizeof(recvUserCode));
			file.close();

			cout << "ע��ɹ���" << endl;
			send(sockConn, "true", strlen("true") + 1, 0);
		}
		else if (recvChar[0] == 'l')
		{
			cout << "��¼��..." << endl;
			char recvUserName[9];
			char recvUserCode[9];
			recv(sockConn, recvUserName, 9, 0);
			recv(sockConn, recvUserCode, 9, 0);

			//��¼;			
			cout << "�û�����" << recvUserName << "\t���룺" << recvUserCode << endl;

			fstream file("F:\\user.dat", ios::in | ios::binary);
			if (file.fail())
			{
				cout << "��ȡʱ�����ļ�ʧ��...;" << endl;
				exit(0);
			}

			cout << "���ļ���ȡ����....;" << endl;
			char UserName[9];
			char UserCode[9];
			bool flag = false;
			while (file.read((char*)UserName, sizeof(UserName)))
			{
				file.read((char*)UserCode, sizeof(UserCode));
				if (strcmp(recvUserName, UserName) == 0 && strcmp(recvUserCode, UserCode) == 0)
				{
					flag = true;
					break;
				}
			}
			file.close();

			if (flag == true)
			{
				cout << "��¼�ɹ���" << endl;
				send(sockConn, "true", strlen("true") + 1, 0);
			}
			else
			{
				cout << "��¼ʧ�ܣ�" << endl;
				send(sockConn, "false", strlen("false") + 1, 0);
			}
		}
		else if (recvChar[0] == 'c')
		{
			cout << "������..." << endl;
			char recvExpresion[50];
			recv(sockConn, recvExpresion, 50, 0);

			string SrecvExpresion(recvExpresion);

			//����;			
			cout << "������ʽ��" << recvExpresion << ";" << endl;

			stringstream os;
			os << main2(SrecvExpresion);
			string Sanswer = os.str();

			send(sockConn, Sanswer.c_str(), Sanswer.size() + 1, 0);
			cout << "��������" << Sanswer << ";" << endl;

		}
		else if (recvChar[0] == 'o')//open book
		{
			system("C:\\Windows\\System32\\notepad.exe");
			cout << "open Writing board" << endl;
		}

		else if (recvChar[0] == 'b')
		{
			system("f:\\Chrome.lnk   www.baidu.com");
			cout << "open Browser" << endl;
		}
		else if (recvChar[0] == 'h')
		{
			cout << "show Help" << endl;
		}

		else if (recvChar[0] == 'C')
		{
			cout << "swap Mouse" << endl;
			SwapMouseButton(true);
		}

		else if (recvChar[0] == 'R')
		{
			cout << "restore Mouse" << endl;
			SwapMouseButton(false);
		}

		closesocket(sockConn);
	}

	printf("\n");
	system("pause");
	return 0;
}


