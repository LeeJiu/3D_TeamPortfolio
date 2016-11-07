#pragma once
#include "cCommand.h"

class cTestCommand : public cCommand
{
public:
	cTestCommand();
	~cTestCommand();

	void Execute();
};