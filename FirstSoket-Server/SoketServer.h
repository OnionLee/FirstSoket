#pragma once

#define BUFSIZE 100		// 받아올 데이터 최대 크기
#define PORT 3000		// 포트번호 할당

class CSoketServer
{
private:
	//소켓의 버전 정보
	WSADATA wsaData;
	//소켓
	SOCKET hServSock;
	//서버 주소
	SOCKADDR_IN servAddr;
	
	//클라이언트 소켓
	SOCKET hClntSock;

	//클라이언트 소켓 주소
	SOCKADDR_IN clntAddr;
	
public:
	CSoketServer();
	~CSoketServer();

	bool init();

	void Loop();

	int Rvalue;
	int Lvalue;
	int Result;

};

