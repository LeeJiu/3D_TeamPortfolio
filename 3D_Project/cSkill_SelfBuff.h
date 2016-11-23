#pragma once
#include "cBaseObject.h"
#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"


class cSkill_SelfBuff : public cBaseObject
{
protected:

	bool               m_IsSelect;       // ��ų ���콺 �������̴�
	bool               m_IsCasting;      // ��ų ĳ���� ���̴�
	bool               m_IsInBuff;       // ���� �������̴�
	bool               m_IsCoolTime;     // ��ų ��Ÿ�� ���̴�


	// (���� �����̱� ������ ����ǥ�ð� ����)


	int                   m_CastTimeCount; //ĳ���� ��� Ÿ��
	int                   m_CastTime;      //ĳ���� Ǯ Ÿ��

	int                   m_CoolTimeCount; //��Ÿ�� ���
	int                   m_CoolTime;      //��Ÿ��

	int                   m_BuffCount; //���ӽð�
	int                   m_BuffTime; //���� ���ӽð�

	float                 m_CastEfcScale;


	D3DXVECTOR3      m_CasterWorldPos; //�������� ��ġ



public:
	cSkill_SelfBuff();
	~cSkill_SelfBuff();

	void BaseObjectEnable(D3DXVECTOR3  casterWorldPos, int castTime, int buffCount, int coolTime);

	void BaseObjectUpdate(float timeDelta, D3DXVECTOR3 CasterWorldPos);

	void SelectSkill(); //UI�� ��ų�� ���콺 ���� ������ �ҷ�����

	void StartCasting(); //��ų�� ����Ѵ� ��ý��� ��ų�� �� �Լ��� �ҷ�����


	bool GetIsInBuff() { return m_IsInBuff; } //�����ϰ��ִ�?


protected:
	//����Ʈ �Լ��� �ʿ��ϸ�..

	virtual void Effect_Init() {};
	virtual void Effect_Update(float timeDelta) {};
	virtual void Effect_Render() {};


};

