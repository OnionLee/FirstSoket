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
	//���� ����
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		printf("error");
		return false;
	}

	//���� ����(TCP ���� UDP����)
	hServSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//������ ����
	servAddr = { 0 };
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(PORT);
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//���ε�
	result = bind(hServSock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));

	if (result != 0)
	{
		printf("error");
		return false;
	}

	//���� ���
	listen(hServSock, 10);

	clntAddr = { 0 };
	int size = sizeof(SOCKADDR_IN);
	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &size);
	
	if (hClntSock == SOCKET_ERROR)
	{
		printf("error");
		return false;
	}

	printf("Ŭ���̾�Ʈ ����\n");
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
			printf("���� ����\n");
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
	printf("�ȳ��ϼ���. ù��° ���� �Է� �� �ּ���!");
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
	printf("�ι�° ���� �Է� �� �ּ���!");
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
	printf("������ �Է� �� �ּ���!");
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

