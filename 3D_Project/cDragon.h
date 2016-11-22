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
	cBoundBox m_Bound[COLLISION];       //���� �� �ٿ
	cTransform* m_boneTrans[COLLISION]; //���� �� Ʈ����

	D3DXVECTOR3 collPos[8];
	cTransform* collTrans[5];           //�浹üũ�� �� Ʈ����

	stSphere spone;      // ������ ���� ��. 

public:
	cDragon();
	~cDragon();
	
	void BaseObjectEnable();					//SetActive(true)�ϸ� ����� -> �ʱ�ȭ �Լ�
	void BaseObjectUpdate(float timeDelta);		//BaseObject �� Update �� ����....
	void BaseObjectBoundBox();					//SetMesh() �ϸ� ComputeBoundBox() ����Ǹ鼭 �����
	void BaseObjectRender();
	
	//==========�̰��� �Լ� �߰�==========
	void Damage(float fDamage);		//cMonster�� �θ� �� �ִ� ���� ���� �Լ� / �ݵ�� override

	//========= collTrans �� ���� =======
	void collPosUpdate();
	bool battleRange();

	//�÷��̾� ��ũ
	void SetPlayer(cPlayer* pPlayer) { m_pPlayer = pPlayer; }
};

