#pragma once
#include "cBaseObject.h"

class cQuadParticleEmitter;


class cSkill_Round : public cBaseObject
{
private:


	bool               m_IsSelect;         // ��ų ���콺 �������̴�
	bool               m_IsCasting;        // ��ų ĳ���� ���̴�
	bool               m_IsAttacking;      // ��ų ���� ���̴�
	bool               m_IsCoolTime;       // ��ų ��Ÿ�� ���̴�



	cQuadParticleEmitter*   m_CircleEfc;     //�Ķ� ���� 
	cQuadParticleEmitter*   m_CastEfc;       //���� ����
	cQuadParticleEmitter*   m_SurroundEfc;   //��Ÿ� ����


	int                   m_CastTime;
	int                   m_CastTimeMax;
	float                 m_CastEfcScale;
	int                   m_MaxDistance; //�ִ� ��Ÿ�
	D3DXVECTOR3           m_MousePos;


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
	cSkill_Round();
	~cSkill_Round();

	void BaseObjectEnable(float surroundLength, int castTime, int maxDistance);

	void BaseObjectUpdate(D3DXVECTOR3 CasterWorldPos, float timeDelta, D3DXVECTOR3 mousePos);

	void BaseObjectRender();

	void SelectSkill(); //��ų�� ��������

	void StartCasting();

	void UseSkill();  //��ų�� �������

};



