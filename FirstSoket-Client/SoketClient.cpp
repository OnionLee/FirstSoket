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
		//입력
		gets_s(buf);
		//입력이 끝나면 send 후 recv 
		//만약 샌드가 없더라도 계속 와일문을 돌면서
		//버퍼에 있는 값을 가져온다.
		//버퍼의 크기만큼 가져온다.
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
