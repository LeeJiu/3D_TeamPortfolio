#pragma once
#include "cBaseObject.h"
#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"


class cSkill_Surround : public cBaseObject
{
public:
	int                   m_CastTimeCount; //ĳ���� ��� Ÿ��
	int                   m_CastTime;      //ĳ���� Ǯ Ÿ��

	int                   m_CoolTimeCount; //��Ÿ�� ���
	int                   m_CoolTime;      //��Ÿ��

	int                   m_AttackingCount; //���� �����ð��� ���
	int                   m_AttackingTime;	//���ݽð�

protected:
	bool               m_IsSelect;       // ��ų ���콺 �������̴�
	bool               m_IsCasting;      // ��ų ĳ���� ���̴�
	bool               m_IsAttacking;    // ��ų ���� ���̴�
	bool               m_IsCoolTime;     // ��ų ��Ÿ�� ���̴�


	// �⺻ �������� ���� �ʱ�ȭ 

	cQuadParticleEmitter*   m_CircleEfc;
	cQuadParticleEmitter*   m_CastEfc;

	float                 m_CastEfcScale;

	cBoundSphere     m_BoundSphere;

	D3DXVECTOR3      m_CasterWorldPos; //�������� ��ġ
	float            m_SurroundLength; //����



public:
	cSkill_Surround();
	~cSkill_Surround();

	void BaseObjectEnable(D3DXVECTOR3  casterWorldPos, float surroundLength, int castTime, int attackingTime, int coolTime);

	void BaseObjectUpdate(float timeDelta, D3DXVECTOR3 CasterWorldPos);

	void BaseObjectRender();

	void SelectSkill(); //UI�� ��ų�� ���콺 ���� ������ �ҷ�����

	void StartCasting(); //��ų�� ����Ѵ� ��ý��� ��ų�� �� �Լ��� �ҷ�����



	bool GetIsAttacking() { return m_IsAttacking; } //�����ϰ��ִ�?
	bool GetIsCool() { return m_IsCoolTime; }

protected:
	//����Ʈ �Լ��� �ʿ��ϸ�..

	virtual void Effect_Init() {};
	virtual void Effect_Update(float timeDelta) {};
	virtual void Effect_Render() {};
};

