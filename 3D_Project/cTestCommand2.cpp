#include "stdafx.h"
#include "cTestCommand2.h"


cTestCommand2::cTestCommand2()
{
}


cTestCommand2::~cTestCommand2()
{
}

void cTestCommand2::Execute()
{
	LOG_MGR->AddLog("테스트 커멘드 2 실행");
}
