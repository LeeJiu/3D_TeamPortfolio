#pragma once

class cCommand
{
public:
	cCommand();
	virtual ~cCommand();

	virtual void Execute() = 0;
};

