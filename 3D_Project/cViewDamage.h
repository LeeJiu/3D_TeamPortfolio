#pragma once
#include "cTransform.h"

class cViewDamage : public cTransform
{
private:
	int num;		//받아온 숫자
	int unit;		//1의자리
	int tens;		//10의자리
	int hund;		//100의자리
	int thou;		//1000의자리
	int mil;		//10000의자리

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

