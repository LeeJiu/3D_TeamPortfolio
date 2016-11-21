#pragma once
#include "cBaseObject.h"

class cQuadParticleEmitter;

class cSkill_Surround : public cBaseObject
{

private:
	
	bool               m_IsSelect; // ��ų ���콺 �������̴�
	bool               m_IsCasting; // ��ų ĳ���� ���̴�
	bool               m_IsAttacking; // ��ų ���� ���̴�
	bool               m_IsCoolTime;  // ��ų ��Ÿ�� ���̴�



	cQuadParticleEmitter*   m_CircleEfc;
	cQuadParticleEmitter*   m_CastEfc;
	int                   m_CastTime;
	int                   m_CastTimeMax;
	float                   m_CastEfcScale;

	D3DXVECTOR3      m_CasterWorldPos; //�������� ��ġ
	float            m_SurroundLength; //����



	cBoundSphere     m_BoundSphere;
	cTransform*      m_CasterPos;       //�������� ��ġ
	float            m_SurroundRadius;  //���� ����
	

	// int              m_HitMax;          //Ÿ���ο�
	float            m_tickTime;
	float            m_timeTemp;

	int              m_Damage;
	int              m_UseSP;




	bool             m_IsHit;              //���� �¾Ҵ�?


public:
	cSkill_Surround();
	~cSkill_Surround();

	void BaseObjectEnable(D3DXVECTOR3  casterWorldPos, float surroundLength, int castTime);

	void BaseObjectUpdate(float timeDelta, D3DXVECTOR3 CasterWorldPos);

	void BaseObjectRender();

	void SelectSkill(); //��ų�� ��������

	void StartCasting();

	void UseSkill();  //��ų�� �������



};

