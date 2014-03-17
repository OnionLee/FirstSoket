#pragma once

#define BUFSIZE 100		// �޾ƿ� ������ �ִ� ũ��
#define PORT 3000		// ��Ʈ��ȣ �Ҵ�

class CSoketServer
{
private:
	//������ ���� ����
	WSADATA wsaData;
	//����
	SOCKET hServSock;
	//���� �ּ�
	SOCKADDR_IN servAddr;
	
	//Ŭ���̾�Ʈ ����
	SOCKET hClntSock;

	//Ŭ���̾�Ʈ ���� �ּ�
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

