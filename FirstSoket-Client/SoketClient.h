#pragma once

#define BUFSIZE 100		// �޾ƿ� ������ �ִ� ũ��
#define PORT 3000		// ��Ʈ��ȣ �Ҵ�

class SoketClient
{
private:
	//������ ���� ����
	WSADATA wsaData;
	//����
	SOCKET hServSock;
	//���� �ּ�
	SOCKADDR_IN servAddr;



public:
	SoketClient();
	~SoketClient();

	bool init();
	void Loop();

};

