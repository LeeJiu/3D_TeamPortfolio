#pragma once


class cCommand
{
public:
	cCommand();
	virtual ~cCommand();

	//���߿� ĳ���͸� �μ��� �޾Ƽ� �÷����� ���͸� ����������.
	//virtual void Execute(cActor& actor) = 0;
	virtual void Execute() = 0;
};

