#pragma once
#include "cTransform.h"

class cViewDamage : public cTransform
{
private:
	int num;		//�޾ƿ� ����
	int unit;		//1���ڸ�
	int tens;		//10���ڸ�
	int hund;		//100���ڸ�
	int thou;		//1000���ڸ�
	int mil;		//10000���ڸ�

	cTransform unit_trans;
	cTransform tens_trans;
	cTransform hund_trans;
	cTransform thou_trans;
	cTransform mil_trans;

	cTransform damage_trans;

public:
	cViewDamage();
	~cViewDamage();

	void SetNumber(int number, cTransform* trans);
	void Release();
	void Update(float timeDelta);
	void Render();
};

