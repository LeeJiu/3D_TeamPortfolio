#include "stdafx.h"
#include "cTickFunc.h"


cTickFunc::cTickFunc()
{
	countTime = 0.f;
	start = false;
}


cTickFunc::~cTickFunc()
{

}
void cTickFunc::init(float tick)
{
	tickTime = tick;
}

void cTickFunc::tickUpdate(float timeDelta)
{
	//처음 함수 들어왔을때 카운트 되겠금 함.

	if (start == true)
	{
		if (countTime < tickTime)
		{
			countTime += timeDelta;  // 시간 값을 계산.
			//hit = false;
		}
		else if (countTime >= tickTime)
		{
			countTime = 0.f; // 
			start = false;
			//hit = true;
		}
	}



}

bool cTickFunc::tickStart()
{
	if (start == false)  // false가 초기값
	{
		start = true;
		//hit = true;
		return true;
	}

	return false;
}

