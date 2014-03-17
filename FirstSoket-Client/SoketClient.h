#pragma once

#define BUFSIZE 100		// 받아올 데이터 최대 크기
#define PORT 3000		// 포트번호 할당

class SoketClient
{
private:
	//소켓의 버전 정보
	WSADATA wsaData;
	//소켓
	SOCKET hServSock;
	//서버 주소
	SOCKADDR_IN servAddr;



public:
	SoketClient();
	~SoketClient();

	bool init();
	void Loop();

};

