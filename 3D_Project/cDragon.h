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

	string m_nowAni;                      // �ִϸ��̼�
	
	
	bool isMove;                          // �����̴���?
	bool isBattle;                        // ������?
	bool isBasicAttack;                   // ��Ÿ��?
	
	bool isBreath;                        // �극����?
	bool isEarthquake;                    // ������?
	bool isHeadAtt;                       // �Ӹ� ġ��
	
	bool isNoneBasicAttack;               // ��Ÿ�̿��� ��ų.( ���� �Ⱦ��� �𸣰��� )
	int skillChance;                      // ��ų �ߵ�Ȯ��

	float skillCoolTime;                 // ��ų ��Ÿ��
	float tempCoolTime;                  // ��ų ��Ÿ�ֿ̹� ��� �� ��
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
	//========= ó�� ���� �������� �� �Լ� ====
	void spawn();
	// ��ų ������Ʈ �Լ�  
	void basicAttackUpdate();
	void breathUpdate();
	void earthUpate();
	void HeadAttUpate();
	// ���°� �ʱ�ȭ.
	void stateInit();
	// ���� ȸ�� ��Ű�� �ϴ� �Լ�
	void LookPos(D3DXVECTOR3 target);
	// �ִϸ��̼� ���� ���ִ� �Լ�
	void aniManager();
	//�÷��̾� ��ũ
	void SetPlayer(cPlayer* pPlayer) { m_pPlayer = pPlayer; }


};

