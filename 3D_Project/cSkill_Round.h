#pragma once
#include "cBaseObject.h"
#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"



class cSkill_Round : public cBaseObject
{
protected:

	bool               m_IsSelect;         // ��ų ���콺 �������̴�
	bool               m_IsCasting;        // ��ų ĳ���� ���̴�
	bool               m_IsAttacking;      // ��ų ���� ���̴�
	bool               m_IsCoolTime;       // ��ų ��Ÿ�� ���̴�


	int                   m_CastTimeCount; //ĳ���� ��� Ÿ��
	int                   m_CastTime;      //ĳ���� Ǯ Ÿ��

	int                   m_CoolTimeCount; //��Ÿ�� ���
	int                   m_CoolTime;      //��Ÿ��

	int                   m_AttackingCount; //���� �����ð��� ���
	int                   m_AttackingTime;

	float                 m_CastEfcScale;



	cQuadParticleEmitter*   m_CircleEfc;     //�Ķ� ���� 
	cQuadParticleEmitter*   m_CastEfc;       //���� ����
	cQuadParticleEmitter*   m_SurroundEfc;   //��Ÿ� ����
	int                     m_MaxDistance; //�ִ� ��Ÿ�

	D3DXVECTOR3             m_MousePos;
	D3DXVECTOR3             m_CasterWorldPos; //�������� ��ġ
	D3DXVECTOR3             m_AttackPos;       //�����ϴ� ������ ������
	float                   m_SurroundLength; //����


	cBoundSphere     m_BoundSphere;







public:
	cSkill_Round();
	~cSkill_Round();

	void BaseObjectEnable(D3DXVECTOR3  casterWorldPos, float surroundLength, int maxDistance, int castTime, int attackingTime, int coolTime);

	void BaseObjectUpdate(float timeDelta, D3DXVECTOR3 casterWorldPos, D3DXVECTOR3 mousePos);

	void BaseObjectRender();

	void SelectSkill(); //UI�� ��ų�� ���콺 ���� ������ �ҷ�����

	void StartCasting(); //��ų�� ����Ѵ� ��ý��� ��ų�� �� �Լ��� �ҷ�����

	int  GetCastCount()   { return m_CastTimeCount; } //�������۽� ����� ����������� ��� ����������
	int  GetAtkCount()   { return m_AttackingCount; }
	bool GetIsSelecting() { return m_IsSelect; } //�������̴�?
	bool GetIsAttacking() { return m_IsAttacking; } //�����ϰ��ִ�?


protected:
	//����Ʈ �Լ��� �ʿ��ϸ�..

	virtual void Effect_Init() {};
	virtual void Effect_Update(float timeDelta) {};
	virtual void Effect_Render() {};

};



