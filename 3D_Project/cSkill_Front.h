#pragma once
#include "cBaseObject.h"
#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"



class cSkill_Front : public cBaseObject
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

	

	cQuadParticleEmitter*   m_CastEfc;       //���� ����
	
	
	float                   m_MaxDistance;   //���� ��Ÿ�
	float                   m_MaxWidth;      //���� ��

	D3DXVECTOR3             m_LookDir;          //�ٶ󺸴� ����
	D3DXVECTOR3             m_CasterWorldPos;   //�������� ��ġ
	D3DXVECTOR3             m_AttackPos;


	cBoundBox               m_BoundBox;


public:
	cSkill_Front();
	~cSkill_Front();



	void BaseObjectEnable(D3DXVECTOR3 casterWorldPos, float maxDistance, float maxWidth, int castTime, int attackingTime, int coolTime);

	void BaseObjectUpdate(float timeDelta, D3DXVECTOR3 casterWorldPos, D3DXVECTOR3 mousePos);

	void BaseObjectRender();

	void SelectSkill(); //UI�� ��ų�� ���콺 ���� ������ �ҷ�����

	void StartCasting(); //��ų�� ����Ѵ� ��ý��� ��ų�� �� �Լ��� �ҷ�����


	bool GetIsSelecting() { return m_IsSelect; } //�������̴�?
	bool GetIsAttacking() { return m_IsAttacking; } //�����ϰ��ִ�?

protected:
	//����Ʈ �Լ��� �ʿ��ϸ�..

	virtual void Effect_Init() {};
	virtual void Effect_Update(float timeDelta) {};
	virtual void Effect_Render() {};


};
