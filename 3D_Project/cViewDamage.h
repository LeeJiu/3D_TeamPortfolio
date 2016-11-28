#pragma once
#include "cQuadParticleEmitter.h"

class cViewDamage
{
private:

	int num;		//�޾ƿ� ����
	int unit;		//1���ڸ�
	int tens;		//10���ڸ�
	int hund;		//100���ڸ�
	int thou;		//1000���ڸ�
	int mil;		//10000���ڸ�

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

