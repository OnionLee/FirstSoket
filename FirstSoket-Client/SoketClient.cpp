#include "stdafx.h"
#include "SoketClient.h"


SoketClient::SoketClient()
{
}


SoketClient::~SoketClient()
{
}

bool SoketClient::init()
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
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(PORT);
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	result = connect(hServSock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));
	if (result == SOCKET_ERROR)
	{
		printf("connect() Error\n");
		return false;
	}


	return true;

}

void SoketClient::Loop()
{
	int count = 0; 
	while (1)
	{
		char buf[255] = { 0 };
		printf(">> ");
		//�Է�
		gets_s(buf);
		//�Է��� ������ send �� recv 
		//���� ���尡 ������ ��� ���Ϲ��� ���鼭
		//���ۿ� �ִ� ���� �����´�.
		//������ ũ�⸸ŭ �����´�.
		int sendsize = send(hServSock, buf, strlen(buf), 0);

		count++;
		if (count>2)
			break;
	}

	while (true)
	{
		char buf[255];
		memset(buf, 0, sizeof(buf));
		recv(hServSock, buf, sizeof(buf), 0);
		printf("result = %s", buf);
		
		if (strlen(buf) > 0)
		{
			break;
		}
	}



	closesocket(hServSock);
	WSACleanup();
}
