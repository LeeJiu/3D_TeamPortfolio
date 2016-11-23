#pragma once
#include "cBaseObject.h"
#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"

class cSkill_Escape : public cBaseObject
{
protected:

	bool               m_IsSelect;       // ��ų ���콺 �������̴�
	bool               m_IsCasting;      // ��ų ĳ���� ���̴�
	bool               m_IsInBuff;       // ���� �������̴�
	bool               m_IsCoolTime;     // ��ų ��Ÿ�� ���̴�


	// ȸ�Ǳ⸦ ������ ������ ������ �̵��ؾ��Ѵ�.
	

	int                   m_CastTimeCount; //ĳ���� ��� Ÿ��
	int                   m_CastTime;      //ĳ���� Ǯ Ÿ��

	int                   m_CoolTimeCount; //��Ÿ�� ���
	int                   m_CoolTime;      //��Ÿ��

	int                   m_BuffCount; //���ӽð�
	int                   m_BuffTime; //���� ���ӽð�

	float                 m_CastEfcScale;



	cQuadParticleEmitter*   m_CircleEfc;     //�Ķ� ���� 


	D3DXVECTOR3      m_CasterWorldPos; //�������� ��ġ
	D3DXVECTOR3      m_LookDir;
	float            m_MoveLength;    //�����ڰ� �������� �̵��� �Ÿ���
	D3DXVECTOR3      m_CasterMovePos; //�������� �̵��� ������


public:
	cSkill_Escape();
	~cSkill_Escape();

	void BaseObjectEnable(D3DXVECTOR3  casterWorldPos, float moveLength, int castTime, int buffCount, int coolTime);

	void BaseObjectUpdate(float timeDelta, D3DXVECTOR3 CasterWorldPos, D3DXVECTOR3 lookDir);

	void BaseObjectRender();

	void SelectSkill(); //UI�� ��ų�� ���콺 ���� ������ �ҷ�����

	void StartCasting(); //��ų�� ����Ѵ� ��ý��� ��ų�� �� �Լ��� �ҷ�����

	int         GetBuffCount() { return m_BuffCount; }
	bool        GetIsInBuff() { return m_IsInBuff; } //ȸ�ǹ��� ���̴�?
	D3DXVECTOR3 GetEscapePos() { return pTransform->GetWorldPosition(); }

protected:
	//����Ʈ �Լ��� �ʿ��ϸ�..

	virtual void Effect_Init() {};
	virtual void Effect_Update(float timeDelta) {};
	virtual void Effect_Render() {};
};

