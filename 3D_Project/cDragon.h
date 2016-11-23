#pragma once
#include "cMonster.h"
#include "cBoundBox.h"

#define COLLISION 4
/*
   ������ �ɾ�� ������ ���۵�.
   ���� ġ���� ���� �������� ����ߵ�.
*/
struct stSphere
{
	D3DXVECTOR3 worldCenter;
	float radius;
};

class cDragon : public cMonster
{
private:
	int m_collCount;                    //���� ������ ������ ����
	cBoundBox m_bound[COLLISION];       //���� �� �ٿ
	cTransform* m_pBoneTrans[COLLISION]; //���� �� Ʈ����

	D3DXVECTOR3 m_collPos[8];
	cTransform* m_pCollTrans[5];           //�浹üũ�� �� Ʈ����

	stSphere m_spone;                     // ������ ���� ��. 
	stSphere m_basicAttack;               // ��Ÿ ���� �Ÿ�

	bool isMove;                
public:
	cDragon();
	~cDragon();
	
	void BaseObjectEnable();					//SetActive(true)�ϸ� ����� -> �ʱ�ȭ �Լ�
	void BaseObjectUpdate(float timeDelta);		//BaseObject �� Update �� ����....
	void BaseObjectBoundBox();					//SetMesh() �ϸ� ComputeBoundBox() ����Ǹ鼭 �����
	void BaseObjectRender();
	
	//==========�̰��� �Լ� �߰�==========
	void Damage(float fDamage);		//cMonster�� �θ� �� �ִ� ���� ���� �Լ� / �ݵ�� override
	void MoveToPlayer();
	
	//========= collTrans �� ���� =======
	void collPosUpdate();
	//========= update ������ �� �Լ� =====
	bool battleRange();
	bool basicRange();
	//========= ���� �ִϸ��̼� �Լ� ========
	void basicAttack();
	
	//�÷��̾� ��ũ
	void SetPlayer(cPlayer* pPlayer) { m_pPlayer = pPlayer; }


};

