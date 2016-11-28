#pragma once
#include "cQuadParticleEmitter.h"

class cViewDamage
{
private:

	int num;		//받아온 숫자
	int unit;		//1의자리
	int tens;		//10의자리
	int hund;		//100의자리
	int thou;		//1000의자리
	int mil;		//10000의자리

	cQuadParticleEmitter* unit_quard;
	cQuadParticleEmitter* tens_quard;
	cQuadParticleEmitter* hund_quard;
	cQuadParticleEmitter* thou_quard;
	cQuadParticleEmitter* mil_quard;

	cTransform damage_trans;

	float m_time;
	bool  m_isDrawing;

public:
	cViewDamage();
	~cViewDamage();

	void Init();

	void SetNumber(int number);
	void Release();
	void Update(float timeDelta, cTransform * trans, cCamera* camera);
	void Render();

	bool GetIsDrawing() { return m_isDrawing; }
};

