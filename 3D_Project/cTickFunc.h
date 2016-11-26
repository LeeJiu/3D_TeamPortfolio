#pragma once



class cTickFunc
{
	float countTime; // 계산에 쓰일 변수
	float tickTime;  // 틱 시간
	
	bool start;
	//bool hit;

public:
	cTickFunc();
	~cTickFunc();

	void init(float tick);
	void tickUpdate(float timeDelta);
	bool tickStart();
};

