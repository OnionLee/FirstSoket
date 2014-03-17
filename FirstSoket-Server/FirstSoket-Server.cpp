// FirstSoket-Server.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "SoketServer.h"


using namespace std;



int _tmain(int argc, _TCHAR* argv[])
{
	// 서버 인스턴트
	CSoketServer server;

	// 서버시작
	if (server.init())
	{
		server.Loop();
	}
	
	return 0;
}

