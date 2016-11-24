#include "stdafx.h"
#include "cViewDamage.h"


cViewDamage::cViewDamage()
{
	num = 0;
}


cViewDamage::~cViewDamage()
{
}

void cViewDamage::SetNumber(int number, cTransform * trans)
{
	num = number;
	if (num != 0)
	{
		if (num < 10)
		{
			unit = num;

			unit_trans = *(trans);
		}
		else if (num < 100)
		{
			unit = (number % 10);
			tens = (number / 10) % 10;

			unit_trans = *(trans);
			tens_trans = *(trans);
			tens_trans.MovePositionLocal(-2, 0, 0);
		}
		else if (num < 1000)
		{
			unit = (number % 10);
			tens = (number / 10) % 10;
			hund = (number / 100);
		}
		else if (num < 10000)
		{
			unit = (number % 10);
			tens = (number / 10) % 10;
			hund = (number / 100) % 10;
			thou = (number / 1000);
		}
		else if (num < 100000)
		{
			unit = (number % 10);
			tens = (number / 10) % 10;
			hund = (number / 100) % 10;
			thou = (number / 1000) % 10;
			mil = (number / 10000);
		}
		else
		{
			LOG_MGR->AddLog("숫자 표기 범위를 벗어낫다대스");
			return;
		}
	}
}

void cViewDamage::Release()
{
}

void cViewDamage::Update(float timeDelta)
{
}

void cViewDamage::Render()
{

}
