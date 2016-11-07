#pragma once


class cCommand
{
public:
	cCommand();
	virtual ~cCommand();

	//나중에 캐릭터를 인수로 받아서 플레이할 액터를 설정해주자.
	//virtual void Execute(cActor& actor) = 0;
	virtual void Execute() = 0;
};

