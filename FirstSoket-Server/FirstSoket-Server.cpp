// FirstSoket-Server.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "SoketServer.h"


using namespace std;



int _tmain(int argc, _TCHAR* argv[])
{
	// ���� �ν���Ʈ
	CSoketServer server;

	// ��������
	if (server.init())
	{
		server.Loop();
	}
	
	return 0;
}

