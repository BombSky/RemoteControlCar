#include <iostream>
#include <conio.h>
#include <winsock2.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	WORD wdVersion = MAKEWORD(2, 2);
	WSADATA wdSockMsg;
	int nRes = WSAStartup(wdVersion, &wdSockMsg);


	//版本校验
	if (2 != HIBYTE(wdSockMsg.wVersion) || 2 != LOBYTE(wdSockMsg.wVersion))
	{
		std::cout << "版本校验 fail\n";
		WSACleanup();
		return 0;
	}

	SOCKET socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == socketServer)
	{
		std::cout << "模式设置错误\n";
		WSACleanup();
		return 0;
	}

	//cmd查看端口号netstat -ano
	//netstat -ano|findstr "12345"
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = inet_addr("192.168.0.104");
	//绑定
	if (SOCKET_ERROR == bind(socketServer, (const sockaddr*)&si, sizeof(si)))
	{
		std::cout << "绑定 fail\n";
		closesocket(socketServer);
		WSACleanup();
		return 0;
	}
	//监听
	if (SOCKET_ERROR == listen(socketServer, SOMAXCONN))
	{
		std::cout << "监听 fail\n";
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}
	//创建客户端链接
	sockaddr_in clienMsg;
	int len = sizeof(clienMsg);
	SOCKET socketClient = accept(socketServer, (sockaddr*)&clienMsg, &len);
	if (INVALID_SOCKET == socketServer)
	{
		closesocket(socketServer);
		WSACleanup();
		return 0;
	}
	char ch;
	while (true)
	{
		//char str[1500] = { 0 };
		//std::cin >> str;
		ch = _getch();
		if ('w' == ch) send(socketClient, "w", strlen("w") + sizeof(char), NULL);
		else if ('a' == ch) send(socketClient, "a", strlen("w") + sizeof(char), NULL);
		else if ('s' == ch) send(socketClient, "s", strlen("w") + sizeof(char), NULL);
		else if ('d' == ch) send(socketClient, "d", strlen("w") + sizeof(char), NULL);
	}

	closesocket(socketClient);
	closesocket(socketServer);
	WSACleanup();
	return 0;
}