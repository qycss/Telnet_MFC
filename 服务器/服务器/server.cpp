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
	// 加载socket动态链接库(dll)
	WORD wVersionRequested;
	WSADATA wsaData;	// 这结构是用于接收Wjndows Socket的结构信息的
	int err;

	wVersionRequested = MAKEWORD(1, 1);	// 请求1.1版本的WinSock库

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return -1;			// 返回值为零的时候是表示成功申请WSAStartup
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		// 检查这个低字节是不是1，高字节是不是1以确定是否我们所请求的1.1版本
		// 否则的话，调用WSACleanup()清除信息，结束函数
		WSACleanup();
		return -1;
	}

	// 创建socket操作，建立流式套接字，返回套接字号sockSrv
	// SOCKET socket(int af, int type, int protocol);
	// 第一个参数，指定地址簇(TCP/IP只能是AF_INET，也可写成PF_INET)
	// 第二个，选择套接字的类型(流式套接字)，第三个，特定地址家族相关协议（0为自动）
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	// 套接字sockSrv与本地地址相连
	// int bind(SOCKET s, const struct sockaddr* name, int namelen);
	// 第一个参数，指定需要绑定的套接字；
	// 第二个参数，指定该套接字的本地地址信息，该地址结构会随所用的网络协议的不同而不同
	// 第三个参数，指定该网络协议地址的长度
	// PS: struct sockaddr{ u_short sa_family; char sa_data[14];};
	//                      sa_family指定该地址家族， sa_data起到占位占用一块内存分配区的作用
	//     在TCP/IP中，可使用sockaddr_in结构替换sockaddr，以方便填写地址信息
	// 
	//     struct sockaddr_in{ short sin_family; unsigned short sin_port; struct in_addr sin_addr; char sin_zero[8];};
	//     sin_family表示地址族，对于IP地址，sin_family成员将一直是AF_INET。
	//     sin_port指定将要分配给套接字的端口。
	//     sin_addr给出套接字的主机IP地址。
	//     sin_zero[8]给出填充数，让sockaddr_in与sockaddr结构的长度一样。
	//     将IP地址指定为INADDR_ANY，允许套接字向任何分配给本地机器的IP地址发送或接收数据。
	//     如果想只让套接字使用多个IP中的一个地址，可指定实际地址，用inet_addr()函数。
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // 将INADDR_ANY转换为网络字节序，调用 htonl(long型)或htons(整型)
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	bind(sockSrv, (SOCKADDR*)& addrSrv, sizeof(SOCKADDR)); // 第二参数要强制类型转换

	// 将套接字设置为监听模式（连接请求）， listen()通知TCP服务器准备好接收连接
	// int listen(SOCKET s,  int backlog);
	// 第一个参数指定需要设置的套接字，第二个参数为（等待连接队列的最大长度）
	listen(sockSrv, 10);

	// accept()，接收连接，等待客户端连接
	// SOCKET accept(  SOCKET s,  struct sockaddr* addr,  int* addrlen);
	// 第一个参数，接收一个处于监听状态下的套接字
	// 第二个参数，sockaddr用于保存客户端地址的信息
	// 第三个参数，用于指定这个地址的长度
	// 返回的是向与这个监听状态下的套接字通信的套接字

	// 客户端与用户端进行通信

	// send(), 在套接字上发送数据
	// int send( SOCKET s,  const char* buf,  int len,  int flags);
	// 第一个参数，需要发送信息的套接字，
	// 第二个参数，包含了需要被传送的数据，
	// 第三个参数是buffer的数据长度，
	// 第四个参数，一些传送参数的设置

	// recv(), 在套接字上接收数据
	// int recv(  SOCKET s,  char* buf,  int len,  int flags);
	// 第一个参数，建立连接后的套接字，
	// 第二个参数，接收数据
	// 第三个参数，接收数据的长度，
	// 第四个参数，一些传送参数的设置

	SOCKADDR_IN  addrClient;
	int len = sizeof(SOCKADDR);

	while (true) {	// 不断等待客户端请求的到来
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)& addrClient, &len);
		cout << "连接成功！" << endl;

		char recvChar[2];
		recv(sockConn, recvChar, 2, 0);

		if (recvChar[0] == 'r')        //若为注册;
		{
			char recvUserName[9];
			char recvUserCode[9];
			recv(sockConn, recvUserName, 9, 0);
			recv(sockConn, recvUserCode, 9, 0);

			//注册;
			cout << "注册中..." << endl;
			cout << "用户名：" << recvUserName << "\t密码：" << recvUserCode << endl;

			fstream file("F:\\user.dat", ios::out | ios::binary | ios::app);
			file.write((char*)recvUserName, sizeof(recvUserName));
			file.write((char*)recvUserCode, sizeof(recvUserCode));
			file.close();

			cout << "注册成功！" << endl;
			send(sockConn, "true", strlen("true") + 1, 0);
		}
		else if (recvChar[0] == 'l')
		{
			cout << "登录中..." << endl;
			char recvUserName[9];
			char recvUserCode[9];
			recv(sockConn, recvUserName, 9, 0);
			recv(sockConn, recvUserCode, 9, 0);

			//登录;			
			cout << "用户名：" << recvUserName << "\t密码：" << recvUserCode << endl;

			fstream file("F:\\user.dat", ios::in | ios::binary);
			if (file.fail())
			{
				cout << "读取时，打开文件失败...;" << endl;
				exit(0);
			}

			cout << "打开文件读取数据....;" << endl;
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
				cout << "登录成功！" << endl;
				send(sockConn, "true", strlen("true") + 1, 0);
			}
			else
			{
				cout << "登录失败！" << endl;
				send(sockConn, "false", strlen("false") + 1, 0);
			}
		}
		else if (recvChar[0] == 'c')
		{
			cout << "计算中..." << endl;
			char recvExpresion[50];
			recv(sockConn, recvExpresion, 50, 0);

			string SrecvExpresion(recvExpresion);

			//计算;			
			cout << "计算表达式：" << recvExpresion << ";" << endl;

			stringstream os;
			os << main2(SrecvExpresion);
			string Sanswer = os.str();

			send(sockConn, Sanswer.c_str(), Sanswer.size() + 1, 0);
			cout << "计算结果：" << Sanswer << ";" << endl;

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


