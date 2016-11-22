#pragma once
#include "cMonster.h"
#include "cBoundBox.h"

#define COLLISION 6

class cDragon : public cMonster
{
private:
	int m_collCount;
	cBoundBox m_Bound[COLLISION];
	cTransform m_boneTrans[COLLISION];


public:
	cDragon();
	~cDragon();

	void BaseObjectEnable();					//SetActive(true)�ϸ� ����� -> �ʱ�ȭ �Լ�
	void BaseObjectUpdate(float timeDelta);		//BaseObject �� Update �� ����....
	void BaseObjectBoundBox();					//SetMesh() �ϸ� ComputeBoundBox() ����Ǹ鼭 �����
	void BaseObjectRender();
	
	//==========�̰��� �Լ� �߰�==========
	void Damage(float fDamage);		//cMonster�� �θ� �� �ִ� ���� ���� �Լ� / �ݵ�� override



	//�÷��̾� ��ũ
	void SetPlayer(cPlayer* pPlayer) { m_pPlayer = pPlayer; }
};

