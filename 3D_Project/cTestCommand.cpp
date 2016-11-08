#include "stdafx.h"
#include "cTestCommand.h"


cTestCommand::cTestCommand()
{
}


cTestCommand::~cTestCommand()
{
}

void cTestCommand::Execute()
{
	LOG_MGR->AddLog("테스트 커멘드 1 실행");
}
