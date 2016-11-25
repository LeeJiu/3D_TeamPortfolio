#pragma once
#include "cMonster.h"

class cBasilisk : public cMonster
{
private:
	bool			m_bHit2;

public:
	cBasilisk();
	~cBasilisk();

	void BaseObjectEnable();					//SetActive(true)�ϸ� ����� -> �ʱ�ȭ �Լ�
	void BaseObjectUpdate(float timeDelta);		//BaseObject �� Update �� ����....
	void BaseObjectBoundBox();					//SetMesh() �ϸ� ComputeBoundBox() ����Ǹ鼭 �����
	void BaseObjectRender();

	//==========�̰��� �Լ� �߰�==========
	void Damage(float fDamage);		//cMonster�� �θ� �� �ִ� ���� ���� �Լ� / �ݵ�� override
	void MoveToPlayer();
	void Attack01(float timeDelta);
	void Attack02(float timeDelta);
	void SetAniState();

	void RangeIn(float timeDelta);
	void RangeOut();


	//�÷��̾� ��ũ
	void SetPlayer(cPlayer* pPlayer) { m_pPlayer = pPlayer; }
};

