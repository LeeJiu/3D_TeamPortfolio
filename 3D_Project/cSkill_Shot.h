#pragma once
#include "cBaseObject.h"
#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"

// �߻��� ��ų�� 
// �߻� ��ư Ŭ���� ������ ����(�Ǵ� ���Ϳ��� �Ÿ����� �߻�ȴ�)



class cSkill_Shot : public cBaseObject
{
protected:


	bool               m_IsShot;           // ��ų �߻����̴�?
	bool               m_IsInRange;        // �߻��� ��ų�� ��Ÿ� ���̴�?
	bool               m_IsAttacking;      // ��ų�� ��Ƽ� �����ϰ� �ִ�?

	int                m_AttackingCount;   //���� �����ð��� ���
	int                m_AttackingTime;    //��ų�� �ӹ��� �ִ� �ð��� ���

	float                   m_MaxDistance;   //���� ��Ÿ�

	D3DXVECTOR3             m_LookDir;         //�ٶ󺸴� ����
	D3DXVECTOR3             m_CasterWorldPos;   //�������� ��ġ
	D3DXVECTOR3             m_EnemyPos;       //������ ������ ����

	cBoundBox               m_BoundBox;


public:
	cSkill_Shot();
	~cSkill_Shot();

	void BaseObjectEnable(D3DXVECTOR3 casterWorldPos, float maxDistance, int attackingTime);

	void BaseObjectUpdate(float timeDelta, D3DXVECTOR3 casterWorldPos, D3DXVECTOR3 lookDir);

	void BaseObjectRender();

	void ShotSkill(); //��ų�� �߻��Ϸ���
	void MakeAtk();



	bool GetIsShot() { return m_IsShot; }       // �߻� ���̴�
	bool GetIsAttacking() { return m_IsAttacking; } //�����ϰ��ִ�?

protected:
	//����Ʈ �Լ��� �ʿ��ϸ�..

	virtual void Effect_Init() {};
	virtual void Effect_Update(float timeDelta) {};
	virtual void Effect_Render() {};


};

