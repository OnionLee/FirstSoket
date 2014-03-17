#include "stdafx.h"
#include "SoketServer.h"


CSoketServer::CSoketServer()
{
}


CSoketServer::~CSoketServer()
{
}

bool CSoketServer::init()
{
	//버전 생성
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		printf("error");
		return false;
	}

	//소켓 설정(TCP 할지 UDP할지)
	hServSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//아이피 설정
	servAddr = { 0 };
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(PORT);
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//바인드
	result = bind(hServSock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));

	if (result != 0)
	{
		printf("error");
		return false;
	}

	//연결 대기
	listen(hServSock, 10);

	clntAddr = { 0 };
	int size = sizeof(SOCKADDR_IN);
	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &size);
	
	if (hClntSock == SOCKET_ERROR)
	{
		printf("error");
		return false;
	}

	printf("클라이언트 접속\n");
	printf("IP : %s , Port : %d\n", inet_ntoa(clntAddr.sin_addr), clntAddr.sin_port);

	RvalueInput();

	LValueInput();


	LastInput();



}

void CSoketServer::Loop()
{
	while (1)
	{
		char buf[255];
		memset(buf, 0, sizeof(buf));
		int recvsize = recv(hClntSock, buf, sizeof(buf), 0);
	
		buf[recvsize = '\0'];
		if (strcmp(buf, "x") == 0)
		{
			printf("접속 종료\n");
			break;
		}
		printf("client >> %s\n", buf);
		int sendsize = send(hClntSock, buf, strlen(buf), 0);

	}

	closesocket(hClntSock);
	closesocket(hServSock);
	WSACleanup();
}

void CSoketServer::RvalueInput()
{
	printf("안녕하세요. 첫번째 수를 입력 해 주세요!");
	while (true)
	{
		char buf[255];
		memset(buf, 0, sizeof(buf));
		int recvsize = recv(hClntSock, buf, sizeof(buf), 0);

		if (recvsize > 0)
		{
			buf[recvsize] = '\0';
			Lvalue = atoi(buf);
			break;
		}
	}
}

void CSoketServer::LValueInput()
{
	printf("두번째 수를 입력 해 주세요!");
	while (true)
	{
		char buf[255];
		memset(buf, 0, sizeof(buf));
		int recvsize = recv(hClntSock, buf, sizeof(buf), 0);

		if (recvsize > 0)
		{
			buf[recvsize] = '\0';
			Rvalue = atoi(buf);
			break;
		}
	}
}

void CSoketServer::LastInput()
{
	printf("수식을 입력 해 주세요!");
	while (true)
	{
		char buf[255];
		memset(buf, 0, sizeof(buf));
		int recvsize = recv(hClntSock, buf, sizeof(buf), 0);

		if (recvsize > 0)
		{
			buf[recvsize] = '\0';
			if (strcmp(buf, "+") == 0)
			{
				memset(buf, 0, sizeof(buf));
				sprintf_s(buf, "%d", Rvalue + Lvalue);
				send(hClntSock, buf, sizeof(buf), 0);
			}
			else if (strcmp(buf, "-") == 0)
			{
				memset(buf, 0, sizeof(buf));
				sprintf_s(buf, "%d", Rvalue - Lvalue);
				send(hClntSock, buf, sizeof(buf), 0);
			}
			else if (strcmp(buf, "*") == 0)
			{
				memset(buf, 0, sizeof(buf));
				sprintf_s(buf, "%d", Rvalue * Lvalue);
				send(hClntSock, buf, sizeof(buf), 0);
			}
			else if (strcmp(buf, "/") == 0)
			{
				memset(buf, 0, sizeof(buf));
				sprintf_s(buf, "%f", (float)(Rvalue / Lvalue));
				send(hClntSock, buf, sizeof(buf), 0);
			}
		}
	}
}

